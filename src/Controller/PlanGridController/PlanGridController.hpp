#pragma once

#include <QLabel>
#include <sstream>
#include <fmt/format.h>
#include <QVBoxLayout>
#include <QPushButton>

#include "../../Core/config/config.hpp"
#include "../../Core/DBHandler/DBHandler/DBHandler.hpp"

class PlanGridController : public QObject {
	Q_OBJECT
private:
	std::string m_connectionString;
protected:
	QString weekdays[5];
	QString times[5];
	QMap<QPair<QString, QString>, QWidget*>* planMap;

public:
	PlanGridController( );

	QMap<QPair<QString, QString>, QWidget*>* getVeranstaltungen( );
	void Krankmelden(const int id, const int tag, const int stunde);
};
