#include "DBPlan.hpp"

DBPlan::DBPlan(std::string connStr) : DBHandler(connStr) { };

void DBPlan::vertretung(std::string tag, std::string stunde, std::string dauer) {
	try {
		std::string prevStunde = std::to_string(std::stoi(stunde) - 1);
		std::string cap = std::to_string(18 - std::stoi(dauer));
		std::string nextStunde;
		std::string nextTag = tag;
		std::string prevTag = tag;
		if (dauer == "4")
			nextStunde = std::to_string(std::stoi(stunde) + 2);
		else
			nextStunde = std::to_string(std::stoi(stunde) + 1);

		if (prevStunde == "0") {
			prevStunde = "5";
			prevTag = std::to_string(std::stoi(tag) - 1);
			if (prevTag == "0")
				prevTag = "5";
		}

		if (nextStunde == "6") {
			nextStunde = "1";
			nextTag = std::to_string(std::stoi(tag) + 1);
			if (nextTag == "6")
				nextTag = "1";
		}

		pqxx::work worker(connectionObject);

		std::string query = R"(
			UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_ID =
			(SELECT ID FROM Veranstalter WHERE ID != (SELECT Veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2)
			AND ID != (SELECT Veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $3 AND tag = $4) LIMIT 1) WHERE uhrzeit_id = $5 AND tag = $6; )";

		worker.exec_params(query, prevStunde, prevTag, nextStunde, nextTag, stunde, tag);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
}

void DBPlan::sucheVertretung(std::string tag, std::string stunde) {
	std::string dauer = getDauer(tag, stunde);
	vertretung(tag, stunde, dauer);
	incarbeitszeit(tag, stunde, dauer);

	if (dauer == "4")
		upperHour(tag, stunde);
}

void DBPlan::meldeKrank(std::string id, std::string tag, std::string stunde) {
	try {
		pqxx::work worker(connectionObject);

		worker.exec_params("UPDATE Veranstalter SET krank = TRUE WHERE ID = $1", id);
		worker.commit( );

		sucheVertretung(tag, stunde);
		meldeGesund(id);
		versendeEmails( );
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
}

void DBPlan::meldeGesund(std::string id) {
	try {
		pqxx::work worker(connectionObject);

		worker.exec_params("UPDATE Veranstalter SET krank = FALSE WHERE ID = $1", id);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
}

void DBPlan::deleteVeranstalterForeign(std::string id) {
	try {
		pqxx::work worker(connectionObject);

		worker.exec_params("UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_ID = NULL WHERE Veranstalter_ID = $1;", id);
		worker.commit( );
		versendeEmails( );
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
}

void DBPlan::deleteVeranstalter(std::string id) {
	try {
		deleteVeranstalterForeign(id);

		pqxx::work worker(connectionObject);

		worker.exec_params("DELETE FROM Veranstalter WHERE ID = $1;", id);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
}

void DBPlan::deleteVeranstaltungForeign(std::string name) {
	try {
		pqxx::work worker(connectionObject);

		worker.exec_params("DELETE FROM Veranstalter_Veranstaltung_Uhrzeit WHERE Veranstaltung_ID = (SELECT ID FROM Veranstaltung WHERE name = '$1');", name);
		worker.commit( );

		versendeEmails( );
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
}

void DBPlan::deleteVeranstaltung(std::string id) {
	try {
		//deleteVeranstaltungForeign(id);

		pqxx::work worker(connectionObject);

		worker.exec_params("DELETE FROM Veranstaltung WHERE name = $1;", id);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
}

void DBPlan::hinzufuegenVeranstaltung(std::string name, std::string dauer, std::string ort, std::string raum) {
	try {
		pqxx::work worker(connectionObject);
		worker.exec_params("INSERT INTO Veranstaltung (name, dauer, ort, raum) VALUES ($1, $2, $3, $4);", name, dauer, ort, raum);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
}

void DBPlan::hinzufuegenVeranstalter(std::string email, std::string name, std::string pw, std::string admin) {
	try {
		pqxx::work worker(connectionObject);

		worker.exec_params("INSERT INTO Veranstalter (email, name, passwort, admin) VALUES ($1, $2, $3, $4);", email, name, pw, admin);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
}

void DBPlan::deleteStudent(std::string id) {
	try {
		pqxx::work worker(connectionObject);

		worker.exec_params("DELETE FROM studenten WHERE ID = $1;", id);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
}

void DBPlan::hinzufuegenStudent(std::string email, std::string name, std::string pw) {
	try {
		pqxx::work worker(connectionObject);

		worker.exec_params("INSERT INTO studenten (email, name, pw) VALUES ($1, $2, $3);", email, name, pw);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
}

std::string DBPlan::getDauer(std::string tag, std::string stunde) {
	try {
		pqxx::work worker(connectionObject);

		pqxx::result response = worker.exec_params(
			"SELECT dauer FROM Veranstaltung WHERE ID = (SELECT Veranstaltung_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2);",
			stunde,
			tag
		);

		worker.commit( );
		return response[0][0].c_str( );
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
	return "0";
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
		fmt::print(e.what( ));
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
		fmt::print(e.what( ));
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
		fmt::print(e.what( ));
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
		fmt::print(e.what( ));
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
		fmt::print(e.what( ));
	}
}

void DBPlan::updateStandort(std::string tag, std::string stunde) {
	try {
		pqxx::work worker(connectionObject);
		std::string query =
			"UPDATE Veranstalter SET standort = (SELECT ort FROM Veranstaltung WHERE ID = (SELECT Veranstaltung_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2)) WHERE ID = (SELECT Veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2);";
		worker.exec_params(query, stunde, tag);
		worker.commit( );
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
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
		fmt::print(e.what( ));
	}
}

void DBPlan::createPlan( ) {
	try {
		for (int tag = 1; tag < 6; tag++) {
			std::string tagStr = std::to_string(tag);
			for (int stunde = 1; stunde < 6; stunde++) {
				std::string stundeStr = std::to_string(stunde);

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
		fmt::print(e.what( ));
	}
}

std::vector<std::string> DBPlan::getPlan( ) {
	createPlan( );
	try {
		std::vector<std::string> plan;

		pqxx::work worker(connectionObject);

		std::string query =
			R"(SELECT tag, u.anfangszeit, u.endzeit, o.ort, o.name, v.name, o.raum, v.ID FROM Veranstalter_Veranstaltung_Uhrzeit 
			JOIN Veranstalter v ON Veranstalter_Veranstaltung_Uhrzeit.veranstalter_ID = v.ID
			JOIN Uhrzeit u ON Veranstalter_Veranstaltung_Uhrzeit.uhrzeit_ID = u.ID
			JOIN Veranstaltung o ON Veranstalter_Veranstaltung_Uhrzeit.veranstaltung_ID = o.ID 
			ORDER BY tag, uhrzeit_ID;)";

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
		return plan;
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
	return std::vector<std::string>{ "" };
}

void DBPlan::versendeEmails( ) {
	fmt::print("Der Einsatzplan wurde geändert");
}
