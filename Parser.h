//
// Created by Kekoapo'aono Montalbo on 10/6/19.
//

#ifndef CS_236_PARSER_H
#define CS_236_PARSER_H

#include "Token.h"
#include <vector>
#include <iostream>
#include <string>
#include "DatalogProgram.h"
#include "Rules.h"

class Parser {
public:
    Parser();
    Parser(std::vector<Token*> *newTokens) : myTokens(newTokens)
    {
      myProgram = new DatalogProgram();
      validProg = checkProgram();
    }
    bool getValidProg() { return validProg; }
    Token* getBadToken() { return badToken; }
    DatalogProgram* getProg() { return myProgram; }
    std::vector<std::string*> *getDomain() { return &myDomain; }
private:
    DatalogProgram *myProgram;
    std::vector<Token*> *myTokens;
    std::vector<std::string*> myDomain;
    int curPos = 0;
    Token* badToken;
    bool validProg;

    bool checkProgram();
    void checkDataLogProg();
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void scheme();
    void fact();
    void rule();
    void query();
    void headPredicate();
    void headPredicate(Rule* myRule);
    void predicate();
    void predicate(Rule* myRule);
    void predicateList(std::vector<std::string*> *v);
    void predicateList(Rule* myRule);
    void parameterList(std::vector<std::string*> *v);
    void parameterList(std::vector<std::string*> *v, Rule* myRule);
    void stringList(std::vector<std::string*> *factList);
    void idList(std::vector<std::string*> *schemeList);
    void idList(std::vector<std::string*> *schemeList, Rule *myRule);
    void parameter();
    void parameter(std::vector<std::string*> *v);
    void parameter(std::string *myS, std::vector<std::string*> *v);
    void parameter(std::vector<std::string*> *v, Rule* myRule);
    void parameter(std::string *myS, std::vector<std::string*> *v, Rule* myRule);
    void expression();
    void expression(std::vector<std::string*> *v, Rule* myRule);
    void expression(std::string *myS, std::vector<std::string*> *v, Rule* myRule);
    void expression(std::vector<std::string*> *v);
    void expression(std::string *myS, std::vector<std::string*> *v);
    void op();
    void op(std::string *myS, std::vector<std::string*> *v, Rule* myRule);
    void op(std::string *myS, std::vector<std::string*> *v);
};


#endif //CS_236_PARSER_H
