#include "statement.h"

#include <utility>


Statement::Statement(int stmtNum, std::string stmt) {
    statementNumber = stmtNum;
    statementText = std::move(stmt);
    type = ENDSTATE;
}

int Statement::getStatementNum() const {
    return statementNumber;
}

std::string Statement::toString() {
    return statementText;
}

/** Let statement */

LetStatement::LetStatement():
    Statement() {
    type = LET;
    exp = nullptr;
}

LetStatement::LetStatement(int stmtNum, std::string var, Expression *exp, std::string stmt):
    Statement(stmtNum,stmt),
    variable(std::move(var)) {
    type = LET;
    this->exp = exp;
}

LetStatement::~LetStatement() {
    delete exp;
}

void LetStatement::execute(RuntimeState & rState) {
    rState.context->setValue(variable, exp->eval(*rState.context));
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

PrintStatement::PrintStatement(int stmtNum, Expression *exp, std::string stmt):
    Statement(stmtNum,stmt) {
    type = PRINT;
    this->exp = exp;
}

PrintStatement::~PrintStatement() {
    delete exp;
}

void PrintStatement::execute(RuntimeState & rState) {
    std::cout << exp->eval(*rState.context)
                << std::endl;
}

std::string PrintStatement::toString() {
    return std::to_string(statementNumber) + " PRINT\n " + exp->toString();
}



