#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <bits/stdc++.h>

enum class TokenType
{
    NUMBER,
    OPERATOR,
    VARIABLE,
    LPAREN,
    RPAREN,
    EQUALS,
    LESS,
    GREATER
};

struct Token
{
    TokenType type;
    std::string value;
};


enum ExpType
{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    POW,
    LEFT_PAREN,
    RIGHT_PAREN,
    NUM,
    VAR,
    END
};

struct ExpToken
{
    ExpType type;
    std::string value;
    int precedence;
};

class Tokenizer
{
public:
    Tokenizer();
    std::vector<Token> Tokenizer::tokenize(std::string &str);
    std::vector<ExpToken> Tokenizer::tokenizeExp(std::vector<Token> &expTokens);

private:
    std::vector<std::string> tokens;

};

#endif // TOKENIZER_H
