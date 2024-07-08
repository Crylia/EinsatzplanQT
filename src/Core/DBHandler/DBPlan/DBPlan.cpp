#include "DBPlan.hpp"

DBPlan::DBPlan(std::string connStr) : DBHandler(connStr) { };

void DBPlan::vertretung(std::string tag, std::string stunde) {
    try {
        std::string dauer = getDauer(tag, stunde);
        std::string prevStunde = std::to_string(std::stoi(stunde) - 1);
        std::string cap = std::to_string(18 - std::stoi(dauer));
        std::string nextStunde;
        std::string nextTag = tag;
        std::string prevTag = tag;
        if (dauer == "4") {
           
           nextStunde = std::to_string(std::stoi(stunde) + 2);        
        }
        else {
           nextStunde = std::to_string(std::stoi(stunde) + 1);
           
        }
        
        if (prevStunde == "0") {
            prevStunde = "5";
            prevTag = std::to_string(std::stoi(tag) - 1);
            if (prevTag == "0") {
                prevTag = "5";
            }
        }

        if (nextStunde == "6") {
            nextStunde = "1";
            nextTag = std::to_string(std::stoi(tag)+1);
            if (nextTag == "6") {
                nextTag = "1";
            }
        }

        pqxx::work worker(connectionObject);
        pqxx::result response;
        int i = 1;
        while (i != 0) {
            std::string query0 =
                R"(SELECT Veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE veranstalter_ID IS NOT NULL AND uhrzeit_id = $1 AND tag = $2;)";
            response = worker.exec_params(query0, prevStunde, prevTag);
            worker.commit();
            
            fmt::print("{0}\n",response.size());
            if (response.size() != 0) {
                i = 0;
                break;
            }
            prevStunde = std::to_string(std::stoi(prevStunde) - 1);
            if (prevStunde == "0") {
                prevStunde = "5";
                prevTag = std::to_string(std::stoi(prevTag) - 1);
                if (prevTag == "0") {
                    prevTag = "5";
                }
            }          
        }
        

        pqxx::result res;
        i = 1;
        while (i != 0) {
            
            std::string query00 =
                R"(SELECT Veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE veranstalter_ID IS NOT NULL AND uhrzeit_id = $1 AND tag = $2;)";
            res = worker.exec_params(query00, nextStunde, nextTag);
            worker.commit();

            if (response.size() != 0) {
                i = 0;
                break;
            }
            nextStunde = std::to_string(std::stoi(nextStunde) + 1);
            if (nextStunde == "6") {
                nextStunde = "1";
                nextTag = std::to_string(std::stoi(nextTag) + 1);
                if (nextTag == "6") {
                    nextTag = "1";
                }
            }         
        } 
         
     
        std::string query =
            R"(UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_ID = 
            (SELECT ID FROM Veranstalter WHERE ID != (SELECT Veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2 LIMIT 1)
            AND ID != (SELECT Veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $3 AND tag = $4 LIMIT 1)
            AND uhrzeit_id != $5 AND tag != $6 LIMIT 1) WHERE uhrzeit_id = $7 AND tag = $8;)";
      
        response = worker.exec_params(query, prevStunde, prevTag, nextStunde, nextTag, stunde, tag, stunde, tag);
       
        worker.commit();

        if (response.affected_rows() == 0) {
            meldeGesund(tag, stunde);
            std::string query2 =
                "DELETE FROM Veranstalter_Veranstaltung_Uhrzeit WHERE tag = $1 AND uhrzeit_id = $2";
            worker.exec_params(query2, tag, stunde);
            worker.commit();

            if (dauer == "4") {
                std::string query3 =
                    "DELETE FROM Veranstalter_Veranstaltung_Uhrzeit WHERE tag = $1 AND uhrzeit_id = $2";
                worker.exec_params(query3, tag, nextStunde);
                worker.commit();
            }
        }
        else {
            incarbeitszeit(tag, stunde, dauer);
            if (dauer == "4") {
                upperHour(tag, stunde);
            }
        }
        

    }
    catch (const std::exception& e) {
        fmt::println(e.what( ));

    }
}

void DBPlan::meldeKrank(std::string id, std::string tag, std::string stunde) {
	try {
		pqxx::work worker(connectionObject);
		std::string query =
			"UPDATE Veranstalter SET krank = TRUE, tag = $1, uhrzeit_id = $2 WHERE ID = $3;";

		worker.exec_params(query, tag, stunde, id);
		worker.commit( );

		vertretung(tag, stunde);
		versendeEmails( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::meldeGesund(std::string tag, std::string stunde) {
	try {
		pqxx::work worker(connectionObject);
		std::string query = "UPDATE Veranstalter SET krank = FALSE, uhrzeit_ID = 0, tag = 0 WHERE tag = $1 AND uhrzeit_id = $2;";

		worker.exec_params(query, id);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::deleteVeranstalterForeign(std::string id) {
	try {
		pqxx::work worker(connectionObject);
		std::string query =
			"SELECT tag, uhrzeit_id FROM Veranstalter_Veranstaltung_Uhrzeit WHERE Veranstalter_ID = $1; ";

		pqxx::result response = worker.exec_params(query, id);
		worker.commit( );

		std::string tag, stunde;

		for (int i = 0; i < response.affected_rows( ); i++) {
			tag = response[i][0].c_str( );
			stunde = response[i][1].c_str( );
			std::string query2 =
				"UPDATE Veranstalter SET krank = TRUE, tag = $1, uhrzeit_id = $2 WHERE ID = $3;";

			pqxx::result response = worker.exec_params(query, tag, stunde, id);
			worker.commit( );
			vertretung(tag, stunde);
			if (getDauer(tag, stunde) == "4")
				i++;
		}
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::deleteVeranstalter(std::string id) {
	try {
		deleteVeranstalterForeign(id);
		pqxx::work worker(connectionObject);
		std::string query = "DELETE FROM Veranstalter WHERE ID = $1;";

		worker.exec_params(query, id);
		worker.commit( );
		versendeEmails( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::deleteVeranstaltung(std::string name) {
	try {
		pqxx::work worker(connectionObject);
		std::string query = "DELETE FROM Veranstaltung WHERE name = $1;";

		worker.exec_params(query, name);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::hinzufuegenVeranstaltung(std::string name, std::string dauer, std::string ort, std::string raum) {
	try {
		pqxx::work worker(connectionObject);
		std::string query =
			"INSERT INTO Veranstaltung (name, dauer, ort, raum) VALUES ($1, $2, $3, $4);";
		worker.exec_params(query, name, dauer, ort, raum);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::hinzufuegenVeranstalter(std::string email, std::string name, std::string pw, std::string admin) {
	try {
		pqxx::work worker(connectionObject);
		std::string query =
			"INSERT INTO Veranstalter (email, name, passwort, admin) VALUES ($1, $2, $3, $4);";
		worker.exec_params(query, email, name, pw, admin);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::deleteStudent(std::string id) {
	try {
		pqxx::work worker(connectionObject);
		std::string query =
			"DELETE FROM studenten WHERE ID = $1;";
		worker.exec_params(query, id);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::hinzufuegenStudent(std::string email, std::string name, std::string pw) {
	try {
		pqxx::work worker(connectionObject);
		std::string query =
			"INSERT INTO studenten (email, name, pw) VALUES ($1, $2, $3);";
		worker.exec_params(query, email, name, pw);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

std::string DBPlan::getDauer(std::string tag, std::string stunde) {
	try {
		pqxx::work worker(connectionObject);
		std::string query =
			"SELECT dauer FROM Veranstaltung WHERE ID = (SELECT Veranstaltung_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2);";

		pqxx::result response = worker.exec_params(query, stunde, tag);

		worker.commit( );

		return response[0][0].c_str( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
	return "";
}

void DBPlan::addFirstOfDayTwo(std::string tag) {
	try {
		pqxx::work worker(connectionObject);
		std::string query =
			R"(UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_ID = (SELECT ID FROM Veranstalter WHERE arbeitszeit <= 16 AND krank = FALSE LIMIT 1)
			WHERE uhrzeit_id = 1 AND tag = $1;)";
		worker.exec_params(query, tag);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::addTwoHour(std::string tag, std::string stunde) {
	try {
		std::string prevStunde = std::to_string(std::stoi(stunde) - 1);

		pqxx::work worker(connectionObject);
		std::string query =
			R"(UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_id = (SELECT ID FROM Veranstalter
			WHERE arbeitszeit <= 16 AND krank = FALSE
			AND(standort = (SELECT ort FROM Veranstaltung WHERE ID = (SELECT veranstaltung_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2))
			AND ID != (SELECT veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2))
			ORDER BY random() LIMIT 1)
			WHERE uhrzeit_id = $3 AND tag = $4;)";
		worker.exec_params(query, prevStunde, tag, stunde, tag);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::addFirstOfDayFour(std::string tag) {
	try {
		pqxx::work worker(connectionObject);
		std::string query =
			R"(UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_ID = (SELECT ID FROM Veranstalter WHERE arbeitszeit <= 14 AND krank = FALSE LIMIT 1)
			WHERE uhrzeit_id = 1 AND tag = $1;)";
		worker.exec_params(query, tag);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::addFourHour(std::string tag, std::string stunde) {
	try {
		std::string prevStunde = std::to_string(std::stoi(stunde) - 1);
		pqxx::work worker(connectionObject);
		std::string query =
			R"(UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_id = (SELECT ID FROM Veranstalter
			WHERE arbeitszeit <= 14 AND krank = FALSE
			AND(standort = (SELECT ort FROM Veranstaltung WHERE ID = (SELECT veranstaltung_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2))
			AND ID != (SELECT veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2))
			ORDER BY random() LIMIT 1)
			WHERE uhrzeit_id = $3 AND tag = $4;)";
		worker.exec_params(query, prevStunde, tag, stunde, tag);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::upperHour(std::string tag, std::string stunde) {
	try {
		std::string nextStunde = std::to_string(std::stoi(stunde) + 1);

		pqxx::work worker(connectionObject);
		std::string query =
			R"(UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_ID = (SELECT Veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2)
			WHERE uhrzeit_id = $3 AND tag = $2;)";
		worker.exec_params(query, stunde, tag, nextStunde);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::updateStandort(std::string tag, std::string stunde) {
	try {
		pqxx::work worker(connectionObject);
		std::string query =
			R"(UPDATE Veranstalter SET standort = (SELECT ort FROM Veranstaltung WHERE ID = (SELECT Veranstaltung_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2)) WHERE ID = (SELECT Veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2);)";
		worker.exec_params(query, stunde, tag);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::incarbeitszeit(std::string tag, std::string stunde, std::string amount) {
	try {
		pqxx::work worker(connectionObject);

		std::string query =
			"UPDATE Veranstalter SET arbeitszeit = arbeitszeit + $1 WHERE ID = (SELECT Veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $2 AND tag = $3);";

		worker.exec_params(query, amount, stunde, tag);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::insertVeranstaltungenIntoPlan(std::string cap, std::string tag, std::string stunde) {
	try {
		pqxx::work worker(connectionObject);
		std::string query =
			R"(INSERT INTO Veranstalter_Veranstaltung_Uhrzeit (Veranstaltung_ID, tag, uhrzeit_ID)
                SELECT ID, $1, $2 FROM Veranstaltung WHERE dauer <= $3
                ORDER BY used ASC
                LIMIT 1;)";

		worker.exec_params(query, tag, stunde, cap);
		worker.commit( );

		std::string query2 =
			R"(UPDATE Veranstaltung SET used = used+1 WHERE ID = 
                    (SELECT Veranstaltung_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE tag = $1 AND uhrzeit_id = $2); )";

		worker.exec_params(query2, tag, stunde);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::insertAgain(std::string tag, std::string stunde) {
	try {
		std::string nextStunde = std::to_string(std::stoi(stunde) + 1);

		pqxx::work worker(connectionObject);

		std::string query =
			R"(INSERT INTO Veranstalter_Veranstaltung_Uhrzeit (Veranstaltung_ID, tag, uhrzeit_ID)
                SELECT Veranstaltung_ID, $1, $2 FROM Veranstalter_Veranstaltung_Uhrzeit WHERE tag = $3 AND uhrzeit_id = $4;)";

		worker.exec_params(query, tag, nextStunde, tag, stunde);
		worker.commit( );

	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

void DBPlan::insertVeranstaltungIntoPlanHandler( ) {

	int timeDay;
	for (int i = 1; i <= 5; i++) {
		timeDay = 1;

		while (timeDay <= 5) {
			std::string tagStr = std::to_string(i);
			std::string stundeStr = std::to_string(timeDay);
			if (timeDay == 5)
				insertVeranstaltungenIntoPlan("2", tagStr, stundeStr);
			else {
				insertVeranstaltungenIntoPlan("4", tagStr, stundeStr);
				if (getDauer(tagStr, stundeStr) == "4") {
					insertAgain(tagStr, stundeStr);
					timeDay++;
				}
			}
			timeDay++;
		}
	}
}

void DBPlan::createPlan( ) {
	try {
		insertVeranstaltungIntoPlanHandler( );
		for (int tag = 1; tag < 6; tag++) {
			std::string tagStr = std::to_string(tag);
			for (int stunde = 1; stunde < 6; stunde++) {
				std::string stundeStr = std::to_string(stunde);
				//get dauer of next class
				if (std::stoi(getDauer(tagStr, stundeStr)) == 2) {
					stunde == 1 ? addFirstOfDayTwo(tagStr) : addTwoHour(tagStr, stundeStr);
					updateStandort(tagStr, stundeStr);
					incarbeitszeit(tagStr, stundeStr, "2");
				} else {
					stunde == 1 ? addFirstOfDayFour(tagStr) : addFourHour(tagStr, stundeStr);
					upperHour(tagStr, stundeStr);
					incarbeitszeit(tagStr, stundeStr, "4");
					updateStandort(tagStr, stundeStr);
					stunde++;
				}
			}
		}
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
}

std::string DBPlan::checkPlanSize( ) {
	try {
		pqxx::work worker(connectionObject);
		std::string query =
			"SELECT count(*) FROM Veranstalter_Veranstaltung_Uhrzeit;";
		pqxx::result response = worker.exec(query);
		worker.commit( );
		return response[0][0].c_str( );
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
	return "";
}

std::vector<std::string> DBPlan::getPlan( ) {
	std::vector<std::string> plan;

	try {
		if (checkPlanSize( ) == "0")
			createPlan( );

		pqxx::work worker(connectionObject);

		std::string query =
			R"(SELECT Veranstalter_Veranstaltung_Uhrzeit.tag, u.anfangszeit, u.endzeit, o.ort, o.name, v.name, o.raum, v.ID FROM Veranstalter_Veranstaltung_Uhrzeit 
			JOIN Veranstalter v ON Veranstalter_Veranstaltung_Uhrzeit.veranstalter_ID = v.ID
			JOIN Uhrzeit u ON Veranstalter_Veranstaltung_Uhrzeit.uhrzeit_ID = u.ID
			JOIN Veranstaltung o ON Veranstalter_Veranstaltung_Uhrzeit.veranstaltung_ID = o.ID 
			ORDER BY Veranstalter_Veranstaltung_Uhrzeit.tag, Veranstalter_Veranstaltung_Uhrzeit.uhrzeit_ID;)";

		pqxx::result response = worker.exec(query);
		worker.commit( );

		for (const auto& row : response) {
			std::string rowstring;
			for (const auto& col : row) {
				rowstring.append(col.c_str( ));
				rowstring.append(",");
			}
			plan.push_back(rowstring);
		}
	}
	catch (const std::exception& e) {
		fmt::println(e.what( ));
	}
	return plan;
}

void DBPlan::versendeEmails( ) {
	//Email an alle Nutzer
	fmt::println("Der Einsatzplan wurde geupdated");
}
