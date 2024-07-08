#pragma once

#include <vector>
#include <fmt/core.h>
#include <fmt/printf.h>

#include "../DBHandler/DBHandler.hpp"



class DBPlan : public DBHandler {
private:
	//Functions needed for creation and updating of the plan
	std::string getDauer(std::string tag, std::string stunde);
	void addFirstOfDayTwo(std::string tag);
	void addTwoHour(std::string tag, std::string stunde);
	void addFirstOfDayFour(std::string tag);
	void upperHour(std::string tag, std::string stunde);
	void addFourHour(std::string tag, std::string stunde);
	void vertretung(std::string tag, std::string stunde);
	void deleteVeranstalterForeign(std::string id);
	void updateStandort(std::string tag, std::string stunde);
	void incarbeitszeit(std::string tag, std::string stunde, std::string amount);
	void insertVeranstaltungenIntoPlan(std::string cap, std::string tag, std::string stunde);
	void insertVeranstaltungIntoPlanHandler( );
	void insertAgain(std::string tag, std::string stunde);
	std::string checkPlanSize( );
	void versendeEmails( );

public:
	DBPlan(std::string connStr);

	/**
	 * @brief Deletes prof from plan and searches new one
	 *
	 * @param id
	 * @param tag
	 * @param stunde
	 */
	void meldeKrank(std::string id, std::string tag, std::string stunde);

	/**
	 * @brief Currently directly used after meldeKrank, so Mitarbeiter is only sick for specific hour
	 *
	 * @param id
	 */
	//void meldeGesund(std::string tag, std::string stunde);

	/**
	 * @brief Deletes Veranstaltung from relation Veranstaltung and from Einsatzplan
	 *
	 * @param id
	 */
	void deleteVeranstaltung(std::string name);

	/**
	 * @brief Adds Veranstaltung to relation Veranstaltung
	 *
	 * @param name
	 * @param dauer
	 * @param ort
	 * @param raum
	 */
	void hinzufuegenVeranstaltung(std::string name, std::string dauer, std::string ort, std::string raum);

	/**
	 * @brief Deletes Veranstlater from relattion Veranstalter and from Einsatzplan
	 *
	 * @param id
	 */
	void deleteVeranstalter(std::string id);

	/**
	 * @brief Add Veranstalter to relation Veranstalter
	 *
	 * @param email
	 * @param name
	 * @param pw
	 * @param admin
	 */
	void hinzufuegenVeranstalter(std::string email, std::string name, std::string pw, std::string admin);

	/**
	 * @brief Deletes a student from the database
	 *
	 * @param id
	 */
	void deleteStudent(std::string id);

	/**
	 * @brief Adds a new student
	 *
	 * @param email
	 * @param name
	 * @param pw
	 */
	void hinzufuegenStudent(std::string email, std::string name, std::string pw);

	/**
	 * @brief Create a Plan object
	 *
	 */
	void createPlan( );

	/**
	 * @brief Each string in form of (tag , anfangszeit , endzeit , Ort , Veranstaltung , Mitarbeiter , mitarbeiterID , )
	 *
	 * @return std::vector<std::string>
	 */

	std::vector<std::string> getPlan( );
};

