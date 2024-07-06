#include "EinsatzplanFrame.hpp"

EinsatzplanFrame::EinsatzplanFrame(QWidget* parent, QString id, bool admin)
	:QFrame(parent) {
	setFrameStyle(QFrame::Box);
	setObjectName("einsatzplanFrame");
	setStyleSheet(R"(
    #einsatzplanFrame{
      background-color: #212121;
      border: none;
    }
  )");

	m_controller = new EinsatzplanFrameController(id, admin);

	m_profileImg = new QLabel(this);
	m_profileImg->setFixedSize(60, 60);
	m_profileImg->setPixmap(QPixmap(":account-box.png"));
	m_profileImg->setObjectName("profileImg");
	m_profileImg->setStyleSheet(R"(
    #profileImg{
      
    }
  )");
	m_profileImg->show( );

	m_id = new QLabel(id, this);
	m_id->setFixedSize(122, 80);
	m_id->setObjectName("id");
	m_id->setStyleSheet(R"(
    #id{
			font-size: 24px;
			color: #d8d8d8;
			font-weight: bold;
    }
  )");
	m_id->show( );

	m_abmeldenButton = new QPushButton("Abmelden", this);
	m_abmeldenButton->setFixedSize(150, 50);
	m_abmeldenButton->setObjectName("abmeldenButton");
	m_abmeldenButton->setStyleSheet(R"(
    #abmeldenButton{
      font-size: 24px;
      font-weight: bold;
      color: #212121;
      background-color: #E0894A;
      border-radius: 10px;
    }
    #abmeldenButton:pressed{
      background-color: #D0793A;
    }
  )");
	m_abmeldenButton->show( );

	//implement logoutButton functionality
	connect(m_abmeldenButton, &QPushButton::clicked, this, &EinsatzplanFrame::abmelden);

	m_einsatzplanLabel = new QLabel("Einsatzplan", this);
	m_einsatzplanLabel->setFixedSize(645, 80);
	m_einsatzplanLabel->setAlignment(Qt::AlignCenter);
	m_einsatzplanLabel->setObjectName("einsatzplanLabel");
	m_einsatzplanLabel->setStyleSheet(R"(
    #einsatzplanLabel{
			font-size:40px;
			color: #7FF;
			font-weight: bold;
    }
  )");
	m_einsatzplanLabel->show( );

	m_planGrid = new PlanGrid(this);
	m_planGrid->show( );

	QVBoxLayout* totalLayout = new QVBoxLayout(this);
	totalLayout->setContentsMargins(30, 20, 30, 20);

	QHBoxLayout* topLayout = new QHBoxLayout( );
	topLayout->addWidget(m_profileImg, 0, Qt::AlignLeft);
	topLayout->addSpacing(10);
	topLayout->addWidget(m_id, 0, Qt::AlignLeft);
	topLayout->addWidget(m_einsatzplanLabel, 4, Qt::AlignCenter);
	topLayout->addWidget(m_abmeldenButton, 0, Qt::AlignRight);

	QHBoxLayout* bottomLayout = new QHBoxLayout( );
	bottomLayout->addWidget(m_planGrid, 1, Qt::AlignCenter);

	//make bottomLayout bigger then topLayout
	totalLayout->addLayout(topLayout, 1);
	totalLayout->addLayout(bottomLayout, 4);

	if (!admin) { return; }

	m_createMemberButton = new QPushButton("Mitarbeiter\nHinzufügen", this);
	m_createMemberButton->setFixedSize(200, 50);
	m_createMemberButton->setObjectName("createMember");
	m_createMemberButton->setStyleSheet(R"(
    #createMember{
      font-size: 16px;
      font-weight: bold;
      background-color: #DCFF78;
			color: #212121;
      border-radius: 10px;
    }
    #createMember:pressed{
      background-color: #CCEF68;
    }
  )");
	m_createMemberButton->show( );

	//implement createMemberButton functionality
	connect(m_createMemberButton, &QPushButton::clicked, this, &EinsatzplanFrame::createMember);

	m_deleteMemberButton = new QPushButton("Mitarbeiter\nEntfernen", this);
	m_deleteMemberButton->setFixedSize(200, 50);
	m_deleteMemberButton->setObjectName("deleteMember");
	m_deleteMemberButton->setStyleSheet(R"(
    #deleteMember{
      font-size: 16px;
      font-weight: bold;
      background-color: #DCFF78;
			color: #212121;
      border-radius: 10px;
    }
    #deleteMember:pressed{
      background-color: #CCEF68;
    }
  )");
	m_deleteMemberButton->show( );

	//implement deleteMemberButton functionality
	connect(m_deleteMemberButton, &QPushButton::clicked, this, &EinsatzplanFrame::deleteMember);

	m_createVeranstaltungButton = new QPushButton("Veranstaltung\nHinzufügen", this);
	m_createVeranstaltungButton->setFixedSize(200, 50);
	m_createVeranstaltungButton->setObjectName("createVeranstaltung");
	m_createVeranstaltungButton->setStyleSheet(R"(
    #createVeranstaltung{
      font-size: 16px;
      font-weight: bold;
      background-color: #DCFF78;
			color: #212121;
      border-radius: 10px;
    }
    #createVeranstaltung:pressed{
      background-color: #CCEF68;
    }
  )");
	m_createVeranstaltungButton->show( );

	//implement createVeranstaltungButton functionality
	connect(m_createVeranstaltungButton, &QPushButton::clicked, this, &EinsatzplanFrame::createVeranstaltung);

	m_deleteVeranstaltungButton = new QPushButton("Veranstaltung\nEntfernen", this);
	m_deleteVeranstaltungButton->setFixedSize(200, 50);
	m_deleteVeranstaltungButton->setObjectName("deleteVeranstaltung");
	m_deleteVeranstaltungButton->setStyleSheet(R"(
    #deleteVeranstaltung{
      font-size: 16px;
      font-weight: bold;
      background-color: #DCFF78;
			color: #212121;
      border-radius: 10px;
    }
    #deleteVeranstaltung:pressed{
      background-color: #CCEF68;
    }
  )");
	m_deleteVeranstaltungButton->show( );

	//implement deleteVeranstaltungButton functionality
	connect(m_deleteVeranstaltungButton, &QPushButton::clicked, this, &EinsatzplanFrame::deleteVeranstaltung);

	QHBoxLayout* adminLayout = new QHBoxLayout( );
	adminLayout->addWidget(m_createMemberButton, 1, Qt::AlignLeft);
	adminLayout->addWidget(m_deleteMemberButton, 1, Qt::AlignLeft);
	adminLayout->addStretch(1);
	adminLayout->addWidget(m_createVeranstaltungButton, 1, Qt::AlignRight);
	adminLayout->addWidget(m_deleteVeranstaltungButton, 1, Qt::AlignRight);

	totalLayout->addLayout(adminLayout);
}

void EinsatzplanFrame::abmelden( ) {
	static_cast<QApplication*>(parent( )->parent( ))->exit( );
}

void EinsatzplanFrame::deleteVeranstaltung( ) {
	bool ok;
	QString text = QInputDialog::getText(this, tr("Veranstaltung Entfernen"),
		tr("Bitte geben sie den Veranstaltungskürzel ein:"), QLineEdit::Normal,
		"", &ok);
	if (ok && text.size( ) == 3) {
		m_controller->deleteVeranstaltung(text);
		QMessageBox::information(this, "Veranstaltung entfernen", "Veranstaltung wird entfernt!");
	}
}

void EinsatzplanFrame::createVeranstaltung( ) {
	CreateVerDialog dialog(this);
	if (dialog.exec( ) == QDialog::Accepted) {
		QString name = dialog.getName( );
		QString raum = dialog.getRaum( );
		QString campus = dialog.getCampus( );
		QString time = dialog.getTime( );
		m_controller->createVeranstaltung(name, raum, campus, time);
	}
}

void EinsatzplanFrame::deleteMember( ) {
	bool ok;
	QString text = QInputDialog::getText(this, tr("Mitarbeiter Entfernen"),
		tr("Bitte geben sie die Mitarbeiter ID ein:"), QLineEdit::Normal,
		"", &ok);

	if (ok && text.size( ) == 7) {
		m_controller->deleteMember(text);
		QMessageBox::information(this, "Mitarbeiter entfernen", "Mitarbeiter wird entfernt!");
	}
}

void EinsatzplanFrame::createMember( ) {
	CreateMemDialog dialog(this);
	if (dialog.exec( ) == QDialog::Accepted) {
		QString name = dialog.getName( );
		QString email = dialog.getEmail( );
		QString password = dialog.getPassword( );
		bool isAdmin = dialog.isAdmin( );
		m_controller->createMember(name, email, password, isAdmin);
	}
}
