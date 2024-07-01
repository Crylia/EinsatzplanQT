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
       ('tech_guru', 'admin@example.com', 'password123', TRUE),
('code_master', 'user1@example.com', 'password1', FALSE),
('binary_hero', 'user2@example.com', 'password2', FALSE),
('debug_ninja', 'user3@example.com', 'password3', FALSE),
('data_wizard', 'user4@example.com', 'password4', FALSE),
('script_samurai', 'user5@example.com', 'password5', FALSE),
('dev_genius', 'user6@example.com', 'password6', FALSE),
('cyber_maven', 'user7@example.com', 'password7', FALSE),
('net_knight', 'user8@example.com', 'password8', FALSE),
('bit_boss', 'user9@example.com', 'password9', FALSE),
('sys_sensei', 'user10@example.com', 'password10', FALSE),
('crypto_champ', 'user11@example.com', 'password11', FALSE),
('cloud_conqueror', 'user12@example.com', 'password12', FALSE),
('hack_whiz', 'user13@example.com', 'password13', FALSE),
('matrix_mage', 'user14@example.com', 'password14', FALSE),
('app_artisan', 'user15@example.com', 'password15', FALSE),
('ai_architect', 'user16@example.com', 'password16', FALSE),
('tech_titan', 'user17@example.com', 'password17', FALSE),
('proto_pro', 'user18@example.com', 'password18', FALSE),
('alg_adept', 'user19@example.com', 'password19', FALSE),
('data_diver', 'user20@example.com', 'password20', FALSE),
('web_warrior', 'user21@example.com', 'password21', FALSE),
('os_overlord', 'user22@example.com', 'password22', FALSE),
('kernel_keeper', 'user23@example.com', 'password23', FALSE);

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


INSERT INTO Veranstalter_Veranstaltung_Uhrzeit (uhrzeit_ID, tag, veranstaltung_ID) VALUES
(1, 1, 1),
(2, 1, 2),
(3, 1, 2),
(4, 1, 3),

(1, 2, 4),
(2, 2, 4),
(3, 2, 5),
(4, 2, 6),
(5, 2, 6),

(1, 3, 7),
(2, 3, 8),
(3, 3, 9),
(4, 3, 10),
(5, 3, 1),

(1, 4, 2),
(2, 4, 2),
(3, 4, 3),
(4, 4, 4),
(5, 4, 4),

(1, 5, 5),
(2, 5, 6),
(3, 5, 6),
(4, 5, 7),
(5, 5, 8);
