# pragma once
# include <QGridLayout>
# include <QWidget>
# include <QLabel>
# include <QDateTime>

class PlanGrid : public QWidget {
    Q_OBJECT
private:
    QString weekdays[5];
    QString times[10];
protected:
    QGridLayout* gridLayout;
    QMap<QPair<QString, QString>, QLabel*>* planMap;
public:
    PlanGrid(QWidget* parent = nullptr);
};
