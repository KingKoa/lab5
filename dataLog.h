//
// Created by Kekoapo'aono Montalbo on 9/18/19.
//

#ifndef PROJECT_1_DATA_LOG_H
#define PROJECT_1_DATA_LOG_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class DataLog {
public:
    DataLog();
    DataLog(std::vector<Token*> *myProgram) : thisProgram(myProgram) { /*checkDataLogProgram();*/ }
private:
    std::vector<Token*> *thisProgram;
    void checkDataLogProgram();
    void parseScheme();
    void parseFacts();
    void parseRules();
    void parseQueries();
};

#endif //PROJECT_1_DATA_LOG_H
