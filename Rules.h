//
// Created by Kekoapo'aono Montalbo on 10/7/19.
//

#ifndef LAB2_RULES_H
#define LAB2_RULES_H

#include <vector>
#include "Predicate.h"

class Rule {
public:
    Rule() {}
    void addRulesName(Predicate *newName) { rulesName = *newName; }
    void addList(Predicate *newPred) { predList.push_back(*newPred); }
    Predicate getName() { return rulesName; }
    std::vector<Predicate> getPred() { return predList; }
    std::string toString() {
        std::string returnString = "";
        returnString += rulesName.toString();
        returnString += " :- ";
        for(unsigned int i = 0; i < predList.size(); ++i)
        {
            returnString += predList.at(i).toString();
            if(i != predList.size() - 1) {
                returnString += ",";
            }

        }
        returnString += ".\n";
        return returnString;
    }
private:
    Predicate rulesName;
    std::vector<Predicate> predList;
};

#endif //LAB2_RULES_H
