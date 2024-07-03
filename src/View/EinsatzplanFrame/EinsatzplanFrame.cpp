# include "EinsatzplanFrame.hpp"

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

	controller_m = new EinsatzplanFrameController(id, admin);

	profileImg_m = new QLabel(this);
	profileImg_m->setFixedSize(60, 60);
	profileImg_m->setPixmap(QPixmap(":account-box.png"));
	profileImg_m->setObjectName("profileImg");
	profileImg_m->setStyleSheet(R"(
    #profileImg{
        
    }
    )");
	profileImg_m->show( );


	id_m = new QLabel(id, this);
	id_m->setFixedSize(122, 80);
	id_m->setObjectName("id");
	id_m->setStyleSheet(R"(
    #id{
		font-size: 24px;
		color: #d8d8d8;
		font-weight: bold;
    }
    )");
	id_m->show( );


	abmeldenButton_m = new QPushButton("Abmelden", this);
	abmeldenButton_m->setFixedSize(150, 50);
	abmeldenButton_m->setObjectName("abmeldenButton");
	abmeldenButton_m->setStyleSheet(R"(
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
	abmeldenButton_m->show( );

	//implement logoutButton functionality
	connect(abmeldenButton_m, &QPushButton::clicked, this, &EinsatzplanFrame::abmelden);


	einsatzplanLabel_m = new QLabel("Einsatzplan", this);
	einsatzplanLabel_m->setFixedSize(645, 80);
	einsatzplanLabel_m->setAlignment(Qt::AlignCenter);
	einsatzplanLabel_m->setObjectName("einsatzplanLabel");
	einsatzplanLabel_m->setStyleSheet(R"(
    #einsatzplanLabel{
		font-size:40px;
		color: #7FF;
		font-weight: bold;
    }
    )");
	einsatzplanLabel_m->show( );


	planGrid_m = new PlanGrid(this);
	planGrid_m->show( );



	QVBoxLayout* totalLayout = new QVBoxLayout(this);
	totalLayout->setContentsMargins(30, 20, 30, 20);

	QHBoxLayout* topLayout = new QHBoxLayout(this);
	topLayout->addWidget(profileImg_m, 0, Qt::AlignLeft);
	topLayout->addSpacing(10);
	topLayout->addWidget(id_m, 0, Qt::AlignLeft);
	topLayout->addWidget(einsatzplanLabel_m, 4, Qt::AlignCenter);
	topLayout->addWidget(abmeldenButton_m, 0, Qt::AlignRight);


	QHBoxLayout* bottomLayout = new QHBoxLayout(this);
	bottomLayout->addWidget(planGrid_m, 1, Qt::AlignCenter);


	//make bottomLayout bigger then topLayout
	totalLayout->addLayout(topLayout,1);
	totalLayout->addLayout(bottomLayout, 4);



	if (admin) {

		createMemberButton_m = new QPushButton("Mitarbeiter\nHinzufügen", this);
		createMemberButton_m->setFixedSize(200, 50);
		createMemberButton_m->setObjectName("createMember");
		createMemberButton_m->setStyleSheet(R"(
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
		createMemberButton_m->show( );

		//implement createMemberButton functionality
		connect(createMemberButton_m, &QPushButton::clicked, this, &EinsatzplanFrame::createMember);


		deleteMemberButton_m = new QPushButton("Mitarbeiter\nEntfernen", this);
		deleteMemberButton_m->setFixedSize(200, 50);
		deleteMemberButton_m->setObjectName("deleteMember");
		deleteMemberButton_m->setStyleSheet(R"(
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
		deleteMemberButton_m->show( );

		//implement deleteMemberButton functionality
		connect(deleteMemberButton_m, &QPushButton::clicked, this, &EinsatzplanFrame::deleteMember);


		createVeranstaltungButton_m = new QPushButton("Veranstaltung\nHinzufügen", this);
		createVeranstaltungButton_m->setFixedSize(200, 50);
		createVeranstaltungButton_m->setObjectName("createVeranstaltung");
		createVeranstaltungButton_m->setStyleSheet(R"(
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
		createVeranstaltungButton_m->show( );

		//implement createVeranstaltungButton functionality
		connect(createVeranstaltungButton_m, &QPushButton::clicked, this, &EinsatzplanFrame::createVeranstaltung);


		deleteVeranstaltungButton_m = new QPushButton("Veranstaltung\nEntfernen", this);
		deleteVeranstaltungButton_m->setFixedSize(200, 50);
		deleteVeranstaltungButton_m->setObjectName("deleteVeranstaltung");
		deleteVeranstaltungButton_m->setStyleSheet(R"(
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
		deleteVeranstaltungButton_m->show( );

		//implement deleteVeranstaltungButton functionality
		connect(deleteVeranstaltungButton_m, &QPushButton::clicked, this, &EinsatzplanFrame::deleteVeranstaltung);

		QHBoxLayout* adminLayout = new QHBoxLayout(this);
		adminLayout->addWidget(createMemberButton_m, 1, Qt::AlignLeft);
		adminLayout->addWidget(deleteMemberButton_m, 1, Qt::AlignLeft);
		adminLayout->addStretch(1);
		adminLayout->addWidget(createVeranstaltungButton_m, 1, Qt::AlignRight);
		adminLayout->addWidget(deleteVeranstaltungButton_m, 1, Qt::AlignRight);

		totalLayout->addLayout(adminLayout);

	}
}

void EinsatzplanFrame::abmelden(){
	static_cast<QApplication*>(parent()->parent())->exit();
}

void EinsatzplanFrame::deleteVeranstaltung(){
	bool ok;
	QString text = QInputDialog::getText(this, tr("Veranstaltung Entfernen"),
                                         tr("Bitte geben sie den Veranstaltungskürzel ein:"), QLineEdit::Normal,
                                         "", &ok);
	if (ok && text.size()!= 3)
		QMessageBox::information(this, "Veranstaltung Entfernen", "Veranstaltungskürzel besteht aus 3 Zeichen!");
	if (ok && text.size() == 3)
		QMessageBox::information(this, "Veranstaltung entfernen", "Veranstaltung wird entfernt!");
}

void EinsatzplanFrame::createVeranstaltung(){
	createVerDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getName();
        QString raum = dialog.getRaum();
        QString campus = dialog.getCampus();
        QString begin = dialog.getBegin();
        QString ende = dialog.getEnde();
		controller_m->createVeranstaltung(name,raum, campus, begin, ende);
	}
}

void EinsatzplanFrame::deleteMember(){
	bool ok;
	QString text = QInputDialog::getText(this, tr("Mitarbeiter Entfernen"),
                                         tr("Bitte geben sie die Mitarbeiter ID ein:"), QLineEdit::Normal,
                                         "", &ok);
	if (ok && text.size()!= 7)
		QMessageBox::information(this, "Mitarbeiter Entfernen", "Mitarbeiter ID besteht aus 7 Zahlen!");
	if (ok && text.size() == 7)
		QMessageBox::information(this, "Mitarbeiter entfernen", "Mitarbeiter wird entfernt!");
}

void EinsatzplanFrame::createMember(){
	createMemDialog dialog(this);
	if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getName();
        QString email = dialog.getEmail();
        QString password = dialog.getPassword();
        bool isAdmin = dialog.isAdmin();
		controller_m->createMember(name, email, password, isAdmin);
	}
}



createMemDialog::createMemDialog(QWidget* parent)
		:QDialog(parent)
		{
			setWindowTitle("Mitarbeiter Hinzufügen");
			setFixedSize(300,400);

			name_m = new QLineEdit(this);
			name_m->setPlaceholderText("Name");
			name_m->show();
			

			email_m = new QLineEdit(this);
			email_m->setPlaceholderText("Email");
			email_m->show();

			password_m = new QLineEdit(this);
			password_m->setPlaceholderText("Passwort");
			password_m->setEchoMode(QLineEdit::Password);
			password_m->show();

			admin_m = new QCheckBox("Admin?", this);
			admin_m->show();
			

			QVBoxLayout* layout = new QVBoxLayout(this);

			layout->addWidget(name_m);
			layout->addWidget(email_m);
			layout->addWidget(password_m);
			layout->addWidget(admin_m);

			QHBoxLayout* buttonLayout = new QHBoxLayout();
			
			okButton = new QPushButton("OK", this);
    		cancelButton = new QPushButton("Abbrechen", this);

			buttonLayout->addWidget(okButton);
			buttonLayout->addWidget(cancelButton);

			layout->addLayout(buttonLayout);

			connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
			connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
		}

QString	createMemDialog::getName() const {
    return name_m->text();
}

QString createMemDialog::getEmail() const {
    return email_m->text();
}

QString createMemDialog::getPassword() const {
    return password_m->text();
}

bool createMemDialog::isAdmin() const {
    return admin_m->isChecked();
}



createVerDialog::createVerDialog(QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("Veranstaltung Hinzufügen");

    QVBoxLayout* layout = new QVBoxLayout(this);

    name_m = new QLineEdit(this);
    name_m->setPlaceholderText("Veranstaltungskürzel");
    layout->addWidget(name_m);

    raum_m = new QLineEdit(this);
    raum_m->setPlaceholderText("Raum");
    layout->addWidget(raum_m);

    campus_m = new QComboBox(this);
    campus_m->addItem("Campus A");
    campus_m->addItem("Campus B");
    layout->addWidget(campus_m);

    begin_m = new QComboBox(this);
    begin_m->addItem("08:00");
    begin_m->addItem("10:00");
    begin_m->addItem("12:00");
    begin_m->addItem("14:00");
    begin_m->addItem("16:00");
    layout->addWidget(begin_m);

    ende_m = new QComboBox(this);
    ende_m->addItem("10:00");
    ende_m->addItem("12:00");
    ende_m->addItem("14:00");
    ende_m->addItem("16:00");
    ende_m->addItem("18:00");
    layout->addWidget(ende_m);

    QHBoxLayout* buttonLayout = new QHBoxLayout();

    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Abbrechen", this);

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString createVerDialog::getName() const {
    return name_m->text();
}

QString createVerDialog::getRaum() const {
    return raum_m->text();
}

QString createVerDialog::getCampus() const {
    return campus_m->currentText();
}

QString createVerDialog::getBegin() const {
    return begin_m->currentText();
}

QString createVerDialog::getEnde() const {
    return ende_m->currentText();
}