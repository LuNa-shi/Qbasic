#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <bits/stdc++.h>

enum TokenType
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
    std::vector<Token> tokenize(std::string &str);
    std::vector<ExpToken> tokenizeExp(std::vector<Token> &expTokens);

private:
    std::vector<std::string> tokens;

};

#endif // TOKENIZER_H
