# include "PlanGrid.hpp"

PlanGrid::PlanGrid(QWidget* parent) :
	QWidget(parent) {

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


	planMap = new QMap<QPair<QString, QString>, QLabel*>( );

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 10; ++j) {
			planMap->insert(qMakePair(weekdays[i], times[j]), nullptr);
		}
	}

	for (int i = 1; i <= 5; i++) {
		gridLayout->addWidget(new QLabel(weekdays[i]), 0, i);
	}
	for (int i = 0; i < 10; i++) {
		gridLayout->addWidget(new QLabel(times[i]), i, 0);
	}


	setLayout(gridLayout);
}
