#include "context.h"


/** EvaluationContext */
void SymbolTable::setValue(const std::string& var, int value) {
    symbolTable[var] = value;
}

int SymbolTable::getValue(const std::string &var) const {
    return symbolTable.at(var);
}

bool SymbolTable::isDefined(const std::string& var) const {
    return symbolTable.find(var) != symbolTable.end();
}
