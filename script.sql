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


  CREATE TABLE Veranstalter_Veranstaltung_Uhrzeit (
        uhrzeit_ID INTEGER REFERENCES Uhrzeit(ID),
        tag INTEGER NOT NULL,
        veranstalter_ID INTEGER REFERNECES Veranstalter(ID),
        veranstaltung_ID INTEGER REFERENCES Veranstaltung(ID),
        PRIMARY KEY(uhrzeit_ID, tag)
    );


    INSERT INTO Veranstalter (name, email, passwort, admin) VALUES
       ('tech_guru', 'admin@example.com', 'password123', 1),
('code_master', 'user1@example.com', 'password1', 0),
('binary_hero', 'user2@example.com', 'password2', 0),
('debug_ninja', 'user3@example.com', 'password3', 0),
('data_wizard', 'user4@example.com', 'password4', 0),
('script_samurai', 'user5@example.com', 'password5', 0),
('dev_genius', 'user6@example.com', 'password6', 0),
('cyber_maven', 'user7@example.com', 'password7', 0),
('net_knight', 'user8@example.com', 'password8', 0),
('bit_boss', 'user9@example.com', 'password9', 0),
('sys_sensei', 'user10@example.com', 'password10', 0),
('crypto_champ', 'user11@example.com', 'password11', 0),
('cloud_conqueror', 'user12@example.com', 'password12', 0),
('hack_whiz', 'user13@example.com', 'password13', 0),
('matrix_mage', 'user14@example.com', 'password14', 0),
('app_artisan', 'user15@example.com', 'password15', 0),
('ai_architect', 'user16@example.com', 'password16', 0),
('tech_titan', 'user17@example.com', 'password17', 0),
('proto_pro', 'user18@example.com', 'password18', 0),
('alg_adept', 'user19@example.com', 'password19', 0),
('data_diver', 'user20@example.com', 'password20', 0),
('web_warrior', 'user21@example.com', 'password21', 0),
('os_overlord', 'user22@example.com', 'password22', 0),
('kernel_keeper', 'user23@example.com', 'password23', 0);

    INSERT INTO Veranstaltung (ort, raum, name, dauer) VALUES 
    ('A', '101', 'Grundlagen der Programmierung', 2),
('B', '202', 'Algorithmen und Datenstrukturen', 4),
('A', '103', 'Netzwerkgrundlagen', 2),
('B', '204', 'Betriebssystemkonzepte', 4),
('A', '105', 'Softwareentwicklung', 2),
('B', '206', 'Intelligente Systeme', 4),
('A', '107', 'Datenbanksysteme', 2),
('B', '208', 'Webtechnologien', 2),
('A', '109', 'Computergrafikgrundlagen', 2),
('B', '210', 'Maschinelles Lernen', 2);
