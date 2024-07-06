#include "PlanGrid.hpp"

PlanGrid::PlanGrid(QWidget* parent)
	:QWidget(parent),
	planGridController(new PlanGridController( )) {
	setObjectName("PlanGrid");
	setStyleSheet(R"(
		QWidget{
			background-color: #313131;
			border: 2px solid #414141;
		}
	)");

	m_weekdays[0] = "Montag";
	m_weekdays[1] = "Dienstag";
	m_weekdays[2] = "Mittwoch";
	m_weekdays[3] = "Donnerstag";
	m_weekdays[4] = "Freitag";

	m_times[0] = "08:00";
	m_times[1] = "10:00";
	m_times[2] = "12:00";
	m_times[3] = "14:00";
	m_times[4] = "16:00";

	planMap = new QMap<QPair<QString, QString>, QWidget*>( );

	gridLayout = new QGridLayout(this);

	// Empty top left corner
	QLabel* temp = new QLabel( );
	temp->setObjectName("temp");
	temp->setStyleSheet(R"(
		#temp{
			border-top-left-radius: 10px;
		}
	)");
	temp->setFixedSize(130, 80);
	gridLayout->addWidget(temp, 0, 0);

	// Add Weekdays ontop of plan
	for (int i = 0; i < 5; i++) {
		QLabel* temp = new QLabel(m_weekdays[i]);
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

	// Add times left to plan
	for (int i = 0; i < 5; i++) {
		QLabel* temp = new QLabel(m_times[i]);
		temp->setFixedSize(130, 100);
		temp->setObjectName("temp");
		if (i == 4) {
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
		temp->setAlignment(Qt::AlignCenter);
		gridLayout->addWidget(temp, i + 1, 0);
	}

	planMap = planGridController->getVeranstaltungen( );
	populateGrid( );

	gridLayout->setSpacing(0);
	setLayout(gridLayout);
}

void PlanGrid::populateGrid( ) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; ++j) {
			gridLayout->addWidget(planMap->value(qMakePair(m_weekdays[i], m_times[j])), j + 1, i + 1);
			if (i == 4 && j == 4) {
				(planMap->value(qMakePair(m_weekdays[i], m_times[j])))->setStyleSheet(R"(
					border-bottom-right-radius:10px;
				)");
			}
		}
	}
}

