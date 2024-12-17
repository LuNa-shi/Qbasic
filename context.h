#ifndef CONTEXT_H
#define CONTEXT_H
#include <bits/stdc++.h>

class SymbolTable {

public:

    void setValue(const std::string& var, int value);
    int getValue(const std::string &var) const;
    bool isDefined(const std::string& var) const;

private:

    std::unordered_map<std::string,int> symbolTable;

};


#endif // CONTEXT_H
