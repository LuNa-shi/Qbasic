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
    ENDSTATE,
    REM
};

class Statement
{
public:
    explicit Statement(int stmtNum = 0);
    virtual ~Statement() = default;
    virtual void execute(SymbolTable & context) = 0;
    virtual std::string toString() = 0;
    int getStmtNum() const;


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
    void execute(SymbolTable & context) override;
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
    void execute(SymbolTable & context) override;
    std::string toString() override;

private:
    Expression *exp;
};



#endif // STATEMENT_H
