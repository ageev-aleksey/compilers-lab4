

#include "Lexer.h"
#include "Token.h"
#include "Option.h"
#include <iostream>
#include <Lexer.h>

Lexer::Lexer(const std::string &text) {
    this->text = text;
    current.start = this->text.begin();
    current.end = current.start;
    current.start_column = 1;
    before = current;
    current_line = 1;
}

Lexer::Lexer(const Lexer &lexer) {
    text = lexer.text;
    current = lexer.current;
    before = lexer.before;
    current_line = lexer.current_line;
}

Token Lexer::makeToken(int type) {
    before = current;
    current.step();
    before_type = type;
    Token tok = {before_type, before.get()};
    before.end = before.start;
    return tok;
}

Option<LexerError> Lexer::isToken(const std::string &str) {
    bool isDetected = true;
    auto state = current.end;
    for(size_t i = 0; i < str.size(); i++) {
        if(current.end == text.end() || (++current.end) == text.end()) {
            current.end = state;
            return Option<LexerError>(END_OF_TEXT, true);
        }
        if(*current.end != str[i]) {
            isDetected = false;
            current.end = state;
            break;
        }
    }

    return Option<LexerError>(NOT_ERROR, isDetected);
}

bool Lexer::isSpace(const char &v) {
    if(v == '\n') {
        current_line += 1;
        current.start_column = 0;
        return  true;
    }
    return (v == ' ') || (v == '\t') || (v == '\r');
}

Token Lexer::get() {
    this->back();
    Token tok = this->next();
    return tok;
}

size_t Lexer::line() {
    return current_line;
}

size_t Lexer::column() {
    return before.start_column;
}

Token Lexer::next() {
    Token token;
    while((current.end != text.end())
        && (isSpace(*current.end))) {
        current.step();
    }
    if ((current.end == text.end()) || (*current.end == '\0')) {
        return {TokenType::END, ""};
    }

    switch (*current.end) {
        case '(':
            token =  makeToken(TokenType::ORBRACKET);
            break;
        case ')':
            token = makeToken(TokenType::CRBRACKET);
            break;
        case '<':
            if(!(*(++current.end) == '=' || *current.end == '>'))
                --current.end;
            token =  makeToken(TokenType::RELATION);
            break;
        case '>':
            if(*(++current.end) != '=')
                --current.end;
            token = makeToken(TokenType::RELATION);
            break;
        case '=':
            if(*(++current.end) == '=') {
                token = makeToken(TokenType::RELATION);
                break;
            }
            token = makeToken(TokenType::UNDEFINED);
            break;
        case '+':
        case '-':
            token = makeToken(TokenType::SUM_OP);
            break;
        case '*':
        case '/':
            token = makeToken(TokenType::MUL_OP);
            break;
        case '$': {
            const std::string id("id");
            const std::string _const("const");
            Option<LexerError> res = isToken(id);
            if (res)  {
                token =  makeToken(TokenType::ID);
                break;
            }
            if(res.get() != NOT_ERROR) {
                token = makeToken(TokenType::UNDEFINED);
            }
            res = isToken(_const);
            if(res) {
                token =  makeToken(TokenType::CONST);
                break;
            }
            token = makeToken(TokenType::UNDEFINED);
            break;
        }

        default:
            token =  makeToken(TokenType::UNDEFINED);
    }

    return token;

}

void Lexer::back() {
    current = before;
}

void Lexer::token_itr::step() {
    end++;
    start_column += std::distance(start, end);
    start = end;
}

std::string Lexer::token_itr::get() {
    std::string res;
    std::string::iterator tmp = end;
    tmp++;
    std::copy(start, tmp, std::back_inserter(res));
    return res;
}