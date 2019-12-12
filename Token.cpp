//
// Created by Kekoapo'aono Montalbo on 9/18/19.
//    enum tokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY,
//    ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EndOfFile};

#include "Token.h"

std::string Token::toString()
{
    switch (nameOf)
    {
        case COMMA:
            return "(COMMA,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case PERIOD:
            return "(PERIOD,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case Q_MARK:
            return "(Q_MARK,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case LEFT_PAREN:
            return "(LEFT_PAREN,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case RIGHT_PAREN:
            return "(RIGHT_PAREN,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case COLON:
            return "(COLON,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case COLON_DASH:
            return "(COLON_DASH,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case MULTIPLY:
            return "(MULTIPLY,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case ADD:
            return "(ADD,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case SCHEMES:
            return "(SCHEMES,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case FACTS:
            return "(FACTS,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case RULES:
            return "(RULES,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case QUERIES:
            return "(QUERIES,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case ID:
            return "(ID,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case STRING:
            return "(STRING,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case COMMENT:
            return "(COMMENT,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case UNDEFINED:
            return "(UNDEFINED,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        case EndOfFile:
            return "(EOF,\"" + tokenString + "\"," + std::to_string(lineFound) + ")";
        default:
            return "";
    }
}
