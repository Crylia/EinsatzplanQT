#pragma once

#include <pqxx/pqxx>
#include <string>
#include <fmt/core.h>
#include <random>
#include <ctime>

class DBHandler {
private:
	std::unique_ptr<pqxx::connection> m_dbConnection;

public:
	DBHandler(const std::string& connStr);

	/**
	 * @brief Tries to login the user
	 * @param id user id
	 * @param pw user password
	 * @return returns 1 if admin and 0 if not
	 */
	int tryAuthenticate(std::string id, std::string pw);

	bool createVeranstalter(const std::string& name, const std::string& email, const std::string& password, bool admin);
	bool deleteVeranstalter(int id);
	bool deleteVeranstalter(const std::string& name);

	bool createVeranstaltung(const std::string& name, const std::string& campus, const std::string& time, const std::string& veranstalter);
	bool deleteVeranstaltung(const std::string& name);

	bool krankmelden(const std::string& veranstalter, const std::string& uhrzeit, int tag);

	std::vector<std::string> getPlan( );
};
