#include "LoginFrameController.hpp"

LoginFrameController::LoginFrameController( ) {
	auto config = load_config( );

	m_dbHandler = std::make_unique<DBHandler>(fmt::format(
		"host={} port={} dbname={} user={} password={}",
		config.at("DB_HOST"),
		config.at("DB_PORT"),
		config.at("DB_NAME"),
		config.at("DB_USER"),
		config.at("DB_PASSWORD")
	));
}

int LoginFrameController::tryLogin(QString id, QString password) {
	return m_dbHandler->tryAuthenticate(id.toStdString( ), password.toStdString( ));
}
