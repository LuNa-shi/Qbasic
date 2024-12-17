#include "program.h"
Program::Program()
{
    runtimeState = new RuntimeState();
}

Program::~Program()
{
    delete runtimeState;
    for (Statement *stmt : statementList) {
        delete stmt;
    }
}

void Program::appendStatement(Statement *stmt)
{
    auto it = statementList.begin();
    while (it != statementList.end() && (*it)->getStatementNum() < stmt->getStatementNum()) {
        ++it;
    }
    statementList.insert(it, stmt);
    statementMap[stmt->getStatementNum()] = stmt;
}


void Program::removeStatement(int stmtNum)
{
    auto it = statementMap.find(stmtNum);
    if (it != statementMap.end()) {
        statementList.remove(it->second);
        statementMap.erase(it);
    }
}

std::vector<std::string> Program::toString() const
{
    std::vector<std::string> result;
    for (Statement *stmt : statementList) {
        result.push_back(stmt->toString());
    }
    return result;
}

Statement *Program::getStatement(int stmtNum)
{
    auto it = statementMap.find(stmtNum);
    if (it != statementMap.end()) {
        return it->second;
    }
    return nullptr;
}

Statement *Program::getNextStatement(int stmtNum)
{
    auto it = statementList.begin();
    while (it != statementList.end() && (*it)->getStatementNum() <= stmtNum) {
        ++it;
    }
    if (it != statementList.end()) {
        return *it;
    }
    return nullptr;
}

int Program::getNextStatementNum(int stmtNum) {
    Statement *stmt = getNextStatement(stmtNum);
    if (stmt != nullptr) {
        return stmt->getStatementNum();
    }
    return -1;
}

Statement *Program::getFirstStatement() {
    if (statementList.empty()) {
        return nullptr;
    }
    return statementList.front();
}

void Program::run() {
    int curline = getFirstStatement()->getStatementNum();

    while (curline > 0) {
        auto stmt = getStatement(curline);
        runtimeState->PC = getNextStatementNum(curline); //endline's next line is -1
        stmt->execute(*runtimeState);//could change PC and context
        curline = runtimeState->PC;
    }
}

