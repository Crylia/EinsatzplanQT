#pragma once
#include <iostream>
#include <QString>

class LoginFrameController{
private:
public:
    LoginFrameController();
    bool tryLogin(QString id, QString password);
};