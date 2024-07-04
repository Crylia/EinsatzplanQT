#ifndef _DBPLAN_HPP_
#define _DBPLAN_HPP_


#include "DBHandler.hpp"
#include <iostream>
#include <vector>

class DBPlan : public DBHandler {
private:
	std::string getDauer(std::string tag, std::string stunde);
	void addFirstOfDayTwo(std::string tag);
	void addTwoHour(std::string tag, std::string stunde);
	void addFirstOfDayFour(std::string tag);
	void upperHour(std::string tag, std::string stunde);
	void addFourHour(std::string tag, std::string stunde);

	void updateStandort(std::string tag, std::string stunde);
public:
	DBPlan(std::string connStr);
	void meldeKrank(std::string id, std::string zeit);
	void meldeGesund(std::string id);
	void deleteVeranstaltung(std::string id);
	void hinzufuegenVeranstaltung(std::string name, std::string dauer, std::string ort, std::string raum);


	void deleteVeranstalter(std::string id);
	void hinzufuegenVeranstalter(std::string email, std::string name, std::string pw, std::string admin);
	

	void deleteStudent(std::string id);
	void hinzufuegenStudent(std::string email, std::string name, std::string pw);
	

	void createPlan();
	void incarbeitszeit(std::string tag, std::string stunde, std::string amount);


	void clear();

};

#endif
