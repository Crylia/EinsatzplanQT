# pragma once
# include <QString>

class EinsatzplanFrameController{
protected:
    QString id_m;
    bool admin_m;
public:
    EinsatzplanFrameController(QString id = "0000000", bool admin = true);
    void deleteMember(QString id);
    void deleteVeranstaltung(QString veranstaltungsname);
    void createMember(QString name, QString email, QString passwort, bool admin);
    void createVeranstaltung(QString name, QString raum, QString campus, QString time);
};