#pragma once

#include <iostream>
#include <QString>
#include <fmt/core.h>

#include "../../Core/DBHandler/DBLogin/DBLogin.hpp"
#include "../../Core/config/config.hpp"

class LoginFrameController {
private:
    std::string m_connectionString;
public:
    LoginFrameController( );
    int tryLogin(QString id, QString password);
};
