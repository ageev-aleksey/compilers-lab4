//
// Created by nrx on 23.05.2020.
//

#ifndef LAB4_PARSER_H
#define LAB4_PARSER_H

#include "Lexer.h"
#include <vector>
#include "Graph.h"

class Parser {
public:
    using Graph_t =Graph<std::string, Empty>;
    Parser(Lexer l, std::vector<std::vector<char>> t, void (*errorHandler)(char typeError));
    bool run();
    std::stack<Token> get();
private:
    Lexer lexer;
    std::stack<Token> conv;
    std::vector<std::vector<char>> table;
    void (*errorHandler)(char typeError);
};


#endif //LAB4_PARSER_H
