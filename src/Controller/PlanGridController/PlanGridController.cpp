# include "PlanGridController.hpp"

PlanGridController::PlanGridController(){
    weekdays[0] = "Montag";
	weekdays[1] = "Dienstag";
	weekdays[2] = "Mittwoch";
	weekdays[3] = "Donnerstag";
	weekdays[4] = "Freitag";

	times[0] = "8:00 - 10:00";
	times[1] = "10:00 - 12:00";
	times[2] = "12:00 - 14:00";
	times[3] = "14:00 - 16:00";
	times[4] = "16:00 - 18:00";

    planMap = new QMap<QPair<QString, QString>, QLabel*>();
}

QMap<QPair<QString, QString>, QLabel*>* PlanGridController::getVeranstaltungen(){
	DBPlan* db = new DBPlan();

	// stringFormat = tag , anfangszeit , Ort , Veranstaltung , Mitarbeiter , mitarbeiterID
	std::vector<std::string> planData = db->getPlan();

	QString tag;
	QString anfang;
	QString ort;
	QString name;
	QString mitarbeiter;
	QString mitarbeiterId;
	std::string temp;
	for (const auto& veranstaltung:planData){
		std::istringstream f(veranstaltung);
		std::getline(f,temp,',');
		tag.fromStdString(temp);
		std::getline(f,temp,',');
		anfang.fromStdString(temp);
		std::getline(f,temp,',');
		ort.fromStdString(temp);
		std::getline(f,temp,',');
		name.fromStdString(temp);
		std::getline(f,temp,',');
		mitarbeiter.fromStdString(temp);
		std::getline(f,temp,',');
		mitarbeiterId.fromStdString(temp);

		QLabel* temp = new QLabel(name + "\n" + mitarbeiter + "\n" + ort);
			temp->setObjectName("temp");
			temp->setStyleSheet(R"(
			#temp{
				
			}
			)");
			temp->setFixedSize(240, 100);
			planMap->insert(qMakePair(tag, anfang), temp);
	}
	
	return planMap;

    //DatabaseHandler db = new DatabaseHandler();
    //db.ex
}
