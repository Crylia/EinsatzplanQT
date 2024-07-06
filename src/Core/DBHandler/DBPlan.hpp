#ifndef _DBPLAN_HPP_
#define _DBPLAN_HPP_


#include "DBHandler.hpp"
#include <iostream>
#include <vector>

class DBPlan : public DBHandler {
private:
	//Functions needed for creation and updating of the plan
	std::string getDauer(std::string tag, std::string stunde);
	void addFirstOfDayTwo(std::string tag);
	void addTwoHour(std::string tag, std::string stunde);
	void addFirstOfDayFour(std::string tag);
	void upperHour(std::string tag, std::string stunde);
	void addFourHour(std::string tag, std::string stunde);
	void sucheVertretung(std::string tag, std::string stunde);
	void vertretung(std::string tag, std::string stunde, std::string dauer);
	void deleteVeranstalterForeign(std::string id);
	void deleteVeranstaltungForeign(std::string id);
	void updateStandort(std::string tag, std::string stunde);
	void incarbeitszeit(std::string tag, std::string stunde, std::string amount);
	void versendeEmails();
public:
	DBPlan(std::string connStr);

	//deletes prof from plan and searches new one
	void meldeKrank(std::string id, std::string tag, std::string stunde);
	//currently directly used after meldeKrank, so Mitarbeiter is only sick for specific hour
	void meldeGesund(std::string id);

	//Deletes Veranstaltung from relation Veranstaltung and from Einsatzplan
	void deleteVeranstaltung(std::string id);
	//Adds Veranstaltung to relation Veranstaltung
	void hinzufuegenVeranstaltung(std::string name, std::string dauer, std::string ort, std::string raum);
	
	//Deletes Veranstlater from relattion Veranstalter and from Einsatzplan
	void deleteVeranstalter(std::string id);
	//Add Veranstalter to relation Veranstalter
	void hinzufuegenVeranstalter(std::string email, std::string name, std::string pw, std::string admin);
	
	
	void deleteStudent(std::string id);
	void hinzufuegenStudent(std::string email, std::string name, std::string pw);
	
	
	void createPlan();

	//Each string in form of (tag , anfangszeit , endzeit , Ort , Veranstaltung , Mitarbeiter , mitarbeiterID , )  
	std::vector<std::string> getPlan();



};

#endif