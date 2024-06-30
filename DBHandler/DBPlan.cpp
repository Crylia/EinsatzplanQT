#include "DBPlan.hpp"

DBPlan::DBPlan(std::string connStr) : DBHandler(connStr) {};


void DBPlan::meldeKrank(int id) {

    try {
        pqxx::work worker(connectionObject);
        std::string query =
            "INSERT INTO krank (veranstalter_ID) VALUES($1);";

        pqxx::result response = worker.exec_params(query, id);
        worker.commit();
    }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;

        }
    }


    void DBPlan::meldeGesund(int id) {
        try {
            pqxx::work worker(connectionObject);
            std::string query =
                "DELETE FROM krank WHERE veranstalter_ID = $1 ;";

            pqxx::result response = worker.exec_params(query, id);
            worker.commit();
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }





    void DBPlan:: deleteVeranstalter(int id) {
        try {
            pqxx::work worker(connectionObject);
            std::string query =
                "DELETE FROM Veranstalterrrr WHERE ID = $1";

            pqxx::result response = worker.exec_params(query, id);
            worker.commit();
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


};