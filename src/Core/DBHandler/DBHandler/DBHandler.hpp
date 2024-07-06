#pragma once

#include <pqxx/pqxx>
#include <string>
#include <fmt/core.h>

class DBHandler {
protected:
	pqxx::connection connectionObject;

public:
	DBHandler(std::string connStr);
};
