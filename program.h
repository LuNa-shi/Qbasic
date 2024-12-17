#pragma once
#ifndef PROGRAM_H
#define PROGRAM_H
#include "statement.h"
#include "runtimestate.h"
#include <bits/stdc++.h>
class Program
{
public:
    Program();
    ~Program();
    void executeStatement(SymbolTable &context, Statement *stmt);
    void appendStatement(Statement *stmt);
    void removeStatement(int stmtNum);
    Statement* getStatement(int stmtNum);
    Statement* getNextStatement(int stmtNum);
    int getNextStatementNum(int stmtNum);
    [[nodiscard]] std::vector<std::string> toString() const;
    Statement* getFirstStatement();
    void run();

private:

    std::list<Statement *> statementList;
    std::map<int, Statement *> statementMap;
    RuntimeState *runtimeState;

};

#endif // PROGRAM_H
