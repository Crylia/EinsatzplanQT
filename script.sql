
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
