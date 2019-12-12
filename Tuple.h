#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>
#include "Predicate.h"

class Tuple : public std::vector<std::string> {
public:
    Tuple() {}

    std::string toString() const
    {
      std::string returnString = "( ";

      for(unsigned int i = 0; i < this->size(); i++)
      {
        returnString += this->at(i);
        returnString += " ";
      }

      returnString += ")";

      return returnString;
    }
};

#endif //TUPLE_H
/*
    bool operator == (Tuple compare)
    {
      std::vector<std::string*> *otherData = compare.getData();

      for(unsigned int i = 0; i < this->tupData->size(); ++i)
      {
        if(*(this->tupData->at(i)) != *(otherData->at(i)))
        {
          return false;
        }
      }
      return true;
    }

    bool operator < (Tuple compare)
    {
      std::vector<std::string*> *otherData = compare.getData();

      for(unsigned int i = 0; i < this->tupData->size(); ++i)
      {
        if(*(this->tupData->at(i)) < *(otherData->at(i)))
        {
          return true;
        }
      }

      return false;
    }
*/