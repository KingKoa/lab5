//
// Created by Kekoapo'aono Montalbo on 9/18/19.
//

#include "Scanner.h"

char Scanner::getTestChar()
{
    return testChar;
}

int Scanner::getCurLine()
{
    return curLine;
}

int Scanner::getNumTokenized()
{
    return numTokenized;
}

void Scanner::openFile()
{
    inputStream.open(fileName);
}

void Scanner::closeFile()
{
    inputStream.close();
}

std::vector<Token*> *Scanner::tokenize()
{
    std::vector<Token*> *foundTokens = new std::vector<Token*>;



    inputStream.get(testChar);

    while (!inputStream.eof())
    {
        Token* commaS;
        Token* periodS;
        Token* questionS;
        Token* leftParenS;
        Token* rightParenS;
        Token* collenS;
        Token* additionS;
        Token* multiS;
        Token* checkS;
        Token* idS;
        Token* commentS;

        commaS = CheckComma();
        periodS = CheckPeriod();
        questionS = CheckQuestionMark();
        leftParenS = CheckLeftParen();
        rightParenS = CheckRightParen();
        collenS = CheckColons();
        additionS = CheckAdditionSign();
        multiS = CheckMultiplicationSign();
        checkS = CheckString();
        idS = CheckId();
        commentS = CheckComment();

        if (commaS != NULL) { foundTokens->push_back(commaS); }
        else if (periodS != NULL) { foundTokens->push_back(periodS); }
        else if (questionS != NULL) { foundTokens->push_back(questionS); }
        else if (leftParenS != NULL) {  foundTokens->push_back(leftParenS); }
        else if (rightParenS != NULL) { foundTokens->push_back(rightParenS); }
        else if (collenS != NULL) { foundTokens->push_back(collenS); }
        else if (additionS != NULL) { foundTokens->push_back(additionS); }
        else if (multiS != NULL) { foundTokens->push_back(multiS); }
        else if (checkS != NULL) { foundTokens->push_back(checkS); }
        else if (idS != NULL) { foundTokens->push_back(idS); }
        else if (commentS != NULL) { foundTokens->push_back(commentS); }
        else { foundTokens->push_back(CheckUndefined()); }

        if (testChar == '\n')
        {
            ++curLine;
        }

        inputStream.get(testChar);
    }

    numTokenized++;
    Token* endOfFile = new Token(EndOfFile, "", curLine);
    foundTokens->push_back(endOfFile);
    closeFile();
    return foundTokens;
}

Token* Scanner::CheckComma()
{
    if (testChar == ',')
    {
        numTokenized++;
        Token* newToken = new Token(COMMA, ",", curLine);
        return newToken;
    }

    return nullptr;
}

Token* Scanner::CheckPeriod()
{
    if (testChar == '.')
    {
        numTokenized++;
        Token* newToken = new Token(PERIOD, ".", curLine);
        return newToken;
    }

    return nullptr;
}

Token* Scanner::CheckQuestionMark()
{
    if (testChar == '?')
    {
        numTokenized++;
        Token* newToken = new Token(Q_MARK, "?", curLine);
        return newToken;
    }

    return nullptr;
}

Token* Scanner::CheckLeftParen()
{
    if (testChar == '(')
    {
        numTokenized++;
        Token* newToken = new Token(LEFT_PAREN, "(", curLine);
        return newToken;
    }

    return nullptr;
}


Token* Scanner::CheckRightParen()
{
    if (testChar == ')')
    {
        numTokenized++;
        Token* newToken = new Token(RIGHT_PAREN, ")", curLine);
        return newToken;
    }

    return nullptr;
}

Token* Scanner::CheckColons()
{
    if (testChar == ':')
    {
        if (inputStream.peek() == '-')
        {
            numTokenized++;
            inputStream >> testChar;
            Token* newToken = new Token(COLON_DASH, ":-", curLine);
            return newToken;
        }

        numTokenized++;
        Token* newToken = new Token(COLON, ":", curLine);
        return newToken;
    }

    return nullptr;
}

Token* Scanner::CheckMultiplicationSign()
{
    if (testChar == '*')
    {
        numTokenized++;
        Token* newToken = new Token(MULTIPLY, "*", curLine);
        return newToken;
    }

    return nullptr;
}

Token* Scanner::CheckAdditionSign()
{
    if (testChar == '+')
    {
        numTokenized++;
        Token* newToken = new Token(ADD, "+", curLine);
        return newToken;
    }

    return nullptr;
}

Token* Scanner::CheckId()
{
    if (isalpha(testChar))
    {
        std::string inputString;
        inputString += testChar;

        while(isalnum(inputStream.peek()) && inputStream.peek() != '\n' && inputStream >> testChar && testChar != ' ')
        {
            inputString += testChar;
        }

        numTokenized++;

        if (inputString == "Schemes")
        {
            Token* newToken = new Token(SCHEMES, "Schemes", curLine);
            return newToken;
        }

        else if (inputString == "Facts")
        {
            Token* newToken = new Token(FACTS, "Facts", curLine);
            return newToken;
        }

        else if (inputString == "Rules")
        {
            Token* newToken = new Token(RULES, "Rules", curLine);
            return newToken;
        }

        else if (inputString == "Queries")
        {
            Token* newToken = new Token(QUERIES, "Queries", curLine);
            return newToken;
        }

        Token* newToken = new Token(ID, inputString, curLine);
        return newToken;
    }

    return nullptr;
}

Token* Scanner::CheckString()
{
    if (testChar == '\'')
    {
        int lineFound = curLine;

        std::string inputString;
        inputString += testChar;
        inputStream.get(testChar);
        inputString += testChar;

        while(testChar != '\'' || inputStream.peek() == '\'')
        {

            if(testChar == '\'' && inputStream.peek() == '\'') { inputString += testChar; inputStream.get(testChar); }

            if(testChar == '\n') { curLine++; }

            inputStream.get(testChar);

            if (inputStream.eof())
            {
                testChar = ' ';
                numTokenized++;
                Token* newToken = new Token(UNDEFINED, inputString, lineFound);
                return newToken;
            }

            inputString += testChar;
        }
        numTokenized++;
        Token* newToken = new Token(STRING, inputString, lineFound);
        return newToken;
    }

    return nullptr;
}

Token* Scanner::CheckComment()
{
    if (testChar == '#')
    {
        std::string returnString = "";
        returnString += testChar;
        int lineFound = curLine;

        if (inputStream.peek() == '|')
        {
            inputStream.get(testChar);
            returnString += testChar;
            inputStream.get(testChar);

            while(!(testChar == '|' && inputStream.peek() == '#'))
            {
                if (inputStream.eof())
                {
                    testChar = ' ';
                    numTokenized++;
                    Token* newToken = new Token(UNDEFINED, returnString, lineFound);
                    return newToken;
                }

                returnString += testChar;
                inputStream.get(testChar);
                if (testChar == '\n') { ++curLine; }
            }

            returnString += testChar;
            inputStream.get(testChar);
            returnString += testChar;
            numTokenized++;
            Token* newToken = new Token(COMMENT, returnString, lineFound);
            return newToken;
        }

        else
            {
                while (inputStream.peek() != EOF && inputStream.peek() != '\n')
                {
                    inputStream.get(testChar);
                    returnString += testChar;
                }

                numTokenized++;
                Token* newToken = new Token(COMMENT, returnString, lineFound);
                return newToken;
            }
    }

    return nullptr;
}

Token* Scanner::CheckUndefined()
{
    std::string testString;
    testString += testChar;
    if (testChar != '\n' && testChar != '\t' && testChar != '\v' && testChar != '\f' && testChar != '\r' && testChar != ' ')
    {
        numTokenized++;
        Token* newToken = new Token(UNDEFINED, testString, curLine);
        return newToken;
    }

    return nullptr;
}
