#pragma once
#include <iostream>

class LoginFrameController{
private:
public:
    LoginFrameController();
    bool tryLogin(std::string id, std::string password);
};