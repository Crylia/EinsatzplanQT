# include "PlanGrid.hpp"

PlanGrid::PlanGrid(QWidget* parent) 
:QWidget(parent) 
{
	setObjectName("PlanGrid");
	setStyleSheet(R"(
	QWidget{
		background-color: #313131;
		border: 2px solid #414141;
	}
	)");

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

	gridLayout = new QGridLayout(this);

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 10; ++j) {
			planMap->insert(qMakePair(weekdays[i], times[j]), nullptr);
		}
	}

	QLabel* temp = new QLabel();
	temp->setFixedSize(124,100);
	gridLayout->addWidget(temp, 0, 0);

	for (int i = 0; i < 5; i++) {
		QLabel* temp = new QLabel(weekdays[i]);
		temp->setFixedSize(250,80);
		temp->setObjectName("temp");
		temp->setStyleSheet(R"(
		#temp{
			font-size: 24px;
			font-weight: bold;
			color: #d8d8d8
		}
		)");
		gridLayout->addWidget(temp, 0, i+1,Qt::AlignCenter);
	}
	for (int i = 0; i < 10; i++) {
		QLabel* temp = new QLabel(times[i]);
		temp->setFixedSize(124,50);
		temp->setObjectName("temp");
		temp->setStyleSheet(R"(
		#temp{
			font-size: 16px;
			font-weight: bold;
			color: #d8d8d8
		}
		)");
		gridLayout->addWidget(temp, i+1, 0, Qt::AlignCenter);
	}

	setLayout(gridLayout);
}
