#pragma once

#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QDateTime>

#include "../../Controller/PlanGridController/PlanGridController.hpp"
#include "../EinsatzplanFrame/Dialogs/Krankmelden/Krankmelden.hpp"
#include "../EinsatzplanFrame/Dialogs/CreateMember/CreateMember.hpp"

class PlanGrid : public QWidget {
	Q_OBJECT
private:
	QString m_weekdays[5];
	QString m_times[6];


protected:
	QGridLayout* gridLayout;
	QMap<QPair<QString, QString>, QWidget*>* planMap;

	void KrankmeldenDialog( );

public:
	PlanGrid(QWidget* parent = nullptr);

	PlanGridController* planGridController;

	void populateGrid( );

	inline void setPlanMap(QMap<QPair<QString, QString>, QWidget*>* planMap) {
		this->planMap = planMap;
	}
};
