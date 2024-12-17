#include "context.h"


/** EvaluationContext */
void SymbolTable::setValue(std::string var, int value) {
    symbolTable[var] = value;
}

int SymbolTable::getValue(std::string var) {
    return symbolTable[var];
}

bool SymbolTable::isDefined(std::string var) {
    return symbolTable.find(var) != symbolTable.end();
}
