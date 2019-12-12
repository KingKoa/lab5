//
// Created by Kekoapo'aono Montalbo on 10/7/19.
//

#ifndef LAB2_PREDICATE_H
#define LAB2_PREDICATE_H

#include <vector>
#include "Token.h"

class Predicate {
public:
    Predicate()
    {
      parmList = new std::vector<std::string*>;
      predName = new std::string();
    }
    Predicate(std::vector<std::string*> *newPred)
    {
        parmList = new std::vector<std::string*>;
        predName = newPred->at(0);

        for (unsigned int i = 1; i < newPred->size(); ++i)
        {
            parmList->push_back(newPred->at(i));
        }
    }

    std::string getName() { return *predName; }
    std::vector<std::string*> *getParams() { return parmList; }
    std::string toString()
    {
          std::string returnString = "";
          returnString += *predName;
          returnString += "(";
              for(unsigned int j = 0; j < parmList->size(); ++j)
              {
                  returnString += *(parmList->at(j));
                  if(j != parmList->size() - 1)
                  {
                      returnString += ",";
                  }
              }
              returnString += ")";


          return returnString;
    }
private:
    std::string *predName;
    std::vector<std::string*> *parmList;
};


#endif //LAB2_PREDICATE_H
