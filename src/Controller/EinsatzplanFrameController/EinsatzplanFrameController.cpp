# include "EinsatzplanFrameController.hpp"

EinsatzplanFrameController::EinsatzplanFrameController(QString id, bool admin)
:id_m(id),admin_m(admin)
{

}

void EinsatzplanFrameController::deleteMember(QString id){
    /*
    DatabaseHandler db = new DatabaseHandler();
    db.executeQuery("DELETE FROM ...")
    */
}

void EinsatzplanFrameController::deleteVeranstaltung(QString veranstaltungsname){
    /*
    DatabaseHandler db = new DatabaseHandler();
    db.executeQuery()
    */
}

void EinsatzplanFrameController::createMember(QString name, QString email, QString passwort, bool admin){
    /*
    DatabaseHandler db = new DatabaseHandler();
    db.executeQuery()
    */
}

void EinsatzplanFrameController::createVeranstaltung(QString name, QString raum, QString campus, QString begin, QString ende){
    /*
    DatabaseHandler db = new DatabaseHandler();
    db.executeQuery()
    */
}