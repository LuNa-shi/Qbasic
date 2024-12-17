#include "runtimestate.h"

RuntimeState::RuntimeState() {
    PC = 0;
    symTable = new SymbolTable();
    displayInfo = new DisplayInfo();
}




