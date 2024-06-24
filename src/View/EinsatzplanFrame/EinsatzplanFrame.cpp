# include "EinsatzplanFrame.hpp"

EinsatzplanFrame::EinsatzplanFrame(QWidget* parent, QString id, bool admin)
:QFrame(parent)
{
    //setFrameStyle(QFrame::Box);
    setObjectName("EinsatzplanFrame");
    setStyleSheet(R"(

    )");


    profileImg_m = new QLabel(this);
    profileImg_m->show();


    id_m = new QLabel(id,this);
    id_m->show();


    abmeldenButton_m = new QPushButton(this);
    abmeldenButton_m->show();


    einsatzplanLabel_m = new QLabel("Einsatzplan",this);
    einsatzplanLabel_m->show();

    
    planGrid_m = new PlanGrid(this);

    QVBoxLayout* totalLayout = new QVBoxLayout(this);

    QHBoxLayout* topLayout = new QHBoxLayout(this);
    topLayout->addStretch(1);
    topLayout->addWidget(profileImg_m);
    topLayout->addStretch(1);
    topLayout->addWidget(id_m);
    topLayout->addStretch(6);
    topLayout->addWidget(abmeldenButton_m);
    topLayout->addStretch(1);

    QHBoxLayout* bottomLayout = new QHBoxLayout(this);
    // PlanGrid
    
    
    

    totalLayout->addLayout(topLayout);
    totalLayout->addLayout(bottomLayout);



    if (admin){

        createMemberButton_m = new QPushButton("Mitarbeiter Hinzufügen",this);
        createMemberButton_m->show();


        deleteMemberButton_m = new QPushButton(this);
        deleteMemberButton_m->show();


        createVeranstaltungButton_m = new QPushButton(this);
        createVeranstaltungButton_m->show();


        deleteVeranstaltungButton_m = new QPushButton(this);
        deleteVeranstaltungButton_m->show();

        QHBoxLayout* adminLayout = new QHBoxLayout(this);
        adminLayout->addStretch(1);
        adminLayout->addWidget(createMemberButton_m, 1, Qt::AlignLeft);
        adminLayout->addWidget(deleteMemberButton_m,1 , Qt::AlignLeft);
        adminLayout->addWidget(createVeranstaltungButton_m,1 , Qt::AlignLeft);
        adminLayout->addWidget(deleteVeranstaltungButton_m,1 , Qt::AlignLeft);
        
        totalLayout->addLayout(adminLayout);

    }
}