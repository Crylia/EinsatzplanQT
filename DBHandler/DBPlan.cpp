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
                "DELETE FROM Veranstalter WHERE ID = $1";

            pqxx::result response = worker.exec_params(query, id);
            worker.commit();
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


};

void DBPlan::deleteVeranstaltung(int id) {
    try {
        pqxx::work worker(connObject);
        std::string query =
            "DELETE FROM Veranstaltung WHERE ID = $1;";

        pqxx::result response = worker.exec_params(query, id);
        worker.commit();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}


void DBPlan::hinzufuegenVeranstaltung(std::string name, int dauer, std::string ort, std::string raum) {
    try {
        pqxx::work worker(connObject);
        std::string query =
            "INSERT INTO Veranstaltung (name, dauer, ort, raum) VALUES ($1, $2, $3, $4);";
        pqxx::result response = worker.exec_params(query, name, dauer, ort, raum);
        worker.commit();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}


void DBPlan:: hinzufuegenVeranstalter(std::string email, std::string name, std::string pw, bool admin) {
    try {
        pqxx::work worker(connObject);
        std::string query =
            "INSERT INTO Veranstaltung (email, name, pw, admin) VALUES ($1, $2, $3, $4);";
        pqxx::result response = worker.exec_params(query, email, name, pw, admin);
        worker.commit();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}


void DBPlan::deleteStudent(int id) {
    try {
        pqxx::work worker(connObject);
        std::string query =
            "DELETE FROM studenten WHERE ID = $1;";
        pqxx::result response = worker.exec_params(query, id);
        worker.commit();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}


void DBPlan:: hinzufuegenStudent(std::string email, std::string name, std::string pw) {

    try {
        pqxx::work worker(connObject);
        std::string query =
            "INSERT INTO studenten (email, name, pw) VALUES ($1, $2, $3);";
        pqxx::result response = worker.exec_params(query, email, name, pw);
        worker.commit();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


}
