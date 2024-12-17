#include "program.h"

Program::Program() {}

Program::~Program() {}

void Program::executeStatement(EvaluationContext &context, Statement *stmt)
{
    stmt->execute(context);
}

void Program::appendStatement(Statement *stmt)
{
    if (head == nullptr)
    {
        head = std::unique_ptr<Statement>(stmt);
    }
    else
    {
        Statement *current = head.get();
        while (current->next != nullptr)
        {
            current = current->next.get();
        }
        current->next = std::unique_ptr<Statement>(stmt);
    }
    statementMap[stmt->getStmtNum()] = stmt;
}

void Program::removeStatement(int stmtNum)
{
    if (statementMap.find(stmtNum) != statementMap.end())
    {
        Statement *stmt = statementMap[stmtNum];
        if (stmt == head.get())
        {
            head = std::move(stmt->next);
        }
        else
        {
            Statement *current = head.get();
            while (current->next.get() != stmt)
            {
                current = current->next.get();
            }
            current->next = std::move(stmt->next);
        }
        statementMap.erase(stmtNum);
    }
}

std::string Program::toString()
{
    std::string result;
    Statement *current = head.get();
    while (current != nullptr)
    {
        result += current->toString() + "\n";
        current = current->next.get();
    }
    return result;
}

