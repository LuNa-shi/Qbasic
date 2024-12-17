#pragma once
#ifndef RUNTIMESTATE_H
#define RUNTIMESTATE_H
#include "displayinfo.h"
#include "context.h"
class RuntimeState
{
public:
    RuntimeState();
    SymbolTable* symTable;
    DisplayInfo* displayInfo;
    int PC;

};

#endif // RUNTIMESTATE_H
