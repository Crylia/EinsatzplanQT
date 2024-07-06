#pragma once

#include <fmt/printf.h>

#include "../DBHandler/DBHandler.hpp"

class DBLogin : public DBHandler {
public:
	DBLogin(std::string connStr);

	/**
	 * @brief Tries to login the user
	 * @param id user id
	 * @param pw user password
	 * @return returns 1 if admin and 0 if not
	 */
	int checkValidLogin(std::string id, std::string pw);
};
