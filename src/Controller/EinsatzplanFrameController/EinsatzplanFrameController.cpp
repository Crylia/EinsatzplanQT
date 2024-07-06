# include "EinsatzplanFrameController.hpp"
# include "../../Core/DBHandler/DBPlan.hpp"

EinsatzplanFrameController::EinsatzplanFrameController(QString id, bool admin)
:id_m(id),admin_m(admin)
{

}

void EinsatzplanFrameController::deleteMember(QString id){
    DBPlan* db = new DBPlan();
    db->deleteVeranstalter(id.toStdString());
    
    /*
    DatabaseHandler db = new DatabaseHandler();
    db.executeQuery("DELETE FROM ...")
    */
}

void EinsatzplanFrameController::deleteVeranstaltung(QString veranstaltungsname){
    DBPlan* db = new DBPlan();
    db->deleteVeranstaltung(veranstaltungsname.toStdString());
    /*
    DatabaseHandler db = new DatabaseHandler();
    db.executeQuery()
    */
}

void EinsatzplanFrameController::createMember(QString name, QString email, QString passwort, bool admin){
    DBPlan* db = new DBPlan();
    std::string temp;
    if (admin)
        temp = "TRUE";
    else    
        temp = "FALSE";
    db->hinzufuegenVeranstalter(email.toStdString(),name.toStdString(),passwort.toStdString(),temp);
    /*
    DatabaseHandler db = new DatabaseHandler();
    db.executeQuery()
    */
}

void EinsatzplanFrameController::createVeranstaltung(QString name, QString raum, QString campus, QString time){
    DBPlan* db = new DBPlan();
    db->hinzufuegenVeranstaltung(name.toStdString(),time.toStdString(),campus.toStdString(),raum.toStdString());
    
    /*
    DatabaseHandler db = new DatabaseHandler();
    db.executeQuery()
    */
}