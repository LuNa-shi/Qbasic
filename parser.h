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
    Expression *parseExp(std::vector<std::string> &expTokens);
    Statement *parseLet(std::vector<std::string> &tokens);
    Statement *parsePrint(std::vector<std::string> &tokens);
    Statement *parseInput(std::vector<std::string> &tokens);
    Statement *parseIf(std::vector<std::string> &tokens);
    Statement *parseGoto(std::vector<std::string> &tokens);
    Statement *parseEnd(std::vector<std::string> &tokens);
    Statement *parseRem(std::vector<std::string> &tokens);

};

#endif // PARSER_H
