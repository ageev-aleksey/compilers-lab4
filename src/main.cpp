//
// Created by nrx on 23.05.2020.
//
#include "Lexer.h"
#include "Graph.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <GraphToDOT.h>
#include <utility>
#include "Parser.h"

/*Таблица отношений приоритетов
*/std::vector<std::vector<char>> table =
     /*                                              <, >,
      *                                             <=, >=,
      *                   $id,$cons;  +, -;  *, /;  <>, ==;  (;  );   $*/
 /*$id, $const*/    {     {  '0',      '>',   '>',    '>',  '1','>', '>'},
/*+, -*/                  {  '<',      '>',   '<',    '>',  '<','>', '>'},
/**, /*/                  {  '<',      '>',   '>',    '>',  '<','>', '>'},
/*<, >, <=, >=, <>, ==*/  {  '<',      '<',   '<',    '2',  '<','3', '>'},
/*(*/                     {  '<',      '<',   '<',    '<',  '<','=', '4'},
/*)*/                     {  '5',      '>',   '>',    '>',  '6','>', '>'},
/*$*/                     {  '<',      '<',   '<',    '<',  '<','7', '8'},};

std::string rpnFromGraph(Graph<std::string, Empty> graph) {
    using Graph_t = Graph<std::string, Empty>;
    std::string res;
    std::stack<int> stack;
    std::stack<int> parents;
    stack.push(graph.lastNode().getIndex());
    parents.push(-1);
    parents.push(-1);
    while(!stack.empty()) {
        int n = stack.top();
        stack.pop();
        int p = parents.top();
        parents.pop();
        int before_parent = parents.top();
        auto node = graph.getNodeByIndex(n);
        if(node.getLinks().empty()) {
            res.append(node.getData());
        } else {
            for(Graph_t::Link &l : node.getLinks()) {
                stack.push(l.node.getIndex());
                parents.push(n);
            }
        }

        if(p != before_parent) {
            if(graph.getNodeByIndex(p).getData() != "E")
            res.append(graph.getNodeByIndex(p).getData());
        }

    }

    return res;

}

void errorHandler(char typeError) {

}

int main(int argc, char **argv){
    if(argc < 2) {
        std::cout << "Необходимо передать в качестве арумента путь к файлу" << std::endl;
        return -1;
    }
    std::ifstream file(argv[1]);
    if(!file.is_open()) {
        std::cout << "Не удалось открыть файл: " << argv[1] << std::endl;
        return -2;
    }
    std::string source;
    std::stringstream str;
    str << file.rdbuf();
    source = str.str();
    Lexer lexer(source);
    Parser parser(lexer, table, errorHandler);
//    if(!parser.run()) {
//        std::cout << "error" << std::endl;
//        return -3;
//    }
    parser.run();
    auto graph = parser.getGraph();
    saveImageGV(graphToDOT(graph), "graph");
    std::cout << rpnFromGraph(graph) << std::endl;
    return 0;
}