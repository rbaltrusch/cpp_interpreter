/*
Author: R. Baltrusch
*/

#pragma once
#ifndef LEXER_H
#define LEXER_H

#include <deque>
#include <string>
#include <memory>

#include "TokenFactory.hpp"

class Lexer
{

    TokenFactory &tokenFactory;

public:
    Lexer(TokenFactory &tokenFactory);
    std::deque<std::shared_ptr<Token>> lex(std::string &text);

protected:
    static std::deque<std::string> split(std::string &text);
};

#endif
