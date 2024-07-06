#include "DBLogin.hpp"

DBLogin::DBLogin(std::string connStr) : DBHandler(connStr) { };

int DBLogin::checkValidLogin(std::string id, std::string pw) {
	try {
		pqxx::work worker(connectionObject);

		std::string query =
			"SELECT admin FROM studenten_veranstalter WHERE id = $1 AND passwort = $2";

		pqxx::result response = worker.exec_params(query, id, pw);

		return response.affected_rows( ) > 0 ? response[0][0].as<bool>( ) : -1;
	}
	catch (const std::exception& e) {
		fmt::printf("ERROR: %s", e.what( ));
	}

	return -1;
}

