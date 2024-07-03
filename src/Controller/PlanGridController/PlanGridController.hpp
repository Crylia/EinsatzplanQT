# pragma once
# include <QLabel>

class PlanGridController{
protected:
    QString weekdays[5];
    QString times[10];
    QMap<QPair<QString, QString>, QLabel*>* planMap;
public:
    PlanGridController();

    QMap<QPair<QString, QString>, QLabel*> getVeranstaltungen();
};