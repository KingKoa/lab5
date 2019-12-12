//
// Created by Kekoapo'aono Montalbo on 10/7/19.
//

#include "DatalogProgram.h"
DatalogProgram::~DatalogProgram()
{
    for (unsigned int i = 0; i < mySchemes.size(); ++i)
    {
        delete mySchemes.at(i);
    }

    for (unsigned int i = 0; i < myFacts.size(); ++i)
    {
        delete myFacts.at(i);
    }

    for (unsigned int i = 0; i < myQueries.size(); ++i)
    {
        delete myQueries.at(i);
    }

    for (unsigned int i = 0; i < myRules.size(); ++i)
    {
        delete myRules.at(i);
    }

}

std::string DatalogProgram::toStringScheme()
{
    std::string returnString = "";
    std::vector<std::string*> *theParams;
    returnString += "Scheme(";
    returnString += std::to_string(mySchemes.size());
    returnString += "):\n";
    for(unsigned int i = 0; i < mySchemes.size(); ++i)
    {
        returnString += "  ";
        returnString += mySchemes.at(i)->getName();
        returnString += "(";
        theParams = mySchemes.at(i)->getParams();
        for(unsigned int j = 0; j < theParams->size(); ++j)
        {
            returnString += *(theParams->at(j));
            if(j != theParams->size() - 1)
            {
                returnString += ",";
            }
        }
        returnString += ").\n";
    }

    return returnString;
}

std::string DatalogProgram::toStringFacts()
{
    std::string returnString = "";
    std::vector<std::string*> *theParams;
    returnString += "Facts(";
    returnString += std::to_string(myFacts.size());
    returnString += "):\n";
    for(unsigned int i = 0; i < myFacts.size(); ++i)
    {
        returnString += "  ";
        returnString += myFacts.at(i)->getName();
        returnString += "(";
        theParams = myFacts.at(i)->getParams();
        for(unsigned int j = 0; j < theParams->size(); ++j)
        {
            returnString += *(theParams->at(j));
            if(j != theParams->size() - 1)
            {
                returnString += ",";
            }
        }
        returnString += ").\n";
    }

    return returnString;
}

std::string DatalogProgram::toStringRules()
{
    std::string returnString = "";
    std::vector<Predicate> thePreds;

    returnString += "Rules(";
    returnString += std::to_string(myRules.size());
    returnString += "):\n";
    for(unsigned int i = 0; i < myRules.size(); ++i)
    {
        returnString += "  ";
        returnString += myRules.at(i)->getName().toString();
        returnString += " :- ";
        thePreds = myRules.at(i)->getPred();
        for(unsigned int j = 0; j < thePreds.size(); ++j)
        {
            returnString += (thePreds.at(j).toString());
            if(j != thePreds.size() - 1)
            {
                returnString += ",";
            }
        }
        returnString += ").\n";
    }

    return returnString;
}

std::string DatalogProgram::toStringQueries(){
    std::string returnString = "";
    std::vector<std::string*> *theParams;
    returnString += "Queries(";
    returnString += std::to_string(myQueries.size());
    returnString += "):\n";
    for(unsigned int i = 0; i < myQueries.size(); ++i)
    {
        returnString += "  ";
        returnString += myQueries.at(i)->getName();
        returnString += "(";
        theParams = myQueries.at(i)->getParams();
        for(unsigned int j = 0; j < theParams->size(); ++j)
        {
            returnString += *(theParams->at(j));
            if(j != theParams->size() - 1)
            {
                returnString += ",";
            }
        }
        returnString += ")?\n";
    }

    return returnString;
}
