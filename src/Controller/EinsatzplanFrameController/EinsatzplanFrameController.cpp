# include "EinsatzplanFrameController.hpp"

EinsatzplanFrameController::EinsatzplanFrameController(QString id, bool admin)
	:m_id(id),
	m_admin(admin) {
	const std::map<std::string, std::string> config = load_config("../config.cfg");

	m_connectionString = fmt::format(
		"host={} port={} dbname={} user={} password={}",
		config.at("DB_HOST"),
		config.at("DB_PORT"),
		config.at("DB_NAME"),
		config.at("DB_USER"),
		config.at("DB_PASSWORD")
	);
}

void EinsatzplanFrameController::deleteMember(QString id) {
	DBPlan* db = new DBPlan(m_connectionString);
	db->deleteVeranstalter(id.toStdString( ));
}

void EinsatzplanFrameController::deleteVeranstaltung(QString veranstaltungsname) {
	DBPlan* db = new DBPlan(m_connectionString);
	db->deleteVeranstaltung(veranstaltungsname.toStdString( ));
}

void EinsatzplanFrameController::createMember(QString name, QString email, QString passwort, bool admin) {
	DBPlan* db = new DBPlan(m_connectionString);
	db->hinzufuegenVeranstalter(email.toStdString( ), name.toStdString( ), passwort.toStdString( ), admin ? "TRUE" : "FALSE");
}

void EinsatzplanFrameController::createVeranstaltung(QString name, QString raum, QString campus, QString time) {
	DBPlan* db = new DBPlan(m_connectionString);
	db->hinzufuegenVeranstaltung(name.toStdString( ), time.toStdString( ), campus.toStdString( ), raum.toStdString( ));
}
