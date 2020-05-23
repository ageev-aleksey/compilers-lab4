//
// Created by nrx on 02.05.2020.
//

#ifndef LAB3_LEXER_H
#define LAB3_LEXER_H
#include "Token.h"
#include "Option.h"
#include <string>
#include <list>
enum LexerError {
    END_OF_TEXT,
    NOT_ERROR
};

class Lexer {
public:
    Lexer(const std::string &str);
    Lexer(const Lexer &lexer);

    Token next();
    Token get();
    size_t line();
    size_t column();
    void back();

private:
    Token makeToken(int);
    Option<LexerError> isToken(const std::string &str);
    bool isSpace(const char &v);

    struct token_itr {
        std::string::iterator start;
        std::string::iterator end;
        size_t start_column;
        void step();
        std::string get();

    };
    std::string text;
    token_itr current;
    token_itr before;
    size_t current_line;
    int before_type;
};



#endif //LAB3_LEXER_H
