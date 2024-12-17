#ifndef PARSER_H
#define PARSER_H
#include <bits/stdc++.h>
#include "statement.h"
#include "tokenizer.h"
#include "exp.h"

//think parser as a factory class of statement
class Parser
{
public:
    Parser();
    ~Parser();
    Statement *getStatement(std::string &stmt);

private:
    Tokenizer* tk;
    Statement *parseImmediate(std::vector<Token> &tokens);
    Statement *parseStatement(std::vector<Token> &tokens,std::string stmt);


    Statement *parseLet(std::vector<Token> &tokens,std::string stmt);
    Statement *parsePrint(std::vector<Token> &tokens,std::string stmt);
    Statement *parseInput(std::vector<Token> &tokens);
    Statement *parseIf(std::vector<Token> &tokens);
    Statement *parseGoto(std::vector<Token> &tokens);
    Statement *parseEnd(std::vector<Token> &tokens);
    Statement *parseRem(std::vector<Token> &tokens);

    Expression *parseExp(std::vector<Token> &expTokens);


};

#endif // PARSER_H
