CREATE SEQUENCE global_id_seq;

CREATE TABLE Studenten (
            matrikelnummer INTEGER PRIMARY KEY DEFAULT nextval('global_id_seq'),
            "name VARCHAR(30) NOT NULL,
            "email VARCHAR(30) NOT NULL,
            "passwort VARCHAR(30) NOT NULL);


 "CREATE TABLE Veranstalter (
            ID INTEGER PRIMARY KEY DEFAULT nextval('global_id_seq'), 
            name VARCHAR(30),
            email VARCHAR(30),
            passwort VARCHAR(30),
            admin BOOLEAN NOT NULL DEFAULT(FALSE)

            );


CREATE TABLE krank (
            veranstalter_ID INTEGER,
            FOREIGN KEY (veranstalter_ID) REFERENCES veranstalterrrr(ID) ON DELETE CASCADE);


            
 CREATE VIEW studenten_veranstalterr AS 
 SELECT matrikelnummer AS id, passwort, NULL AS admin FROM Studenten 
     UNION ALL 
 SELECT ID, passwort, admin FROM Veranstalterrrr;



 CREATE TABLE Veranstaltung ( 
            ID SERIAL PRIMARY KEY, 
            ort VARCHAR(30) NOT NULL, 
            raum VARCHAR(30) NOT NULL, 
            name VARCHAR(30) NOT NULL );




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