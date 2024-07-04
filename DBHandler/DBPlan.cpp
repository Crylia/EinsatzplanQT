#include "DBPlan.hpp"

DBPlan::DBPlan(std::string connStr) : DBHandler(connStr) {
};


void DBPlan::meldeKrank(std::string id, std::string zeit) {

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


void DBPlan::meldeGesund(std::string id) {
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





void DBPlan::deleteVeranstalter(std::string id) {
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




void DBPlan::deleteVeranstaltung(std::string id) {
    try {
        pqxx::work worker(connectionObject);
        std::string query =
            "DELETE FROM Veranstaltung WHERE ID = $1;";

        pqxx::result response = worker.exec_params(query, id);
        worker.commit();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}


void DBPlan::hinzufuegenVeranstaltung(std::string name, std::string dauer, std::string ort, std::string raum) {
    try {
        pqxx::work worker(connectionObject);
        std::string query =
            "INSERT INTO Veranstaltung (name, dauer, ort, raum) VALUES ($1, $2, $3, $4);";
        pqxx::result response = worker.exec_params(query, name, dauer, ort, raum);
        worker.commit();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}


void DBPlan::hinzufuegenVeranstalter(std::string email, std::string name, std::string pw, std::string admin) {
    try {
        pqxx::work worker(connectionObject);
        std::string query =
            "INSERT INTO Veranstaltung (email, name, pw, admin) VALUES ($1, $2, $3, $4);";
        pqxx::result response = worker.exec_params(query, email, name, pw, admin);
        worker.commit();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}


void DBPlan::deleteStudent(std::string id) {
    try {
        pqxx::work worker(connectionObject);
        std::string query =
            "DELETE FROM studenten WHERE ID = $1;";
        pqxx::result response = worker.exec_params(query, id);
        worker.commit();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}


void DBPlan::hinzufuegenStudent(std::string email, std::string name, std::string pw) {

    try {
        pqxx::work worker(connectionObject);
        std::string query =
            "INSERT INTO studenten (email, name, pw) VALUES ($1, $2, $3);";
        pqxx::result response = worker.exec_params(query, email, name, pw);
        worker.commit();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


}



std::string DBPlan::getDauer(std::string tag, std::string stunde) {
    try {
       
        pqxx::work worker(connectionObject);
        std::string query =
            "SELECT dauer FROM Veranstaltung WHERE ID = (SELECT Veranstaltung_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2);";
        pqxx::result response = worker.exec_params(query, stunde, tag);
        worker.commit();
        
        
        return response[0][0].c_str();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}










void DBPlan::addFirstOfDayTwo(std::string tag) {
    try {
        pqxx::work worker(connectionObject);
        std::string query =
            "UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_ID = (SELECT ID FROM Veranstalter WHERE arbeitszeit <= 16 LIMIT 1) "
            "WHERE uhrzeit_id = 1 AND tag = $1;";
        pqxx::result response = worker.exec_params(query, tag);
        worker.commit();
      
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void DBPlan::addTwoHour(std::string tag, std::string stunde) {
    try {
        
        std::string prevStunde = std::to_string(std::stoi(stunde) - 1);

        std::cout  << " prevStunde: " << prevStunde << " Tag: " << tag << " stunde " << stunde << std::endl;
        pqxx::work worker(connectionObject);
        std::string query =
            "UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_id = (SELECT ID FROM Veranstalter "
               "WHERE arbeitszeit <= 16 "
               "AND(standort = (SELECT ort FROM Veranstaltung WHERE ID = (SELECT veranstaltung_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2)) "
                   "AND ID != (SELECT veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2)) "
              "ORDER BY random() LIMIT 1) "
           "WHERE uhrzeit_id = $3 AND tag = $4;";
        pqxx::result response = worker.exec_params(query, prevStunde, tag, stunde, tag);
        worker.commit();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void DBPlan::addFirstOfDayFour(std::string tag) {
    try {
        pqxx::work worker(connectionObject);
        std::string query =
            "UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_ID = (SELECT ID FROM Veranstalter WHERE arbeitszeit <= 14 LIMIT 1) "
            "WHERE uhrzeit_id = 1 AND tag = $1;";
        pqxx::result response = worker.exec_params(query, tag);
        worker.commit();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void DBPlan::addFourHour(std::string tag, std::string stunde) {
    try {
        
        std::string prevStunde = std::to_string(std::stoi(stunde) - 1);
        pqxx::work worker(connectionObject);
        std::string query =
           "UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_id = (SELECT ID FROM Veranstalter "
                "WHERE arbeitszeit <= 14 "
                "AND(standort = (SELECT ort FROM Veranstaltung WHERE ID = (SELECT veranstaltung_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2)) "
                    "AND ID != (SELECT veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2)) "
                "ORDER BY random() LIMIT 1) "
            "WHERE uhrzeit_id = $3 AND tag = $4;";
        pqxx::result response = worker.exec_params(query, prevStunde, tag, stunde, tag);
        worker.commit();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void DBPlan::upperHour(std::string tag, std::string stunde) {
    try {
        
        std::string nextStunde = std::to_string(std::stoi(stunde) + 1);

        std::cout << "tag: " << tag  << " stunde: " << stunde << " prevStunde " << nextStunde << std::endl;
        pqxx::work worker(connectionObject);
        std::string query =
            "UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_ID = (SELECT Veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2)"
            "WHERE uhrzeit_id = $3 AND tag = $2;";
        pqxx::result response = worker.exec_params(query, stunde, tag, nextStunde);
        worker.commit();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


void DBPlan::updateStandort(std::string tag, std::string stunde) {
    try {

      
        pqxx::work worker(connectionObject);
        std::string query =
            "UPDATE Veranstalter SET standort = (SELECT ort FROM Veranstaltung WHERE ID = (SELECT Veranstaltung_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2)) WHERE ID = (SELECT Veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2);";
        pqxx::result response = worker.exec_params(query, stunde, tag);
        worker.commit();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void DBPlan::incarbeitszeit(std::string tag, std::string stunde, std::string amount) {
    try {


        pqxx::work worker(connectionObject);
        
            std::string query =
            "UPDATE Veranstalter SET arbeitszeit = arbeitszeit + $1 WHERE ID = (SELECT Veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $2 AND tag = $3);";

        pqxx::result response = worker.exec_params(query,amount, stunde, tag);
        worker.commit();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void DBPlan::createPlan() {


    
    try {
        for (int tag = 1; tag < 6; tag++) {
            std::string tagStr = std::to_string(tag);
            for (int stunde = 1; stunde < 6; stunde++) {
                std::string stundeStr = std::to_string(stunde);
                //get dauer of next class
                
                if (std::stoi(getDauer(tagStr, stundeStr)) == 2) {
                    if (stunde == 1) {
                        addFirstOfDayTwo(tagStr);
                    }
                    else {
                        addTwoHour(tagStr, stundeStr);
                    }
                    updateStandort(tagStr, stundeStr);
                    incarbeitszeit(tagStr, stundeStr, "2");
                }
                else {
                    if (stunde == 1) {
                        addFirstOfDayFour(tagStr);
                        
                    }
                    else {
                        addFourHour(tagStr, stundeStr);
                    }
                    upperHour(tagStr, stundeStr);
                    incarbeitszeit(tagStr, stundeStr, "4");
                    updateStandort(tagStr, stundeStr);
                    stunde++;
                }

            }
            
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}


