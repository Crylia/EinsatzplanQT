#pragma once

#include <QString>
#include <fmt/format.h>

#include "../../Core/DBHandler/DBHandler.hpp"
#include "../../Core/config/config.hpp"

class EinsatzplanFrameController {
private:
	std::unique_ptr<DBHandler> m_dbHandler;

protected:
	QString m_id;
	bool m_admin;

public:
	EinsatzplanFrameController(QString id = "0000000", bool admin = true);
	void deleteMember(QString id);
	void deleteVeranstaltung(QString veranstaltungsname);
	void createMember(QString name, QString email, QString passwort, bool admin);
	void createVeranstaltung(QString name, QString raum, QString campus, QString time);

};
