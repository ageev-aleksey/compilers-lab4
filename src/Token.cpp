//
// Created by nrx on 02.05.2020.
//

#include "Token.h"

bool Token::operator==(const Token &other) const{
    return (this->type == other.type) && (this->value == other.value);
}


std::ostream &operator<<(std::ostream &stream, const Token &token)
{
    switch(token.type) {
        case TokenType::ID:
            stream << "{ID|CONST, '" << token.value << "'}";
            break;
        case TokenType::RELATION:
            stream << "{RELATION, '" << token.value <<  "'}";
            break;
        case TokenType::CRBRACKET:
            stream << "{CRBRACKET, '" << token.value <<  "'}";
            break;
        case TokenType::ORBRACKET:
            stream << "{ORBRACKET, '" << token.value <<  "'}";
            break;
        case TokenType::SUM_OP:
            stream << "{SUM_OP, '" << token.value << "'}";
            break;
        case TokenType::MUL_OP:
            stream << "{MUL_OP, '" << token.value << "'}";
            break;
        case TokenType::END:
            stream << "{END, }";
            break;
        case TokenType::UNDEFINED:
            stream << "{UNDEFINED, '" << token.value << "'}";
            break;
}
return stream;
}

std::ostream &operator<<(std::ostream &stream, const int &token)
{
    switch(token) {
        case TokenType::ID:
            stream << "ID|CONST";
            break;
        case TokenType::RELATION:
            stream << "RELATION";
            break;
        case TokenType::CRBRACKET:
            stream << "CRBRACKET";
            break;
        case TokenType::ORBRACKET:
            stream << "ORBRACKET";
            break;
        case TokenType::SUM_OP:
            stream << "SUM_OP";
            break;
        case TokenType::MUL_OP:
            stream << "MUL_OP";
            break;
        case TokenType::END:
            stream << "END";
            break;
        case TokenType::UNDEFINED:
            stream << "UNDEFINED";
            break;
    }
    return stream;
}