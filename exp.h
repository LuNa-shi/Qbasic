#ifndef EXP_H
#define EXP_H


#include <string>
#include <bits/stdc++.h>
#include "tokenizer.h"
#include "context.h"

/* Forward reference */

class SymbolTable;

/*
 * Type: ExpressionType
 * --------------------
 * This enumerated type is used to differentiate the three different
 * expression types: CONSTANT, IDENTIFIER, and COMPOUND.
 */

enum ExpressionType { CONSTANT, IDENTIFIER, COMPOUND };

/*
 * Class: Expression
 * -----------------
 * This class is used to represent a node in an expression tree.
 * Expression itself is an abstract class.  Every Expression object
 * is therefore created using one of the three concrete subclasses:
 * ConstantExp, IdentifierExp, or CompoundExp.
 */

class Expression {

public:

    Expression();
    virtual ~Expression() = default;
    virtual int eval(SymbolTable & context) = 0;
    virtual std::string toString() = 0;
    virtual ExpressionType type() = 0;



};



class ConstantExp: public Expression {

public:

    explicit ConstantExp(int val);

    int eval(SymbolTable & context) override;
    std::string toString() override;
    ExpressionType type() override;

    int getConstantValue() const;

private:

    int value;

};

/*
 * Class: IdentifierExp
 * --------------------
 * This subclass represents a expression corresponding to a variable.
 */

class IdentifierExp: public Expression {

public:
    explicit IdentifierExp(std::string name);

    int eval(SymbolTable & context) override;
    std::string toString() override;
    ExpressionType type() override;

    std::string getIdentifierName();

private:
    std::string name;
};

/*
 * Class: CompoundExp
 * ------------------
 * This subclass represents a compound expression.
 */

class CompoundExp: public Expression {

public:

    CompoundExp(std::string op, Expression *lhs, Expression *rhs);

    ~CompoundExp() override;

    int eval(SymbolTable & context) override;
    std::string toString() override;
    ExpressionType type() override;

    std::string getOperator();
    Expression *getLHS();
    Expression *getRHS();

private:

    std::string op;
    std::unique_ptr<Expression> lhs, rhs;

};





#endif // EXP_H
