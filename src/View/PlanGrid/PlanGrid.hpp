#pragma once

#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QDateTime>

#include "../../Controller/PlanGridController/PlanGridController.hpp"
#include "../Widgets/GridItem.hpp"

class PlanGrid : public QWidget {
	Q_OBJECT
private:
	QString m_weekdays[5];
	QString m_times[5];

	void populateGrid( );

protected:
	QGridLayout* gridLayout;
	QMap<QPair<QString, QString>, QWidget*>* planMap;
	PlanGridController* planGridController;

public:
	PlanGrid(QWidget* parent = nullptr);
};
