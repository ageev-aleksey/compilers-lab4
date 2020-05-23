//
// Created by nrx on 23.05.2020.
//

#include "Lexer.h"
#include <vector>
#include "Parser.h"




Parser::Parser(Lexer l, std::vector<std::vector<char>> t, void (*errorHandler)(char)) :
lexer(l), table(t), errorHandler(errorHandler)
{}

bool Parser::run() {
    const Token NT = {TokenType::NonTerminal, "E"};
    Token b = lexer.next();
    std::stack<Token> stack;
    stack.push({TokenType::END, "$"});
    Token a = stack.top();
    while(true) {
        if((stack.top().type == TokenType::END) && (b.type == TokenType::END)) {
            return true;
        }
        if((table[a.type][b.type] == '<') || (table[a.type][b.type] == '=')) {
            stack.push(b);
            b = lexer.next();
            a = stack.top();
        } else {
            if(table[a.type][b.type] == '>') {
                Token c;
                std::cout << "Свертка: ";
                do {
                    c = stack.top();
                    stack.pop();
                    a = stack.top();
                    conv.push(c);
                    std::cout <<  c.value <<  " " ;
                }while( (c.type == TokenType::NonTerminal)||
                ((stack.size() > 1) && (table[a.type][c.type] != '<')));
                std::cout << std::endl;
                //conv.push(node);
            } else {
                errorHandler(table[a.type][b.type]);
                return false;
            }
        }
        auto stack_print = stack;
        while(!stack_print.empty()) {
            auto el = stack_print.top();
            stack_print.pop();
            std::cout << el.value << "; ";
        }
        std::cout << std::endl;


    }
    return true;
}

std::stack<Token> Parser::get() {
    return conv;
}