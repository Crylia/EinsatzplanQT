# include "EinsatzplanFrame.hpp"

EinsatzplanFrame::EinsatzplanFrame(QWidget* parent, QString id, bool admin)
:QFrame(parent)
{
    setFrameStyle(QFrame::Box);
    setObjectName("einsatzplanFrame");
    setStyleSheet(R"(
    #einsatzplanFrame{
        background-color: #212121;
        border: none;
    }
    )");


    profileImg_m = new QLabel(this);
    profileImg_m->setObjectName("profileImg");
    profileImg_m->setStyleSheet(R"(
    #profileImg{
        background-color: #000000;
    }
    )");
    profileImg_m->show();


    id_m = new QLabel(id,this);
    id_m->setObjectName("id");
    id_m->setStyleSheet(R"(
    #id{
    
    }
    )");
    id_m->show();


    abmeldenButton_m = new QPushButton(this);
    abmeldenButton_m->setObjectName("abmeldenButton");
    abmeldenButton_m->setStyleSheet(R"(
    #abmeldenButton{
    
    }
    )");
    abmeldenButton_m->show();


    einsatzplanLabel_m = new QLabel("Einsatzplan",this);
    einsatzplanLabel_m->setObjectName("einsatzplanLabel");
    einsatzplanLabel_m->setStyleSheet(R"(
    #einsatzplanLabel{
    
    }
    )");
    einsatzplanLabel_m->show();

    
    planGrid_m = new PlanGrid(this);

    QVBoxLayout* totalLayout = new QVBoxLayout(this);
    totalLayout->setContentsMargins(50,20,50,20);

    QHBoxLayout* topLayout = new QHBoxLayout(this);
    topLayout->addWidget(profileImg_m, 1, Qt::AlignCenter);
    topLayout->addWidget(id_m, 1, Qt::AlignCenter);
    topLayout->addWidget(einsatzplanLabel_m, 2, Qt::AlignCenter);
    topLayout->addWidget(abmeldenButton_m, 1, Qt::AlignRight);

    QHBoxLayout* bottomLayout = new QHBoxLayout(this);
    // PlanGrid
    
    
    

    totalLayout->addLayout(topLayout);
    totalLayout->addLayout(bottomLayout);



    if (admin){

        createMemberButton_m = new QPushButton("Mitarbeiter Hinzufügen",this);
        createMemberButton_m->setObjectName("createMember");
        createMemberButton_m->setStyleSheet(R"(
        #createMember{
        
        }
        )");
        createMemberButton_m->show();


        deleteMemberButton_m = new QPushButton("Mitarbeiter Entfernen",this);
        deleteMemberButton_m->setObjectName("deleteMember");
        deleteMemberButton_m->setStyleSheet(R"(
        #deleteMember{
        
        }
        )");
        deleteMemberButton_m->show();


        createVeranstaltungButton_m = new QPushButton("Veranstaltung Hinzufügen",this);
        createVeranstaltungButton_m->setObjectName("createVeranstaltung");
        createVeranstaltungButton_m->setStyleSheet(R"(
        #createVeranstaltung{
        
        }
        )");
        createVeranstaltungButton_m->show();


        deleteVeranstaltungButton_m = new QPushButton("Veranstaltung Entfernen",this);
        deleteVeranstaltungButton_m->setObjectName("deleteVeranstaltung");
        deleteVeranstaltungButton_m->setStyleSheet(R"(
        #deleteVeranstaltung{
        
        }
        )");
        deleteVeranstaltungButton_m->show();

        QHBoxLayout* adminLayout = new QHBoxLayout(this);
        adminLayout->addWidget(createMemberButton_m, 1, Qt::AlignCenter);
        adminLayout->addWidget(deleteMemberButton_m,1 , Qt::AlignCenter);
        adminLayout->addWidget(createVeranstaltungButton_m,1 , Qt::AlignCenter);
        adminLayout->addWidget(deleteVeranstaltungButton_m,1 , Qt::AlignCenter);
        
        totalLayout->addLayout(adminLayout);

    }
}