#include "statement.h"

Statement::Statement() {
    statementNumber = 0;
    next = nullptr;

}

Statement::Statement(int stmtNum) {
    statementNumber = stmtNum;
    next = nullptr;
}

Statement::~Statement() {
}

void Statement::setNext(std::unique_ptr<Statement> &next) {
    this->next = std::move(next);
}

std::unique_ptr<Statement> &Statement::getNext() {
    return next;
}

int Statement::getStmtNum() {
    return statementNumber;
}


/** Let statement */

LetStatement::LetStatement():
    Statement() {
    type = LET;
}

LetStatement::LetStatement(int stmtNum, std::string var, Expression *exp):
    Statement(stmtNum) {
    type = LET;
    variable = var;
    this->exp = exp;
}

LetStatement::~LetStatement() {
    delete exp;
}

void LetStatement::execute(EvaluationContext & context) {
    context.setValue(variable, exp->eval(context));
}

std::string LetStatement::toString() {
    return std::to_string(statementNumber) + " LET\n " + variable + " = " + exp->toString();
}

/** Print statement */
PrintStatement::PrintStatement():
    Statement() {
    type = PRINT;
}

PrintStatement::PrintStatement(int stmtNum, Expression *exp):
    Statement(stmtNum) {
    type = PRINT;
    this->exp = exp;
}

PrintStatement::~PrintStatement() {
    delete exp;
}

void PrintStatement::execute(EvaluationContext & context) {
    std::cout << exp->eval(context)
                << std::endl;
}

std::string PrintStatement::toString() {
    return std::to_string(statementNumber) + " PRINT\n " + exp->toString();
}



