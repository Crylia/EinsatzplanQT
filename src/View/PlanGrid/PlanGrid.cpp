# include "PlanGrid.hpp"

PlanGrid::PlanGrid(QWidget* parent)
	:QWidget(parent) {
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

	times[0] = "8:00 - 10:00";
	times[1] = "10:00 - 12:00";
	times[2] = "12:00 - 14:00";
	times[3] = "14:00 - 16:00";
	times[4] = "16:00 - 18:00";



	planMap = new QMap<QPair<QString, QString>, QLabel*>( );

	gridLayout = new QGridLayout(this);

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			QLabel* temp = new QLabel();
			temp->setObjectName("temp");
			temp->setStyleSheet(R"(
			#temp{
				
			}
			)");
			temp->setFixedSize(240, 100);
			planMap->insert(qMakePair(weekdays[i], times[j]), temp);
		}
	}

	populateGrid( );


	QLabel* temp = new QLabel( );
	temp->setObjectName("temp");
	temp->setStyleSheet(R"(
	#temp{
		border-top-left-radius: 10px;
	}
	)");
	temp->setFixedSize(130, 80);
	gridLayout->addWidget(temp, 0, 0);

	for (int i = 0; i < 5; i++) {
		QLabel* temp = new QLabel(weekdays[i]);
		temp->setFixedSize(240, 80);
		temp->setObjectName("temp");
		if (i == 4) {
			temp->setStyleSheet(R"(
				#temp{
					font-size: 24px;
					font-weight: bold;
					border-top-right-radius: 10px;
					color: #d8d8d8;
				}
			)");

		} else {
			temp->setStyleSheet(R"(
				#temp{
					font-size: 24px;
					font-weight: bold;
					color: #d8d8d8;
				}
			)");
		}
		temp->setAlignment(Qt::AlignCenter);
		gridLayout->addWidget(temp, 0, i + 1);
	}

	for (int i = 0; i < 5; i++) {
		QLabel* temp = new QLabel(times[i]);
		temp->setFixedSize(130,100);
		temp->setObjectName("temp");
		if (i == 9) {
			temp->setStyleSheet(R"(
				#temp{
					font-size: 16px;
					font-weight: bold;
					border-bottom-left-radius: 10px;
					color: #d8d8d8;
				}
			)");
		} else {
			temp->setStyleSheet(R"(
				#temp{
					font-size: 16px;
					font-weight: bold;
					color: #d8d8d8;
				}
			)");
		}
		temp->setAlignment(Qt::AlignRight);
		gridLayout->addWidget(temp, i + 1, 0);
	}

	gridLayout->setSpacing(0);
	setLayout(gridLayout);
}

void PlanGrid::populateGrid( ) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; ++j) {
			gridLayout->addWidget(planMap->value(qMakePair(weekdays[i], times[j])), j + 1, i + 1);
			if (i == 4 && j == 4) {
				(planMap->value(qMakePair(weekdays[i], times[j])))->setStyleSheet(R"(
					border-bottom-right-radius:10px;
				)");
			}
		}
	}
}

