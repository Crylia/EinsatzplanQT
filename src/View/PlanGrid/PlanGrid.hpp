# pragma once
# include <QGridLayout>

class PlanGrid {
protected:
    QGridLayout* gridLayout;
public:
    PlanGrid(QWidget* parent = nullptr);
};