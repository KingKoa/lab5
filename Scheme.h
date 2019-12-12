#ifndef SCHEME_H
#define SCHEME_H

#include <vector>
#include <string>
#include "Predicate.h"

class Scheme {
public:
    Scheme() { schemeName = ""; schemeAttributes = new std::vector<std::string*>; }
    std::string getName() { return schemeName; }
    void setName(std::string newName) { schemeName = newName; }
    std::vector<std::string*> *getAttributes() { return schemeAttributes; }
    std::string *getAttributesAt(int i) { return schemeAttributes->at(i); }
    void setAttributes(std::vector<std::string*> *newAttributes) { schemeAttributes = newAttributes; }
    void setAttribute(std::string* newAttribute, unsigned int index) { schemeAttributes->at(index) = newAttribute; }
    void insertAttribute(std::string* newAttribute, unsigned int index)
    {
        if (schemeAttributes->size() > index) {
            schemeAttributes->insert(schemeAttributes->begin() + index, newAttribute);
        }
        else
        {
            schemeAttributes->push_back(newAttribute);
        }
    }
    void addAttribute(std::string *newAttribute) { schemeAttributes->push_back(newAttribute); }
    std::string toString()
    {
      std::string returnString = schemeName;
      returnString += "( ";
      for (unsigned int i = 0; i < schemeAttributes->size(); i++)
      {
        returnString += *schemeAttributes->at(i);
        returnString += " ";
      }

      returnString += ")";
      return returnString;
    }

private:
    std::string schemeName;
    std::vector<std::string*> *schemeAttributes;

};

#endif //SCHEME_H
