#include "program.h"

Program::Program() {}

Program::~Program() {}

void Program::executeStatement(SymbolTable &context, Statement *stmt)
{
    stmt->execute(context);
}

void Program::appendStatement(Statement *stmt)
{
    return;
}

void Program::removeStatement(int stmtNum)
{
    return;
}

std::string Program::toString()
{
    return nullptr;
}

