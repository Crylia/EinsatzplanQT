#ifndef _DBLOGIN_HPP_
#define _DBLOGIN_HPP_
#include "DBHandler.hpp"

class DBLogin : public DBHandler {
public:
	DBLogin(std::string connStr);
	/*

return 1 if admin | 0 if not admin | -1 if failed

*/
	int checkValidLogin(std::string id, std::string pw);
};



#endif
