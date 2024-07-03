# include "PlanGridController.hpp"

PlanGridController::PlanGridController(){
    weekdays[0] = "Montag";
	weekdays[1] = "Dienstag";
	weekdays[2] = "Mittwoch";
	weekdays[3] = "Donnerstag";
	weekdays[4] = "Freitag";

	times[0] = "8:00 - 9:00";
	times[1] = "9:00 - 10:00";
	times[2] = "10:00 - 11:00";
	times[3] = "11:00 - 12:00";
	times[4] = "12:00 - 13:00";
	times[5] = "13:00 - 14:00";
	times[6] = "14:00 - 15:00";
	times[7] = "15:00 - 16:00";
	times[8] = "16:00 - 17:00";
	times[9] = "17:00 - 18:00";

    planMap = new QMap<QPair<QString, QString>, QLabel*>();
}

QMap<QPair<QString, QString>, QLabel*> PlanGridController::getVeranstaltungen(){
    //DatabaseHandler db = new DatabaseHandler();
    //db.executeQuery("");
}
