#ifndef PROGRAM_H
#define PROGRAM_H
#include "statement.h"
#include <bits/stdc++.h>
class program
{
public:
    program();

private:
    std::unique_ptr<Statement> head;
    // std::unique_ptr<Statement> tail;
    std::map<int, Statement *> statementMap;
    int nextStatementNumber;

    void executeStatement(EvaluationContext &context, Statement *stmt);
    void appendStatement(Statement *stmt);
    void removeStatement(int stmtNum);




};

#endif // PROGRAM_H
