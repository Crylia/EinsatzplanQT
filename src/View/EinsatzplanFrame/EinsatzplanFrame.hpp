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
# include <QCheckBox>
# include <QComboBox>
# include "../PlanGrid/PlanGrid.hpp"
# include "../../Controller/EinsatzplanFrameController/EinsatzplanFrameController.hpp"


class EinsatzplanFrame : public QFrame{
    Q_OBJECT
protected:
    EinsatzplanFrameController* controller_m;

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

class createVerDialog : public QDialog{
		Q_OBJECT
	protected:

		QLineEdit* name_m;
        QLineEdit* raum_m;
        QComboBox* campus_m;
		QComboBox* begin_m;
		QComboBox* ende_m;
        QPushButton* okButton;
        QPushButton* cancelButton;

public:

	createVerDialog(QWidget* parent = nullptr);

    QString getName() const;
    QString getRaum() const;
    QString getCampus() const;
    QString getBegin() const;
    QString getEnde() const;
};

class createMemDialog : public QDialog{
		Q_OBJECT
	protected:
		QLineEdit* name_m;
		QLineEdit* email_m;
		QLineEdit* password_m;
		QCheckBox* admin_m;
        QPushButton* okButton;
        QPushButton* cancelButton;

public:

	createMemDialog(QWidget* parent = nullptr);

    QString getName() const;
    QString getEmail() const;
    QString getPassword() const;
    bool isAdmin() const;
};