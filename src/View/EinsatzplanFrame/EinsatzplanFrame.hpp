# pragma once
# include <QFrame>
# include <QLabel>
# include <QPushButton>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QMainWindow>
# include <QApplication>
# include <QMessageBox>
# include <QInputDialog>
# include "../PlanGrid/PlanGrid.hpp"


class EinsatzplanFrame : public QFrame{
    Q_OBJECT
protected:
    QLabel* profileImg_m;
    QLabel* id_m;
    QLabel* einsatzplanLabel_m;
    
    PlanGrid* planGrid_m;
    
    QPushButton* abmeldenButton_m;
    QPushButton* createMemberButton_m;
    QPushButton* deleteMemberButton_m;
    QPushButton* createVeranstaltungButton_m;
    QPushButton* deleteVeranstaltungButton_m;

public:
    EinsatzplanFrame(QWidget* parent = nullptr, QString id = "0000000", bool admin = true);

private slots:

    void abmelden();
    void deleteVeranstaltung();
    void createVeranstaltung();
    void deleteMember();
    void createMember();

};