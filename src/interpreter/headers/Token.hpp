/*
Author: R. Baltrusch
*/

#pragma once
#ifndef TOKEN_H
#define TOKEN_H

#include <any>
#include <map>
#include <deque>
#include <vector>
#include <string>
#include <memory>

#include "Value.hpp"

struct ExpectedToken
{
    std::vector<int> types{};
    int run_order{};
    bool optional{};
};

class BaseToken;
class TokenFactory;
class Interpreter;

typedef std::any *(*ValueFactory)(void);
typedef void *(*RunFunction)(Interpreter);

class Token
{
protected:
    static std::vector<ExpectedToken> expectedTokens;
    static ValueFactory *valueFactory;
    static TokenFactory *tokenFactory;
    std::any value;
    int line;
    int run_order;
    std::vector<Token> tokens;
    std::deque<ExpectedToken> expectedTokensCopy;

public:
    Token(std::any value, int line);
    void print(void);
    void run(Interpreter &interpreter);
    bool checkOptionalToken(Token &token);
    void addToken(Token &token);
    std::vector<Token> popTokens(std::deque<std::shared_ptr<Token>> &tokens){};
    void updateTokenFactory(TokenFactory &tokenFactory){};
    void setValue(std::any *value);
    std::any getValue(void);
    bool getFull(void);
    bool getSatisfied(void);

protected:
    void runSelf(Interpreter &interpreter){};
    std::vector<RunFunction> getRunFunctions(void);
    void checkTypes(Token &token);
};

template <class T>
std::unique_ptr<Token> create(std::any value, int line)
{
    return std::unique_ptr<T>(new T(value, line));
};

typedef std::unique_ptr<Token> (*TokenConstructor)(std::any value, int line);
typedef std::map<std::string, TokenConstructor> ConstructorMap;

#endif
