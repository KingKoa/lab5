//
// Created by Kekoapo'aono Montalbo on 10/7/19.
//

#ifndef LAB2_DATALOGPROGRAM_H
#define LAB2_DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rules.h"
#include <string>
#include <iostream>

class DatalogProgram {
public:
    DatalogProgram() {}
    ~DatalogProgram();
    void addScheme(std::vector<std::string*> *stringList) { mySchemes.push_back(new Predicate(stringList)); }
    std::string toStringScheme();
    void addFacts(std::vector<std::string*> *stringList) { myFacts.push_back(new Predicate(stringList)); }
    std::string toStringFacts();
    void addRule(Rule* newRule) { myRules.push_back(newRule); }
    std::string toStringRules();
    void addQuery(std::vector<std::string*> *stringList) { myQueries.push_back(new Predicate(stringList)); }
    std::string toStringQueries();
    std::vector<Predicate*> getSchemes() { return mySchemes; }
    std::vector<Predicate*> getFacts() { return myFacts; }
    std::vector<Rule*> getRules() { return myRules; }
    std::vector<Predicate*> getQueries() { return myQueries; }

private:
    std::vector<Predicate*> mySchemes;
    std::vector<Predicate*> myFacts;
    std::vector<Rule*> myRules;
    std::vector<Predicate*> myQueries;

};


#endif //LAB2_DATALOGPROGRAM_H
