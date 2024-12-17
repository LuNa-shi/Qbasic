#ifndef PROGRAM_H
#define PROGRAM_H
#include "statement.h"
#include <bits/stdc++.h>
class Program
{
public:
    Program();
    ~Program();
    void executeStatement(SymbolTable &context, Statement *stmt);
    void appendStatement(Statement *stmt);
    void removeStatement(int stmtNum);
    std::string toString();


private:
    std::unique_ptr<Statement> head;
    // std::unique_ptr<Statement> tail;
    std::map<int, Statement *> statementMap;

};

#endif // PROGRAM_H
