//
// Created by Kekoapo'aono Montalbo on 9/18/19.
//

#ifndef PROJECT_1_TOKEN_H
#define PROJECT_1_TOKEN_H

#include <string>

enum tokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY,
    ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EndOfFile};

class Token {
public:
    Token();
    Token(tokenType newToken, std::string newString, int newLine) : nameOf(newToken), tokenString(newString), lineFound(newLine) {}
    std::string toString();
    tokenType getTokenType() {return nameOf; }
    std::string getTokenString() { return tokenString; }
private:
    tokenType nameOf;
    std::string tokenString;
    int lineFound;
};

#endif //PROJECT_1_TOKEN_H
