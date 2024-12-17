#ifndef STATEMENT_H
#define STATEMENT_H
#include <bits/stdc++.h>
#include "exp.h"
#include "context.h"


enum StatementType
{
    LET,
    PRINT,
    INPUT,
    IF,
    GOTO,
    ENDSTAT,
    REM
};

class Statement
{
public:
    Statement();
    Statement(int stmtNum);
    virtual ~Statement();
    virtual void execute(EvaluationContext & context) = 0;
    virtual std::string toString() = 0;
    void setNext(std::unique_ptr<Statement> &next); //will be used by program class
    std::unique_ptr<Statement> &getNext();
    int getStmtNum();
    std::unique_ptr<Statement> next;

protected:
    int statementNumber;    
    StatementType type;
};

class LetStatement : public Statement
{
public:
    LetStatement();
    LetStatement(int stmtNum, std::string var, Expression *exp);
    ~LetStatement() override;
    void execute(EvaluationContext & context) override;
    std::string toString() override;


private:
    std::string variable;
    Expression *exp;
};

class PrintStatement : public Statement
{
public:
    PrintStatement();
    PrintStatement(int stmtNum, Expression *exp);
    ~PrintStatement() override;
    void execute(EvaluationContext & context) override;
    std::string toString() override;

private:
    Expression *exp;
};



#endif // STATEMENT_H
