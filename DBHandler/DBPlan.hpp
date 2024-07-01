#ifndef _DBPLAN_HPP_
#define _DBPLAN_HPP_


#include "DBHandler.hpp"
#include <iostream>
#include <vector>

class DBPlan : public DBHandler {
public:
	DBPlan(std::string connStr);
	void meldeKrank(int id);
	void meldeGesund(int id);
	void deleteVeranstaltung(int id);
	void hinzufuegenVeranstaltung(); //Zu Liste mit Veranstaltungen oder direkt in den Einsatzplan?


	void deleteVeranstalter(int id);
	void hinzufuegenVeranstalter(std::string email, std::string name, std::string pw, bool admin);
	std::vector < std::vector<std::string>> getVeranstalter();

	void deleteStudent(int id);
	void hinzufuegenStudent(std::string email, std::string name, std::string pw);
	std::vector < std::vector<std::string>> getStudenten();

};

#endif
