#include "DBHandler.hpp"

DBHandler::DBHandler(const std::string& connStr) :
	m_dbConnection(std::make_unique<pqxx::connection>(connStr.c_str( ))) {
	try {
		m_dbConnection->is_open( ) ?
			fmt::print("Databased connected") :
			fmt::print("Failed to connect to Databased");
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
};

int DBHandler::tryAuthenticate(std::string id, std::string pw) {
	try {
		pqxx::work W(*m_dbConnection.get( ));

		std::string query =
			"SELECT admin FROM veranstalter WHERE id = $1 AND passwort = $2";

		pqxx::result response = W.exec_params(query, id, pw);

		return response.affected_rows( ) > 0 ? response[0][0].as<bool>( ) : -1;
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}

	return -1;
}

bool DBHandler::createVeranstalter(const std::string& name, const std::string& email, const std::string& password, bool admin) {
	try {
		pqxx::work W(*m_dbConnection.get( ));
		std::string admin_value = admin ? "TRUE" : "FALSE";
		std::string query = fmt::format(
			"INSERT INTO Veranstalter (name, email, passwort, admin) VALUES ({}, {}, {}, {})",
			W.quote(name), W.quote(email), W.quote(password), admin_value
		);
		W.exec(query);
		W.commit( );
		return true;
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
		return false;
	}
}

bool DBHandler::deleteVeranstalter(int id) {
	try {
		pqxx::work W(*m_dbConnection.get( ));
		std::string query = fmt::format(
			"DELETE FROM Veranstalter WHERE ID = {}", W.quote(id)
		);
		W.exec(query);
		W.commit( );
		return true;
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
		return false;
	}
}

bool DBHandler::deleteVeranstalter(const std::string& name) {
	try {
		pqxx::work W(*m_dbConnection.get( ));
		std::string query = fmt::format(
			"DELETE FROM Veranstalter WHERE id = {}", W.quote(name)
		);
		W.exec(query);
		W.commit( );
		return true;
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
		return false;
	}
}

bool DBHandler::createVeranstaltung(const std::string& name, const std::string& campus, const std::string& raum, const std::string& dauer) {
	try {
		pqxx::work W(*m_dbConnection.get( ));
		std::string cmp(1, campus.back( ));
		std::string query = fmt::format(
			"INSERT INTO Veranstaltung (name, ort, raum, dauer) VALUES ({}, {}, {}, {})",
			W.quote(name), W.quote(cmp), W.quote(raum), W.quote(dauer)
		);
		fmt::println(query);
		W.exec(query);
		W.commit( );
		return true;
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
		return false;
	}
}

bool DBHandler::deleteVeranstaltung(const std::string& name) {
	try {
		pqxx::work W(*m_dbConnection.get( ));
		std::string query = fmt::format(
			"DELETE FROM Veranstaltung WHERE name = {}", W.quote(name)
		);
		W.exec(query);
		W.commit( );
		return true;
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
		return false;
	}
}

bool DBHandler::krankmelden(const std::string& veranstalter, const std::string& uhrzeit, int tag) {
	try {
		pqxx::work W(*m_dbConnection.get( ));
		std::string query =
			"INSERT INTO Krank (stundeImPlan_uhrzeit, stundeImPlan_tag, veranstalter, krank) "
			"SELECT SIP.uhrzeit, SIP.tag, V.ID, TRUE "
			"FROM StundeImPlan SIP "
			"JOIN Veranstalter V ON SIP.veranstalter = V.ID "
			"JOIN Uhrzeit U ON SIP.uhrzeit = U.ID "
			"JOIN Veranstaltung VA ON SIP.veranstaltung = VA.name "
			"WHERE V.id = " + W.quote(veranstalter) +
			" AND U.anfangszeit = " + W.quote(std::string(uhrzeit + ":00")) +
			" AND SIP.tag = " + W.quote(tag) + ";";

		W.exec(query);
		W.commit( );
		return true;
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
		return false;
	}
}

std::vector<std::string> DBHandler::getPlan( ) {
	std::vector<std::string> plan;
	try {
		pqxx::nontransaction N(*m_dbConnection.get( ));
		std::string query =
			R"(SELECT SIP.tag, U.anfangszeit, U.endzeit, VA.ort, VA.name AS veranstaltungsname, V.name AS veranstaltername, VA.raum, SIP.veranstalter, VA.dauer
        FROM StundeImPlan SIP
        JOIN Uhrzeit U ON SIP.uhrzeit = U.ID
        JOIN Veranstaltung VA ON SIP.veranstaltung = VA.name
        LEFT JOIN Veranstalter V ON SIP.veranstalter = V.ID
        ORDER BY U.anfangszeit)";
		pqxx::result R(N.exec(query));

		for (auto row : R) {
			std::string entry = fmt::format(
				"{},{},{},{},{},{},{},{},{}",
				row["tag"].c_str( ), row["anfangszeit"].c_str( ), row["endzeit"].c_str( ), row["ort"].c_str( ),
				row["veranstaltungsname"].c_str( ), row["veranstaltername"].is_null( ) ? "frei" : row["veranstaltername"].c_str( ), row["raum"].c_str( ), row["veranstalter"].c_str( ), row["dauer"].c_str( )
			);
			plan.push_back(entry);
		}
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
	return plan;
}
