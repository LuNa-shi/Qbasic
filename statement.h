#ifndef STATEMENT_H
#define STATEMENT_H
#include <bits/stdc++.h>
#include "exp.h"



enum StatementType
{
    LET,
    PRINT,
    INPUT,
    IF,
    GOTO,
    ENDSTATE,
    REM
};

class Statement
{
public:
    Statement() = default;
    Statement(int stmtNum,std::string stmt);
    virtual ~Statement() = default;
    virtual void execute(RuntimeState & rState) = 0;
    virtual std::string toString();
    int getStatementNum() const;


protected:
    int statementNumber;
    std::string statementText;
    StatementType type;
};

class LetStatement : public Statement
{
public:
    LetStatement();
    LetStatement(int stmtNum, std::string var, Expression *exp, std::string stmt);
    ~LetStatement() override;
    void execute(RuntimeState & rState) override;
    std::string toString() override;


private:
    std::string variable;
    Expression *exp;
};

class PrintStatement : public Statement
{
public:
    PrintStatement();
    PrintStatement(int stmtNum, Expression *exp, std::string stmt);
    ~PrintStatement() override;
    void execute(RuntimeState & rState) override;
    std::string toString() override;

private:
    Expression *exp;
};



#endif // STATEMENT_H
