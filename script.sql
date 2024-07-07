
DROP VIEW studenten_veranstalter;

DROP TABLE Veranstalter_Veranstaltung_Uhrzeit;
DROP TABLE Studenten;
DROP TABLE Veranstalter;
DROP TABLE Uhrzeit;
DROP TABLE veranstaltung;
DROP SEQUENCE global_id_seq;





CREATE SEQUENCE global_id_seq START WITH 1000000 INCREMENT BY 1;

CREATE TABLE Studenten (
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


CREATE TABLE Veranstalter (
    ID INTEGER PRIMARY KEY DEFAULT nextval('global_id_seq'), 
    name VARCHAR(30),
    email VARCHAR(30),
    passwort VARCHAR(30),
    arbeitszeit INTEGER DEFAULT 0,
    standort VARCHAR(30) DEFAULT random_between_two(),
    krank BOOLEAN DEFAULT FALSE,
    admin BOOLEAN NOT NULL DEFAULT FALSE
);




            
 CREATE VIEW studenten_veranstalter AS 
 SELECT matrikelnummer AS id, passwort, NULL AS admin FROM Studenten 
     UNION ALL 
 SELECT ID, passwort, admin FROM Veranstalter;



 CREATE TABLE Veranstaltung ( 
            ID SERIAL PRIMARY KEY, 
            ort VARCHAR(30) NOT NULL, 
            raum INTEGER NOT NULL, 
            name VARCHAR(90) NOT NULL,
            dauer INTEGER NOT NULL,
            used INTEGER DEFAULT(0)
            );




   CREATE TABLE Uhrzeit ( 
            ID SERIAL PRIMARY KEY, 
            anfangszeit TIME NOT NULL, 
            endzeit TIME NOT NULL );



    INSERT INTO Uhrzeit (anfangszeit, endzeit) VALUES 
            ('08:00:00', '10:00:00'), 
            ('10:00:00', '12:00:00'), 
            ('12:00:00', '14:00:00'), 
            ('14:00:00', '16:00:00'), 
            ('16:00:00', '18:00:00'); 


    CREATE TABLE Veranstalter_Veranstaltung_Uhrzeit (
        uhrzeit_ID INTEGER REFERENCES Uhrzeit(ID),
        tag INTEGER NOT NULL,
        veranstalter_ID INTEGER REFERENCES Veranstalter(ID) ON DELETE CASCADE,
        veranstaltung_ID INTEGER REFERENCES Veranstaltung(ID) ON DELETE CASCADE,
        PRIMARY KEY(uhrzeit_ID, tag)
    );

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
