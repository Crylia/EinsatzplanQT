#pragma once

#include <pqxx/pqxx>
#include <string>
#include <fmt/core.h>
#include <random>
#include <ctime>

class DBHandler {
protected:
	pqxx::connection connectionObject;

	void createEinsatzplan();
public:
	DBHandler(std::string connStr);
	void deleteVeranstalter(std::string id);
	void deleteVeranstaltung(std::string name);
	void createVeranstalter(std::string email, std::string name, std::string passwort, std::string admin);
	void createVeranstaltung(std::string name, std::string uhrzeit, std::string standort, std::string raum);
	std::vector<std::string> getVeranstaltung();
	void meldeKrank(std::string id, std::string tag, std::string stunde);
};
