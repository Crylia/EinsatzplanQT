#pragma once

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>
#include <QCheckBox>
#include <QComboBox>

#include "../PlanGrid/PlanGrid.hpp"
#include "../../Controller/EinsatzplanFrameController/EinsatzplanFrameController.hpp"
#include "Dialogs/CreateMember/CreateMember.hpp"
#include "Dialogs/CreateVeranstaltung/CreateVeranstaltung.hpp"

class EinsatzplanFrame : public QFrame {
	Q_OBJECT
protected:
	EinsatzplanFrameController* m_controller;

	QLabel* m_profileImg;
	QLabel* m_id;
	QLabel* m_einsatzplanLabel;

	PlanGrid* m_planGrid;

	QPushButton* m_abmeldenButton;
	QPushButton* m_createMemberButton;
	QPushButton* m_deleteMemberButton;
	QPushButton* m_createVeranstaltungButton;
	QPushButton* m_deleteVeranstaltungButton;

public:
	EinsatzplanFrame(QWidget* parent = nullptr, QString id = "0000000", bool admin = true);

private slots:

	void abmelden( );
	void deleteVeranstaltung( );
	void createVeranstaltung( );
	void deleteMember( );
	void createMember( );
};
