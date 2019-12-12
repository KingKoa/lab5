#ifndef INTERPRETER_H
#define INTERPRETER_H

//#include <vector>
#include <string>
#include <map>
#include "Predicate.h"
#include "Relations.h"
#include "DataBase.h"
#include "Rules.h"

class Interpreter {
public:
    Interpreter() { }
    Interpreter(std::vector<Predicate*> dbSchemes, std::vector<Predicate*> dbFacts)
    {
        myDataBase.addSchemes(dbSchemes);
        myDataBase.addFacts(dbFacts);
    }
    Interpreter(DataBase newDataBase) { myDataBase = newDataBase; }
    std::string evalRules(std::vector<Rule*> myRules);

    std::string checkQueries(std::vector<Predicate*> myQueries);
private:
  DataBase myDataBase;
};

#endif //INTERPRETER_H
