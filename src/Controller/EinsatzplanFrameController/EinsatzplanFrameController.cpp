# include "EinsatzplanFrameController.hpp"

EinsatzplanFrameController::EinsatzplanFrameController(QString id, bool admin)
	:m_id(id),
	m_admin(admin) {
	const std::map<std::string, std::string> config = load_config( );

	m_dbHandler = std::make_unique<DBHandler>(fmt::format(
		"host={} port={} dbname={} user={} password={}",
		config.at("DB_HOST"),
		config.at("DB_PORT"),
		config.at("DB_NAME"),
		config.at("DB_USER"),
		config.at("DB_PASSWORD")
	));
}

void EinsatzplanFrameController::deleteMember(QString id) {
	m_dbHandler->deleteVeranstalter(id.toStdString( ));
}

void EinsatzplanFrameController::deleteVeranstaltung(QString veranstaltungsname) {
	m_dbHandler->deleteVeranstaltung(veranstaltungsname.toStdString( ));
}

void EinsatzplanFrameController::createMember(QString name, QString email, QString passwort, bool admin) {
	m_dbHandler->createVeranstalter(name.toStdString( ), email.toStdString( ), passwort.toStdString( ), admin);
}

void EinsatzplanFrameController::createVeranstaltung(QString name, QString raum, QString campus, QString time) {
	m_dbHandler->createVeranstaltung(name.toStdString( ), campus.toStdString( ), raum.toStdString( ), std::to_string((char)time.toStdString( ).at(0) - 48));
}
