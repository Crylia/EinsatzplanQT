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
	((QApplication*)(parent()->parent()))->exit();
}

void EinsatzplanFrame::deleteVeranstaltung(){

}

void EinsatzplanFrame::createVeranstaltung(){

}

void EinsatzplanFrame::deleteMember(){

}

void EinsatzplanFrame::createMember(){

}