//
// Created by nrx on 02.05.2020.
//

#ifndef LAB3_TOKEN_H
#define LAB3_TOKEN_H
#include <string>
#include <ostream>

struct TokenType {
    static const inline int ORBRACKET = 4;
    static const inline int CRBRACKET = 5;
    static const inline int RELATION  = 3;
    static const inline int SUM_OP    = 1;
    static const inline int MUL_OP    = 2;
    static const inline int ID        = 0;
    static const inline int CONST     = 0;
    static const inline int END       = 6;
    static const inline int UNDEFINED = 7;
    static const inline int NonTerminal = 8;
};

struct Token {
    int type;
    std::string value;
    bool operator==(const Token &other) const;
};

std::ostream &operator<<(std::ostream &stream, const int &token);
std::ostream &operator<<(std::ostream &stream, const Token &token);
#endif //LAB3_TOKEN_H
