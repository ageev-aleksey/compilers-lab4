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
    Graph_t getGraph();
private:
    Lexer lexer;
    std::vector<std::vector<char>> table;
    Graph<std::string, Empty> g;
    void (*errorHandler)(char typeError);
};


#endif //LAB4_PARSER_H
