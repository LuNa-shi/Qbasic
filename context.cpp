#include "context.h"


/** EvaluationContext */
void EvaluationContext::setValue(std::string var, int value) {
    symbolTable[var] = value;
}

int EvaluationContext::getValue(std::string var) {
    return symbolTable[var];
}

bool EvaluationContext::isDefined(std::string var) {
    return symbolTable.find(var) != symbolTable.end();
}
