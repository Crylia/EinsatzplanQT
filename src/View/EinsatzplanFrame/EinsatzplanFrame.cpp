# include "EinsatzplanFrame.hpp"

EinsatzplanFrame::EinsatzplanFrame(QWidget* parent, QString id, bool admin){
    setFrameStyle(QFrame::Box);

    profileImg_m = new QLabel(this);

    id_m = new QLabel(id,this);

    einsatzplanLabel_m = new QLabel("Einsatzplan",this);
    
    planGrid_m = new PlanGrid(this);
    
    

    if (admin){
        abmeldenButton_m = new QPushButton(this);

        createMemberButton_m = new QPushButton(this);

        deleteMemberButton_m = new QPushButton(this);

        createVeranstaltungButton_m = new QPushButton(this);

        deleteVeranstaltungButton_m = new QPushButton(this);

    }
}