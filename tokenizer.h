#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <vector>

enum ExpType
{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    POW,
    LPAREN,
    RPAREN,
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
    std::vector<std::string> tokenize(std::string &str);
    std::vector<ExpToken> tokenizeExp(std::vector<std::string> &expTokens);

private:
    std::vector<std::string> tokens;

};

#endif // TOKENIZER_H
