#include "PlanGridController.hpp"

PlanGridController::PlanGridController( ) {
	weekdays[0] = "Montag";
	weekdays[1] = "Dienstag";
	weekdays[2] = "Mittwoch";
	weekdays[3] = "Donnerstag";
	weekdays[4] = "Freitag";

	times[0] = "08:00";
	times[1] = "10:00";
	times[2] = "12:00";
	times[3] = "14:00";
	times[4] = "16:00";

	planMap = new QMap<QPair<QString, QString>, QWidget*>( );

	const std::map<std::string, std::string> config = load_config("../config.cfg");

	m_connectionString = fmt::format(
		"host={} port={} dbname={} user={} password={}",
		config.at("DB_HOST"),
		config.at("DB_PORT"),
		config.at("DB_NAME"),
		config.at("DB_USER"),
		config.at("DB_PASSWORD")
	);
}

QMap<QPair<QString, QString>, QWidget*>* PlanGridController::getVeranstaltungen( ) {
	DBPlan* db = new DBPlan(m_connectionString);

	// stringFormat = tag , anfangszeit , Ort , Veranstaltung , Mitarbeiter , mitarbeiterID
	std::vector<std::string> planData = db->getPlan( );

	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j) {
			QLabel* temp = new QLabel( );
			temp->setObjectName("temp");
			temp->setStyleSheet(R"(
					#temp{
						background-color: #313131;
					}
				)");
			temp->setFixedSize(240, 100);
			planMap->insert(qMakePair(weekdays[i], times[j]), temp);
		}

	std::string color;

	for (const auto& veranstaltung : planData) {

		std::vector<std::string> infoVector;
		std::stringstream ss(veranstaltung);
		std::string str;

		while (std::getline(ss, str, ','))
			infoVector.push_back(str);

		//Wochentag, Uhrzeit,Uhrzeitende, Campus, Veranstaltung, ProfName,raum, veranstaltungs dauer
		QFrame* container = new QFrame( );

		container->setObjectName("container");
		container->setStyleSheet(R"(
			#container{
				background-color: #313131;
			}
		)");
		auto layout = new QVBoxLayout(container);
		container->setLayout(layout);

		QPushButton* widget = new QPushButton(QString::fromStdString(infoVector.at(4) + " - " + infoVector.at(5) + "\n" + infoVector.at(3) + infoVector.at(6)));
		layout->addWidget(widget);
		//widget->setAlignment(Qt::AlignCenter);
		widget->setObjectName("widget");
		widget->setFixedSize(210, 70);
		layout->setAlignment(Qt::AlignCenter);
		connect(widget, &QPushButton::clicked, this, [infoVector]( ) {
			fmt::print("clicked on " + infoVector.at(4) + '\n');
			});

		if (infoVector.at(4) == "THI") {
			color = "#9FA8DA";
		} else if (infoVector.at(4) == "DBS") {
			color = "#EF9A9A";
		} else if (infoVector.at(4) == "WIN") {
			color = "#FFCC80";
		} else if (infoVector.at(4) == "ALD") {
			color = "#E6EE9C";
		} else if (infoVector.at(4) == "GDI") {
			color = "#90CAF9";
		} else if (infoVector.at(4) == "BSY") {
			color = "#FFF59D";
		} else if (infoVector.at(4) == "ITS") {
			color = "#9FA8DA";
		} else if (infoVector.at(4) == "WEB") {
			color = "#A5D6A7";
		} else if (infoVector.at(4) == "BVA") {
			color = "#80CBC4";
		} else if (infoVector.at(4) == "SWE") {
			color = "#80DEEA";
		} else {
			color = "#313131";
		}

		widget->setStyleSheet(QString::fromStdString(R"(
			#widget{
				border: 0px solid #313131;
				background-color: )" + color + R"(;
				color: #212121;
				font-weight: 900;
				font-size: 18px;
				border-radius: 8px;
			}
		)"));

		container->setFixedSize(240, 100);
		planMap->insert(qMakePair(
			weekdays[std::stoi(infoVector.at(0)) - 1],
			QString::fromStdString(infoVector.at(1).erase(5, 8))),
			container);
	}

	return planMap;
}
