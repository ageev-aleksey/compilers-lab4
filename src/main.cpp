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



void errorHandler(char typeError) {
    std::cout << "ERROR: ";
    std::cout << typeError << " ";
    switch(typeError) {
        case '0':
            std::cout << "между аргументами отсутсвует оператор" << std::endl;
            break;
        case '1':
            std::cout  << "между аргументом и открывающейся скобкой должен быть оператор" << std::endl;
            break;
        case '2':
            std::cout  << "две и более операций отношения не могут идти подряд" << std::endl;
            break;
        case '3':
            std::cout  << "после операции отношения не хватает аргумента " << std::endl;
            break;

        case '4':
            std::cout << "Забыта заырывающая скобка" << std::endl;
            break;
        case '5':
            std::cout << "после закрывающей скобки должен идти оператор" << std::endl;
            break;
        case '6':
            std::cout << "между с   кобками необходим оператор" << std::endl;
            break;
        case '7':
            std::cout << "Забыта открывающая скобка" << std::endl;
        case '8':
            std::cout << "Пустой ввод" << std::endl;
    }

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
    auto s = parser.get();
    std::cout << "Обратная польская запись: " << std::endl;
    while(!s.empty()) {
        Token t = s.top();
        s.pop();
        if(t.type != TokenType::ORBRACKET && t.type != TokenType::CRBRACKET) {
            std::cout << t.value << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}