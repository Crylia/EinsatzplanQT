#include "DBLogin.hpp"
#include <iostream>

DBLogin::DBLogin(std::string connStr) : DBHandler(connStr) {};



/*

return 1 if admin | 0 if not admin | -1 if failed

*/

int DBLogin::checkValidLogin(int id, std::string pw) {

    try {
        pqxx::work worker(connectionObject);

        std::string query =
            "SELECT admin FROM studenten_veranstalterr WHERE id = $1 AND passwort = $2";

        pqxx::result response = worker.exec_params(query, id, pw);

        if (response.affected_rows() > 0) {

            std::cout << response[0][0] << std::endl;
            if (response[0][0].is_null())
                return 0;
            return response[0][0].as<bool>();

        }

        return -1;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}

