#include "DBHandler.hpp"

DBHandler::DBHandler(std::string connStr) :
	connectionObject(connStr.c_str( )) {
	try {
		if (connectionObject.is_open( ))
			fmt::print("Databased connected");
		else
			fmt::print("Failed to connect to Databased");
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
};

void DBHandler::deleteVeranstalter(std::string id){
	try {
		pqxx::work worker(connectionObject);
		std::string query =  fmt::format("DELETE FROM Student WHERE id = {0}",id);
		worker.exec(query);
		worker.commit();
		query = fmt::format("DELETE FROM Veranstalter WHERE id = {0}",id);
		worker.exec_params(query);
		worker.commit();
		fmt::print("Veranstalter with ID {} deleted successfully.\n", id);
	}
	catch (const std::exception& e) {
		fmt::print("ERROR: {0}", e.what( ));
	}
}

void DBHandler::deleteVeranstaltung(std::string name) {
    try {
        pqxx::work worker(connectionObject);
        std::string query = fmt::format("DELETE FROM Veranstaltung WHERE name = '{0}'", name);
        worker.exec(query);
        worker.commit();
        fmt::print("Veranstaltung with name '{}' deleted successfully.\n", name);
    } catch (const std::exception& e) {
        fmt::print(stderr, "Error deleting Veranstaltung: {}\n", e.what());
    }
}

void DBHandler::createVeranstalter(std::string email, std::string name, std::string passwort, std::string admin) {
    try {
        pqxx::work worker(connectionObject);
        std::string query = fmt::format(
            "INSERT INTO Veranstalter (email, name, passwort, admin) VALUES ('{}', '{}', '{}', {})",
            email, name, passwort, admin
        );
        worker.exec(query);
        worker.commit();
        fmt::print("Veranstalter {} created successfully.\n", name);
    } catch (const std::exception& e) {
        fmt::print(stderr, "Error creating Veranstalter: {}\n", e.what());
    }
}

void DBHandler::createVeranstaltung(std::string name, std::string uhrzeit, std::string standort, std::string raum) {
    try {
        pqxx::work worker(connectionObject);
        std::string query = fmt::format(
            "INSERT INTO Veranstaltung (name, uhrzeit, standort, raum) VALUES ('{}', '{}', '{}', '{}')",
            name, uhrzeit, standort, raum
        );
        worker.exec(query);
        worker.commit();
        fmt::print("Veranstaltung {} created successfully.\n", name);
    } catch (const std::exception& e) {
        fmt::print(stderr, "Error creating Veranstaltung: {}\n", e.what());
    }
}

void DBHandler::createEinsatzplan() {
    try {
        pqxx::work worker(connectionObject);

        // Fetch all Veranstaltungen
        pqxx::result veranstaltungen = worker.exec("SELECT ID, dauer, used FROM Veranstaltung");

        // Fetch all available Uhrzeiten
        std::vector<int> uhrzeiten = {1, 2, 3, 4, 5};  // Representing 1 to 5 time slots

        // Fetch all available Veranstalter
        pqxx::result veranstalter = worker.exec("SELECT ID FROM Veranstalter");

        std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));  // Random number generator
        std::uniform_int_distribution<int> day_dist(1, 5);  // Random days between 1 and 5 (Monday to Friday)
        
        for (auto row : veranstaltungen) {
            int veranstaltungID = row["id"].as<int>();
            int dauer = row["dauer"].as<int>();
            int used = row["used"].as<int>();

            while (used < dauer) {
                // Randomly select a day
                int day = day_dist(rng);

                // Randomly select a Uhrzeit
                std::uniform_int_distribution<int> uhrzeit_dist(0, uhrzeiten.size() - 1);
                int uhrzeitIndex = uhrzeit_dist(rng);
                int uhrzeitID = uhrzeiten[uhrzeitIndex];

                // Randomly select a Veranstalter
                std::uniform_int_distribution<int> veranstalter_dist(0, veranstalter.size() - 1);
                int veranstalterIndex = veranstalter_dist(rng);
                int veranstalterID = veranstalter[veranstalterIndex]["id"].as<int>();

                // Check if the selected Veranstalter is valid for the selected time and location
                std::string checkQuery = fmt::format(
                    "SELECT COUNT(*) FROM StundenImPlan sip "
                    "JOIN Veranstaltung v ON sip.veranstaltung_ID = v.ID "
                    "WHERE sip.tag = {} AND (sip.uhrzeit_ID = {} OR sip.uhrzeit_ID = {} - 1) "
                    "AND v.ort != (SELECT ort FROM Veranstaltung WHERE ID = {}) "
                    "AND sip.veranstalter_ID = {}",
                    day, uhrzeitID, uhrzeitID, veranstaltungID, veranstalterID);
                pqxx::result checkResult = worker.exec(checkQuery);
                int count = checkResult[0][0].as<int>();

                if (count == 0) {
                    // Assign to StundenImPlan
                    std::string query = fmt::format(
                        "INSERT INTO StundenImPlan (uhrzeit_ID, tag, veranstalter_ID, veranstaltung_ID) VALUES ({}, {}, {}, {})",
                        uhrzeitID, day, veranstalterID, veranstaltungID
                    );
                    worker.exec(query);

                    // Update used count
                    used += 2;
                    std::string updateQuery = fmt::format(
                        "UPDATE Veranstaltung SET used = {} WHERE ID = {}",
                        used, veranstaltungID
                    );
                    worker.exec(updateQuery);
                }
            }
        }

        worker.commit();
        fmt::print("Random schedule assigned successfully.\n");
    } catch (const std::exception& e) {
        fmt::print(stderr, "Error assigning random schedule: {}\n", e.what());
    }
}


std::vector<std::string> DBHandler::getVeranstaltung() {
    std::vector<std::string> results;

    try {
        pqxx::work txn(connectionObject);

        // Check if StundenImPlan is empty
        std::string checkQuery = "SELECT COUNT(*) FROM StundenImPlan";
        pqxx::result countResult = txn.exec(checkQuery);
        int count = countResult[0][0].as<int>();

        if (count == 0) {
            createEinsatzplan();
        }

        // Fetch data from StundenImPlan
        pqxx::result stundenImPlanResult = txn.exec(
            "SELECT sip.tag, u.anfangszeit, u.endzeit, v.ort, v.name AS veranstaltungsname, "
            "a.name AS veranstaltername, v.raum, sip.veranstalter_ID "
            "FROM StundenImPlan sip "
            "JOIN Uhrzeit u ON sip.uhrzeit_ID = u.ID "
            "JOIN Veranstaltung v ON sip.veranstaltung_ID = v.ID "
            "JOIN Veranstalter a ON sip.veranstalter_ID = a.ID"
        );

        // Format the results
        for (const auto &row : stundenImPlanResult) {
            std::string result = fmt::format("{},{},{},{},{},{},{},{}",
                                             row["tag"].as<int>(),
                                             row["anfangszeit"].as<std::string>(),
                                             row["endzeit"].as<std::string>(),
                                             row["ort"].as<std::string>(),
                                             row["veranstaltungsname"].as<std::string>(),
                                             row["veranstaltername"].as<std::string>(),
                                             row["raum"].as<std::string>(),
                                             row["veranstalter_id"].as<int>());
            results.push_back(result);
        }

    } catch (const std::exception& e) {
        fmt::print(stderr, "Error retrieving Veranstaltung data: {}\n", e.what());
    }

    return results;
}

void DBHandler::meldeKrank(std::string id, std::string tag, std::string stunde){
	try {
		pqxx::work worker(connectionObject);
		std::string query =  fmt::format("Update StundeImPlan SET veranstalter_ID = NULL WHERE veranstalter_ID = {0}",id);
		worker.exec(query);
		worker.commit();
		fmt::print("Veranstalter with ID {} marked ill successfully.\n", id);
	}
	catch (const std::exception& e) {
		fmt::print("ERROR: {0}", e.what( ));
	}
}