#include "statement.h"

#include <utility>


Statement::Statement(int stmtNum) {
    statementNumber = stmtNum;
    type = ENDSTATE;
}

int Statement::getStmtNum() const {
    return statementNumber;
}


/** Let statement */

LetStatement::LetStatement():
    Statement() {
    type = LET;
    exp = nullptr;
}

LetStatement::LetStatement(int stmtNum, std::string var, Expression *exp):
    Statement(stmtNum),
    variable(std::move(var)) {
    type = LET;
    this->exp = exp;
}

LetStatement::~LetStatement() {
    delete exp;
}

void LetStatement::execute(SymbolTable & context) {
    context.setValue(variable, exp->eval(context));
}

std::string LetStatement::toString() {
    return std::to_string(statementNumber) + " LET\n " + variable + " = " + exp->toString();
}

/** Print statement */
PrintStatement::PrintStatement():
    Statement() {
    type = PRINT;
    exp = nullptr;
}

PrintStatement::PrintStatement(int stmtNum, Expression *exp):
    Statement(stmtNum) {
    type = PRINT;
    this->exp = exp;
}

PrintStatement::~PrintStatement() {
    delete exp;
}

void PrintStatement::execute(SymbolTable & context) {
    std::cout << exp->eval(context)
                << std::endl;
}

std::string PrintStatement::toString() {
    return std::to_string(statementNumber) + " PRINT\n " + exp->toString();
}



