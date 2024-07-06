# pragma once
# include <QLabel>
# include <iostream>
# include <sstream>
# include "../../Core/DBHandler/DBPlan.hpp"

class PlanGridController{
protected:
    QString weekdays[5];
    QString times[5];
    QMap<QPair<QString, QString>, QLabel*>* planMap;
public:
    PlanGridController();

    QMap<QPair<QString, QString>, QLabel*>* getVeranstaltungen();
};