#pragma once

#include <iostream>
#include <QString>
#include <fmt/core.h>

#include "../../Core/DBHandler/DBHandler.hpp"
#include "../../Core/config/config.hpp"

class LoginFrameController {
private:
    std::unique_ptr<DBHandler> m_dbHandler;

public:
    LoginFrameController( );

    int tryLogin(QString id, QString password);

};
