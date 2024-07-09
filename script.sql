
CREATE SEQUENCE global_id_seq START WITH 1000000 INCREMENT BY 1;

CREATE OR REPLACE FUNCTION random_between_two()
RETURNS VARCHAR AS $$
BEGIN
    IF random() < 0.5 THEN
        RETURN 'A';
    ELSE
        RETURN 'B';
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION random_between_days()
RETURNS INTEGER AS $$
BEGIN
    RETURN floor(random() * 5 + 1)::INTEGER;
END;
$$ LANGUAGE plpgsql;

CREATE TABLE IF NOT EXISTS Uhrzeit ( 
  ID SERIAL PRIMARY KEY,
  anfangszeit TIME NOT NULL,
  endzeit TIME NOT NULL
);

CREATE TABLE IF NOT EXISTS Veranstaltung( 
  name VARCHAR(3) PRIMARY KEY,
  ort VARCHAR(1) DEFAULT random_between_two(),
  raum INTEGER NOT NULL,
  dauer INTEGER NOT NULL,
  used_in_plan INTEGER DEFAULT 0
);

CREATE TABLE IF NOT EXISTS Veranstalter(
  ID INTEGER PRIMARY KEY DEFAULT nextval('global_id_seq'), 
  name VARCHAR(30),
  email VARCHAR(30),
  passwort VARCHAR(30),
  arbeitszeit INTEGER DEFAULT 0,
  admin BOOLEAN NOT NULL DEFAULT FALSE
);

CREATE TABLE IF NOT EXISTS StundeImPlan (
  uhrzeit INTEGER REFERENCES Uhrzeit(ID),
  tag INTEGER NOT NULL,
  veranstaltung VARCHAR(3) REFERENCES Veranstaltung(name) ON DELETE CASCADE,
  veranstalter INTEGER REFERENCES Veranstalter(ID)  ON DELETE SET NULL,
  PRIMARY KEY(uhrzeit, tag)
);

CREATE TABLE IF NOT EXISTS Krank(
  ID SERIAL PRIMARY KEY,
  stundeImPlan_uhrzeit INTEGER,
  stundeImPlan_tag INTEGER,
  veranstalter INTEGER REFERENCES Veranstalter(ID) ON DELETE SET NULL,
  krank BOOLEAN DEFAULT FALSE,
  FOREIGN KEY (stundeImPlan_uhrzeit, stundeImPlan_tag) REFERENCES StundeImPlan(uhrzeit, tag) ON DELETE CASCADE
);

CREATE OR REPLACE FUNCTION delete_stundeimplan_for_veranstaltung()
RETURNS TRIGGER AS $$
BEGIN
    DELETE FROM StundeImPlan WHERE veranstaltung = OLD.name;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_delete_stundeimplan_for_veranstaltung
AFTER DELETE ON Veranstaltung
FOR EACH ROW
EXECUTE FUNCTION delete_stundeimplan_for_veranstaltung();

CREATE OR REPLACE FUNCTION update_stundeimplan_for_veranstalter()
RETURNS TRIGGER AS $$
DECLARE
    new_veranstalter_id INTEGER;
BEGIN
    SELECT ID INTO new_veranstalter_id
    FROM Veranstalter
    WHERE arbeitszeit < 18
    ORDER BY arbeitszeit ASC
    LIMIT 1;

    IF new_veranstalter_id IS NOT NULL THEN
        UPDATE StundeImPlan
        SET veranstalter = new_veranstalter_id
        WHERE veranstalter = OLD.ID;
    END IF;

    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_update_stundeimplan_for_veranstalter
AFTER DELETE ON Veranstalter
FOR EACH ROW
EXECUTE FUNCTION update_stundeimplan_for_veranstalter();

CREATE OR REPLACE FUNCTION update_arbeitszeit_for_veranstalter()
RETURNS TRIGGER AS $$
BEGIN
    UPDATE Veranstalter
    SET arbeitszeit = arbeitszeit + (SELECT dauer FROM Veranstaltung WHERE name = NEW.veranstaltung)
    WHERE ID = NEW.veranstalter;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_update_arbeitszeit_for_veranstalter
AFTER INSERT ON StundeImPlan
FOR EACH ROW
EXECUTE FUNCTION update_arbeitszeit_for_veranstalter();

CREATE OR REPLACE FUNCTION generate_plan()
RETURNS TRIGGER AS $$
DECLARE
    v_row RECORD;
    u_row RECORD;
    available_veranstalter RECORD;
    random_day INTEGER;
BEGIN
    FOR u_row IN SELECT * FROM Uhrzeit LOOP
        FOR v_row IN SELECT * FROM Veranstaltung WHERE used_in_plan = 0 LOOP
            SELECT * INTO available_veranstalter
            FROM Veranstalter v
            WHERE v.arbeitszeit + v_row.dauer <= 18
              AND NOT EXISTS (
                  SELECT 1
                  FROM StundeImPlan sp
                  JOIN Veranstaltung va ON sp.veranstaltung = va.name
                  WHERE sp.uhrzeit = u_row.ID
                    AND sp.tag = random_day
                    AND sp.veranstalter = v.ID
              )
              AND NOT EXISTS (
                  SELECT 1
                  FROM StundeImPlan prev_sp
                  JOIN Veranstaltung prev_va ON prev_sp.veranstaltung = prev_va.name
                  WHERE prev_sp.uhrzeit = u_row.ID - 1
                    AND prev_sp.tag = random_day
                    AND prev_sp.veranstalter = v.ID
                    AND prev_va.ort <> v_row.ort 
              )
            ORDER BY v.arbeitszeit ASC
            LIMIT 1;

            IF FOUND THEN
                random_day = random_between_days();
                IF NOT EXISTS (
                    SELECT 1
                    FROM StundeImPlan
                    WHERE uhrzeit = u_row.ID AND tag = random_day
                ) THEN
                    INSERT INTO StundeImPlan (uhrzeit, tag, veranstaltung, veranstalter)
                    VALUES (u_row.ID, random_day, v_row.name, available_veranstalter.ID);

                    UPDATE Veranstaltung SET used_in_plan = used_in_plan + 1 WHERE name = v_row.name;
                    UPDATE Veranstalter SET arbeitszeit = arbeitszeit + v_row.dauer WHERE ID = available_veranstalter.ID;

                    IF v_row.dauer = 4 THEN
                        IF EXISTS (SELECT 1 FROM Uhrzeit WHERE ID = u_row.ID + 1) THEN
                            IF NOT EXISTS (
                                SELECT 1
                                FROM StundeImPlan
                                WHERE uhrzeit = u_row.ID + 1 AND tag = random_day
                            ) THEN
                                INSERT INTO StundeImPlan (uhrzeit, tag, veranstaltung, veranstalter)
                                VALUES (u_row.ID + 1, random_day, v_row.name, available_veranstalter.ID);

                                UPDATE Veranstaltung SET used_in_plan = used_in_plan + 1 WHERE name = v_row.name;
                            END IF;
                        END IF;
                    END IF;
                END IF;
            END IF;
        END LOOP;
    END LOOP;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;
CREATE TRIGGER trg_generate_plan
AFTER INSERT ON Veranstaltung
FOR EACH STATEMENT
EXECUTE FUNCTION generate_plan();

CREATE OR REPLACE FUNCTION handle_krank_insert()
RETURNS TRIGGER AS $$
DECLARE
    new_veranstalter_id INTEGER;
    v_name VARCHAR(3);
BEGIN
    SELECT veranstaltung.name INTO v_name
    FROM Veranstaltung
    WHERE name = (SELECT veranstaltung FROM StundeImPlan WHERE uhrzeit = NEW.stundeImPlan_uhrzeit AND tag = NEW.stundeImPlan_tag);

    WITH PreviousHour AS (
        SELECT sp.veranstalter, v.ort
        FROM StundeImPlan sp
        JOIN Veranstaltung v ON sp.veranstaltung = v.name
        WHERE sp.uhrzeit = NEW.stundeImPlan_uhrzeit - 1
          AND sp.tag = NEW.stundeImPlan_tag
    )
    SELECT v.ID INTO new_veranstalter_id
    FROM Veranstalter v
    JOIN StundeImPlan sp ON v.ID = sp.veranstalter
    JOIN Veranstaltung va ON sp.veranstaltung = va.name
    LEFT JOIN PreviousHour ph ON v.ID = ph.veranstalter
    WHERE v.arbeitszeit + (SELECT dauer FROM Veranstaltung WHERE name = v_name) <= 18
      AND NOT EXISTS (
          SELECT 1
          FROM Krank k
          WHERE k.veranstalter = v.ID
            AND k.stundeImPlan_uhrzeit = NEW.stundeImPlan_uhrzeit
            AND k.stundeImPlan_tag = NEW.stundeImPlan_tag
      )
      AND (ph.veranstalter IS NULL OR ph.veranstalter <> (
        SELECT v.ID
            FROM Veranstalter v
            JOIN StundeImPlan sp ON v.ID = sp.veranstalter
            JOIN Veranstaltung vaa ON sp.veranstaltung = vaa.name
            WHERE sp.uhrzeit = NEW.stundeImPlan_uhrzeit
            AND sp.tag = NEW.stundeImPlan_tag
            AND vaa.ort = va.ort
      ))
    ORDER BY v.arbeitszeit ASC
    LIMIT 1;

    IF new_veranstalter_id IS NOT NULL THEN
        UPDATE Veranstalter
        SET arbeitszeit = arbeitszeit + (SELECT dauer FROM Veranstaltung WHERE name = v_name)
        WHERE ID = new_veranstalter_id;

        UPDATE StundeImPlan
        SET veranstalter = new_veranstalter_id
        WHERE uhrzeit = NEW.stundeImPlan_uhrzeit AND tag = NEW.stundeImPlan_tag;
    ELSE
        UPDATE StundeImPlan
        SET veranstalter = NULL
        WHERE uhrzeit = NEW.stundeImPlan_uhrzeit AND tag = NEW.stundeImPlan_tag;
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_handle_krank_insert
AFTER INSERT ON Krank
FOR EACH ROW
EXECUTE FUNCTION handle_krank_insert();

CREATE OR REPLACE FUNCTION handle_veranstalter_deletion() RETURNS TRIGGER AS $$
DECLARE
    new_veranstalter RECORD;
    affected_row RECORD;
BEGIN
    FOR affected_row IN
        SELECT * FROM StundeImPlan WHERE veranstalter = OLD.id
    LOOP
        SELECT * INTO new_veranstalter
        FROM Veranstalter v
        WHERE v.arbeitszeit + (SELECT dauer FROM Veranstaltung va WHERE va.name = affected_row.veranstaltung) <= 18
          AND NOT EXISTS (
              SELECT 1
              FROM Krank k
              WHERE k.veranstalter = v.ID
                AND k.stundeImPlan_uhrzeit = affected_row.uhrzeit
                AND k.stundeImPlan_tag = affected_row.tag
          )
          AND NOT EXISTS (
              SELECT 1
              FROM StundeImPlan sp
              JOIN Veranstaltung va ON sp.veranstaltung = va.name
              WHERE sp.uhrzeit = affected_row.uhrzeit - 1
                AND sp.tag = affected_row.tag
                AND sp.veranstalter = v.ID
                AND va.ort <> (SELECT ort FROM Veranstaltung WHERE name = affected_row.veranstaltung)
          )
          AND v.ID <> affected_row.veranstalter
        ORDER BY v.arbeitszeit ASC
        LIMIT 1;

        UPDATE StundeImPlan
        SET veranstalter = new_veranstalter.ID
        WHERE uhrzeit = affected_row.uhrzeit AND tag = affected_row.tag AND veranstalter = OLD.id;

        UPDATE Veranstalter
        SET arbeitszeit = arbeitszeit + (SELECT dauer FROM Veranstaltung WHERE name = affected_row.veranstaltung)
        WHERE ID = new_veranstalter.ID;
    END LOOP;

    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE TRIGGER before_veranstalter_delete
BEFORE DELETE ON Veranstalter
FOR EACH ROW
EXECUTE FUNCTION handle_veranstalter_deletion();

INSERT INTO Uhrzeit (anfangszeit, endzeit) VALUES 
    ('08:00:00', '10:00:00'), 
    ('10:00:00', '12:00:00'), 
    ('12:00:00', '14:00:00'), 
    ('14:00:00', '16:00:00'), 
    ('16:00:00', '18:00:00'); 

INSERT INTO Veranstalter (name, email, passwort, admin) VALUES
('Davids', 'admin@example.com', 'password123', TRUE),
('Dalitz', 'user1@example.com', 'password1', FALSE),
('Tipp', 'user2@example.com', 'password2', FALSE),
('Quix', 'user3@example.com', 'password3', FALSE),
('Nietsche', 'user4@example.com', 'password4', FALSE),
('Ueberholz', 'user5@example.com', 'password5', FALSE),
('Rethmann', 'user6@example.com', 'password6', FALSE),
('Pohle-Fröhlich', 'user7@example.com', 'password7', FALSE),
('Stockmann', 'user8@example.com', 'password8', FALSE),
('Gref', 'user9@example.com', 'password9', FALSE),
('Naroska', 'user10@example.com', 'password10', FALSE),
('Grothe', 'user11@example.com', 'supersicherespasswort123', FALSE);


INSERT INTO Veranstaltung (ort, raum, name, dauer) VALUES 
('A', '101', 'GDI', 2),
('B', '202', 'ALD', 4),
('A', '103', 'ITS', 2),
('B', '204', 'BSY', 4),
('A', '105', 'PE1', 2),
('B', '206', 'THI', 4),
('A', '107', 'DBS', 2),
('B', '208', 'WEB', 2),
('A', '109', 'BVA', 2),
('B', '210', 'MA1', 2);
