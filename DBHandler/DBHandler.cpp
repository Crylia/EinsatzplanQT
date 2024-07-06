#include "DBHandler.hpp"

#include <iostream>
//host = localhost port = 5432 dbname = postgres user = postgres password = ****


DBHandler::DBHandler(std::string connStr) : connectionObject(connStr.c_str()) {
    try {
        if (connectionObject.is_open()) {
            std::cout << "Databased connected" << std::endl;
        }
        else
            std::cout << "Failed to connect to Databased" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
};


 
  



