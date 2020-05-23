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
    std::stack<std::pair<typename Graph_t::iterator, Token>> stack;
    std::stack<typename Graph_t::iterator> conv;
    auto root = g.addNodeInBack("<program>");
    stack.push({root, {TokenType::END, "$"}});
    std::pair<typename Graph_t::iterator, Token> a = stack.top();
    while(true) {



        if((stack.top().second.type == TokenType::END) && (b.type == TokenType::END)) {
            return true;
        }
        if((table[a.second.type][b.type] == '<') || (table[a.second.type][b.type] == '=')) {

            auto node = g.addNodeInBack(b.value);

            stack.push({node, b});
            b = lexer.next();
            a = stack.top();
        } else {
            if(table[a.second.type][b.type] == '>') {
                auto node = g.addNodeInBack(NT.value);
               // g.addLink(a.first, c.first, Empty{});
                std::pair<typename Graph_t::iterator, Token> c;
                std::cout << "Свертка: ";
                do {
                    c = stack.top();
                    stack.pop();
                    a = stack.top();

                    if(c.second.type == TokenType::MUL_OP || c.second.type == TokenType::SUM_OP) {
                        auto v1 = conv.top();
                        conv.pop();
                        auto v2 = conv.top();
                        conv.pop();
                        g.addLink(node, v1, Empty{});
                        g.addLink(node, c.first, Empty{});
                        g.addLink(node, v2, Empty{});

                    } else g.addLink(node, c.first, Empty{});
                    std::cout <<  c.second.value <<  " " ;
                }while( (c.second.type == TokenType::NonTerminal)||
                ((stack.size() > 1) && (table[a.second.type][c.second.type] != '<')));
                std::cout << std::endl;
                conv.push(node);
            } else {
                errorHandler(table[a.second.type][b.type]);
                return false;
            }
        }
        auto stack_print = stack;
        while(!stack_print.empty()) {
            auto el = stack_print.top();
            stack_print.pop();
            std::cout << el.second.value << "; ";
        }
        std::cout << std::endl;


    }
    return true;
}

Graph<std::string, Empty> Parser::getGraph() {
    return g;
}