#include "exp.h"

#include <utility>
Expression::Expression(){}

/** ---------- ConstantExp---------- */
ConstantExp::ConstantExp(int val) {
    value = val;
}

int ConstantExp::eval(SymbolTable & context) {
    return value;
}

std::string ConstantExp::toString() {
    return std::to_string(value);
}

ExpressionType ConstantExp::type() {
    return CONSTANT;
}

int ConstantExp::getConstantValue() const {
    return value;
}

/** ----------IdentifierExp----------- */

IdentifierExp::IdentifierExp(std::string name) :
    name(std::move(name)) {}

int IdentifierExp::eval(SymbolTable & context) {
    if (!context.isDefined(name)) {
        std::cerr << "Variable " << name << " is not defined." << std::endl;
    }
    return context.getValue(name);
}

std::string IdentifierExp::toString() {
    return name;
}

ExpressionType IdentifierExp::type() {
    return IDENTIFIER;
}

std::string IdentifierExp::getIdentifierName() {
    return name;
}

/** ------ CompoundExp --------*/
CompoundExp::CompoundExp(std::string op, Expression *lhs, Expression *rhs):
    op(std::move(op)) {
    std::unique_ptr<Expression> lhs_ptr(lhs);
    std::unique_ptr<Expression> rhs_ptr(rhs);
    this->lhs = std::move(lhs_ptr);
    this->rhs = std::move(rhs_ptr);
}

CompoundExp::~CompoundExp() = default;

int CompoundExp::eval(SymbolTable & context) {
    if (op == "+") {
        return lhs->eval(context) + rhs->eval(context);
    } else if (op == "-") {
        return lhs->eval(context) - rhs->eval(context);
    } else if (op == "*") {
        return lhs->eval(context) * rhs->eval(context);
    } else if (op == "/") {
        return lhs->eval(context) / rhs->eval(context);
    } else if (op == "MOD") {
        /*The MOD operator has the same precedence as * and /. 
        In the expression LET r = a MOD b, 
        the absolute value of r should be less than the absolute value of b,
         and the sign of r is the same as that of b. 
         For example, 5 MOD 3 is 2 and 5 MOD (-3) is -1.
        */
        return lhs->eval(context) % rhs->eval(context);     
    } else if (op == "**") {
        return static_cast<int>(pow(lhs->eval(context), rhs->eval(context)));
    }else {
        //TODO: handle error,maybe throw exception
        std::cerr << "Unknown operator: " << op << std::endl;
    }
    return 0;
}

//TODO: Implement the toString method for CompoundExp
std::string CompoundExp::toString() {
    return "(" + lhs->toString() + " " + op + " " + rhs->toString() + ")";
}

ExpressionType CompoundExp::type() {
    return COMPOUND;
}

std::string CompoundExp::getOperator() {
    return op;
}

Expression *CompoundExp::getLHS() {
    return lhs.get();
}

Expression *CompoundExp::getRHS() {
    return rhs.get();
}





