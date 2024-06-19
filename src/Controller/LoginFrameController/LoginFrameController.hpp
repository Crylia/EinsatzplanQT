#pragma once
#include <iostream>

class LoginFrameController{
private:
    std::string id_m;
    std::string passwort_m;
    
public:
    LoginFrameController(std::string id, std::string password);
};