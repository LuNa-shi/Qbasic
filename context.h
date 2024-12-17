#ifndef CONTEXT_H
#define CONTEXT_H
#include <bits/stdc++.h>

class SymbolTable {

public:

    void setValue(std::string var, int value);
    int getValue(std::string var);
    bool isDefined(std::string var);

private:

    std::unordered_map<std::string,int> symbolTable;

};


#endif // CONTEXT_H
