#include "DBPlan.hpp"

DBPlan::DBPlan(std::string connStr) : DBHandler(connStr) {
};


void DBPlan::vertretung(std::string tag, std::string stunde, std::string dauer) {
    try {
        std::string prevStunde = std::to_string(std::stoi(stunde) - 1);
        std::string cap = std::to_string(18 - std::stoi(dauer));
        std::string nextStunde;
        std::string nextTag = tag;
        std::string prevTag = tag;
        if (dauer == "4") {
           
           nextStunde = std::to_string(std::stoi(stunde) + 2);
           std::cout << nextStunde << std::endl;
        }
        else {
           nextStunde = std::to_string(std::stoi(stunde) + 1);
           std::cout << nextStunde << std::endl;
        }

        if (prevStunde == "0") {
            prevStunde = "5";
            prevTag = std::to_string(std::stoi(tag) - 1);
            if (prevTag == "0") {
                prevTag = "5";
            }
        }

        if (nextStunde == "6") {
            nextStunde = "1";
            nextTag = std::to_string(std::stoi(tag)+1);
            if (nextTag == "6") {
                nextTag = "1";
            }
        }

        pqxx::work worker(connectionObject);

        
        std::string query =
            "UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_ID = "
            "(SELECT ID FROM Veranstalter WHERE ID != (SELECT Veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $1 AND tag = $2) "
            "AND ID != (SELECT Veranstalter_ID FROM Veranstalter_Veranstaltung_Uhrzeit WHERE uhrzeit_id = $3 AND tag = $4) LIMIT 1) WHERE uhrzeit_id = $5 AND tag = $6; ";
       

        pqxx::result response = worker.exec_params(query, prevStunde, prevTag, nextStunde, nextTag, stunde, tag);
       
        worker.commit();
        

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;

    }
}

void DBPlan::sucheVertretung(std::string tag, std::string stunde) {
    std::string dauer = getDauer(tag, stunde);
    vertretung(tag, stunde, dauer);
    incarbeitszeit(tag, stunde, dauer);

    if (dauer == "4") {
        upperHour(tag, stunde);
    }

 

}

void DBPlan::meldeKrank(std::string id, std::string tag, std::string stunde) {

    try {
        
        pqxx::work worker(connectionObject);
        std::string query =
            "UPDATE Veranstalter SET krank = TRUE WHERE ID = $1";

        pqxx::result response = worker.exec_params(query, id);
        worker.commit();
        
        sucheVertretung(tag, stunde);
        meldeGesund(id);

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;

    }
}


void DBPlan::meldeGesund(std::string id) {
    try {
        pqxx::work worker(connectionObject);
        std::string query =
            "UPDATE Veranstalter SET krank = FALSE WHERE ID = $1";

        pqxx::result response = worker.exec_params(query, id);
        worker.commit();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}




void DBPlan::deleteVeranstalterForeign(std::string id) {
    try {
        pqxx::work worker(connectionObject);
        std::string query =
            "UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_ID = NULL WHERE Veranstalter_ID = $1;";

        pqxx::result response = worker.exec_params(query, id);
        worker.commit();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void DBPlan::deleteVeranstalter(std::string id) {

    deleteVeranstalterForeign(id);
    
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


void DBPlan::deleteVeranstaltungForeign(std::string id) {
    try {
        pqxx::work worker(connectionObject);
        std::string query =
            "UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstaltung_ID = NULL WHERE Veranstalter_ID = $1;";

        pqxx::result response = worker.exec_params(query, id);
        worker.commit();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void DBPlan::deleteVeranstaltung(std::string id) {
    deleteVeranstaltungForeign(id);

    try {
        pqxx::work worker(connectionObject);
        std::string query =
            "DELETE FROM Veranstaltung WHERE ID = $1";

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
            "UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_ID = (SELECT ID FROM Veranstalter WHERE arbeitszeit <= 16 AND krank = FALSE LIMIT 1) "
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
               "WHERE arbeitszeit <= 16 AND krank = FALSE "
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
            "UPDATE Veranstalter_Veranstaltung_Uhrzeit SET Veranstalter_ID = (SELECT ID FROM Veranstalter WHERE arbeitszeit <= 14 AND krank = FALSE LIMIT 1) "
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
                "WHERE arbeitszeit <= 14 AND krank = FALSE "
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



std::vector<std::string> DBPlan::getPlan() {
    try {

        std::vector<std::string> plan;

        pqxx::work worker(connectionObject);

        std::string query =
            "SELECT tag, u.anfangszeit, u.endzeit, o.ort, o.name, v.name, v.ID FROM Veranstalter_Veranstaltung_Uhrzeit LEFT JOIN Veranstalter v ON Veranstalter_Veranstaltung_Uhrzeit.veranstalter_ID = v.ID "
            "LEFT JOIN Uhrzeit u ON Veranstalter_Veranstaltung_Uhrzeit.uhrzeit_ID = u.ID "
            "LEFT JOIN Veranstaltung o ON Veranstalter_Veranstaltung_Uhrzeit.veranstaltung_ID = o.ID "
            "ORDER BY tag, uhrzeit_ID;";

        pqxx::result response = worker.exec(query);
        worker.commit();

        for (const auto& row : response) {
            std::string rowstring;
            for (const auto& col : row) {
                rowstring.append(col.c_str());
                rowstring.append(" , ");
            }
            plan.push_back(rowstring);
            
        }

        return plan;
       

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}



