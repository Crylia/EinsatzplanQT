#include "DBHandler.hpp"

DBHandler::DBHandler(std::string connStr) :
	connectionObject(connStr.c_str( )) {
	try {
		if (connectionObject.is_open( ))
			fmt::print("Databased connected");
		else
			fmt::print("Failed to connect to Databased");
	}
	catch (const std::exception& e) {
		fmt::print(e.what( ));
	}
};
