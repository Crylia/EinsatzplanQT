
DROP VIEW studenten_veranstalter;

DROP TABLE Veranstalter_Veranstaltung_Uhrzeit;
DROP TABLE Studenten;
DROP TABLE Veranstalter;
DROP TABLE Uhrzeit;
DROP TABLE veranstaltung;
DROP SEQUENCE global_id_seq;





CREATE SEQUENCE global_id_seq START WITH 1000000 INCREMENT BY 1;

CREATE TABLE IF NOT EXISTS Studenten (
    matrikelnummer INTEGER PRIMARY KEY DEFAULT nextval('global_id_seq'),
    name VARCHAR(30) NOT NULL,
    email VARCHAR(30) NOT NULL,
    passwort VARCHAR(30) NOT NULL
);


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


CREATE TABLE Uhrzeit ( 
    ID SERIAL PRIMARY KEY, 
    anfangszeit TIME NOT NULL, 
    endzeit TIME NOT NULL 
);

CREATE TABLE Veranstalter (
    ID INTEGER PRIMARY KEY DEFAULT nextval('global_id_seq'), 
    name VARCHAR(30),
    email VARCHAR(30),
    passwort VARCHAR(30),
    arbeitszeit INTEGER DEFAULT 0,
    admin BOOLEAN NOT NULL DEFAULT FALSE
);

            
 CREATE VIEW studenten_veranstalter AS 
 SELECT matrikelnummer AS id, passwort, NULL AS admin FROM Studenten 
     UNION ALL 
 SELECT ID, passwort, admin FROM Veranstalter;



 CREATE TABLE Veranstaltung ( 
            ID SERIAL PRIMARY KEY, 
            ort VARCHAR(1) DEFAULT random_between_two(), 
            raum INTEGER NOT NULL, 
            name VARCHAR(3) NOT NULL,
            dauer INTEGER NOT NULL,
            used INTEGER DEFAULT(0)
            );

CREATE TABLE StundenImPlan(
    uhrzeit_ID INTEGER REFERENCES Uhrzeit(ID),
    tag INTEGER NOT NULL,
    veranstalter_ID INTEGER REFERENCES Veranstalter(ID) ON DELETE CASCADE,
    veranstaltung_ID INTEGER REFERENCES Veranstaltung(ID) ON DELETE CASCADE,
    PRIMARY KEY(uhrzeit_ID, tag)
);

CREATE TABLE Krankmeldung(
    uhrzeit_id INTEGER REFERENCES StundenImPlan(uhrzeit_ID),
    tag INTEGER REFERENCES StundenImPlan(tag),
    veranstalter_id INTEGER REFERENCES StundenImPlan(veranstalter_ID),
    PRIMARY KEY (uhrzeit_ID,tag,veranstalter_id)
)


CREATE OR REPLACE FUNCTION handle_veranstalter_update() RETURNS TRIGGER AS $$
DECLARE
    neuer_veranstalter INTEGER;
BEGIN
    -- Wenn die Veranstalter_ID auf NULL gesetzt wird oder ein Veranstalter gelöscht wird
    IF TG_OP = 'UPDATE' AND NEW.veranstalter_ID IS NULL THEN
        -- Eintrag in die Krankmeldung
        INSERT INTO Krankmeldung (uhrzeit_ID, tag, veranstalter_id) 
        VALUES (OLD.uhrzeit_ID, OLD.tag, OLD.veranstalter_ID);
    ELSIF TG_OP = 'DELETE' THEN
        -- Eintrag in die Krankmeldung für jede betroffene Stunde
        INSERT INTO Krankmeldung (uhrzeit_ID, tag, veranstalter_id)
        SELECT uhrzeit_ID, tag, OLD.ID FROM StundenImPlan WHERE veranstalter_ID = OLD.ID;
    END IF;

    -- Finde den Veranstalter mit den wenigsten Arbeitsstunden,
    -- der am selben Tag keine Veranstaltung in einer anderen Uhrzeit an einem anderen Ort hat
    SELECT ID INTO neuer_veranstalter
    FROM Veranstalter
    WHERE ID NOT IN (
        SELECT veranstalter_ID FROM StundenImPlan
        WHERE tag = OLD.tag
        AND uhrzeit_ID != OLD.uhrzeit_ID
        AND veranstaltung_ID IN (
            SELECT ID FROM Veranstaltung WHERE ort != (
                SELECT ort FROM Veranstaltung WHERE ID = NEW.veranstaltung_ID
            )
        )
    )
    ORDER BY arbeitszeit ASC
    LIMIT 1;

    -- Wenn ein neuer Veranstalter gefunden wurde
    IF neuer_veranstalter IS NOT NULL THEN
        IF TG_OP = 'UPDATE' THEN
            NEW.veranstalter_ID := neuer_veranstalter;
        ELSIF TG_OP = 'DELETE' THEN
            UPDATE StundenImPlan
            SET veranstalter_ID = neuer_veranstalter
            WHERE veranstalter_ID = OLD.ID;
        END IF;
        -- Update der Arbeitszeit des neuen Veranstalters
        UPDATE Veranstalter
        SET arbeitszeit = arbeitszeit + (
            SELECT dauer FROM Veranstaltung WHERE ID = (
                CASE WHEN TG_OP = 'UPDATE' THEN NEW.veranstaltung_ID ELSE OLD.ID END
            )
        )
        WHERE ID = neuer_veranstalter;
    ELSE
        IF TG_OP = 'DELETE' THEN
            UPDATE StundenImPlan
            SET veranstalter_ID = NULL
            WHERE veranstalter_ID = OLD.ID;
        END IF;
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_handle_veranstalter_update
BEFORE UPDATE ON StundenImPlan
FOR EACH ROW
EXECUTE FUNCTION handle_veranstalter_update();

CREATE TRIGGER trg_handle_veranstalter_delete
BEFORE DELETE ON Veranstalter
FOR EACH ROW
EXECUTE FUNCTION handle_veranstalter_update();



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