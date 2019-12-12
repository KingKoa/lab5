//
// Created by Kekoapo'aono Montalbo on 9/18/19.
//

#ifndef PROJECT_1_SCANNER_H
#define PROJECT_1_SCANNER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Token.h"

class Scanner {
public:
    Scanner();
    Scanner(std::string inFileName) { fileName = inFileName; openFile(); }
    std::vector<Token*> *tokenize();
    char getTestChar();
    int getCurLine();
    int getNumTokenized();
    void openFile();
    void closeFile();

private:
    char testChar;
    int curLine = 1;
    int numTokenized = 0;
    std::string fileName;
    std::ifstream inputStream;

    Token* CheckComma();
    Token* CheckPeriod();
    Token* CheckQuestionMark();
    Token* CheckLeftParen();
    Token* CheckRightParen();
    Token* CheckColons();
    Token* CheckMultiplicationSign();
    Token* CheckAdditionSign();
    Token* CheckId();
    Token* CheckString();
    Token* CheckComment();
    Token* CheckUndefined();
};

#endif //PROJECT_1_SCANNER_H
