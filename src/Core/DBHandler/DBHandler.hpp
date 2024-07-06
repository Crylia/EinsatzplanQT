#ifndef DBHANDLER_HPP_
#define DBHANDLER_HPP_
#include <pqxx/pqxx>
#include <string>

class DBHandler {
protected:
	pqxx::connection connectionObject;

public:
	DBHandler(std::string connStr);
};

#endif