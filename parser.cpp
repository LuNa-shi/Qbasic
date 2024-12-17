#include "parser.h"

Parser::Parser() {
    tk = new Tokenizer();
}

Parser::~Parser() {
    delete tk;
}

Statement *Parser::getStatement(std::string &stmt)
{
    std::vector<std::string> tokens = tk->tokenize(stmt);
    if (tokens.size() == 0)
    {
        return nullptr;
    }
    int stmtNum = std::stoi(tokens[0]);

    if (tokens[1] == "LET")
    {
        return parseLet(tokens);
    }
    else if (tokens[1] == "PRINT")
    {
        return parsePrint(tokens);
    }
    // else if (tokens[1] == "INPUT")
    // {
    //     return parseInput(tokens);
    // }
    // else if (tokens[1] == "IF")
    // {
    //     return parseIf(tokens);
    // }
    // else if (tokens[1] == "GOTO")
    // {
    //     return parseGoto(tokens);
    // }
    // else if (tokens[1] == "END")
    // {
    //     return parseEnd(tokens);
    // }
    else //some other statement
    {
        return nullptr;
    }
}

Expression *Parser::parseExp(std::vector<std::string> &expTokens)
{
    std::vector<ExpToken> tokens = tk->tokenizeExp(expTokens);
    if (tokens.size() == 0)
    {
        return nullptr;
    }
    std::stack<std::unique_ptr<Expression>> expStack;
    std::stack<ExpToken> opStack;

    for (ExpToken &token : tokens)
    {
        if (token.type == NUM)
        {
            expStack.push(std::make_unique<ConstantExp>(std::stoi(token.value)));
        }
        else if (token.type == VAR)
        {
            expStack.push(std::make_unique<IdentifierExp>(token.value));
        }
        else if (token.type == LPAREN)
        {
            opStack.push(token);
        }
        else if (token.type == RPAREN)
        {
            while (opStack.top().type != LPAREN)
            {
                ExpToken op = opStack.top();
                opStack.pop();
                Expression *rhs = expStack.top().release();
                expStack.pop();
                Expression *lhs = expStack.top().release();
                expStack.pop();
                expStack.push(std::make_unique<CompoundExp>(op.value, lhs, rhs));
            }
            opStack.pop(); //when the loop ends, the top of the stack is LPAREN, so pop it
        }
        else if (token.type == END)
        {
            while (!opStack.empty())
            {
                ExpToken op = opStack.top();
                opStack.pop();
                Expression *rhs = expStack.top().release();
                expStack.pop();
                Expression *lhs = expStack.top().release();
                expStack.pop();
                expStack.push(std::make_unique<CompoundExp>(op.value, lhs, rhs));
            }
        }
        else //operator
        {

            while (!opStack.empty() && opStack.top().precedence >= token.precedence)
            {
                if(opStack.top().type == POW && token.type == POW) {
                    break;
                }
                ExpToken op = opStack.top();
                opStack.pop();
                Expression *rhs = expStack.top().release();
                expStack.pop();
                Expression *lhs = expStack.top().release();
                expStack.pop();
                expStack.push(std::make_unique<CompoundExp>(op.value, lhs, rhs));
            }
            opStack.push(token);
        }
    }
    return expStack.top().release();


}

Statement *Parser::parseLet(std::vector<std::string> &tokens)
{
    if (tokens.size() < 4)
    {
        return nullptr;
    }
    std::string var = tokens[2];
    std::vector<std::string> expTokens(tokens.begin() + 3, tokens.end());
    Expression *exp = parseExp(expTokens);
    if (exp == nullptr)
    {
        return nullptr;
    }
    return new LetStatement(std::stoi(tokens[0]), var, exp);
}

// //unchecked
Statement *Parser::parsePrint(std::vector<std::string> &tokens)
{
    if (tokens.size() < 3)
    {
        return nullptr;
    }
    std::vector<std::string> expTokens(tokens.begin() + 2, tokens.end());
    Expression *exp = parseExp(expTokens);
    if (exp == nullptr)
    {
        return nullptr;
    }
    return new PrintStatement(std::stoi(tokens[0]), exp);
}

// Statement *Parser::parseInput(std::vector<std::string> &tokens)
// {
//     if (tokens.size() < 3)
//     {
//         return nullptr;
//     }
//     std::string var = tokens[2];
//     return new InputStatement(std::stoi(tokens[0]), var);
// }

// Statement *Parser::parseIf(std::vector<std::string> &tokens)
// {
//     if (tokens.size() < 6)
//     {
//         return nullptr;
//     }
//     Expression *lhs = parseExp(tokens, 2);
//     if (lhs == nullptr)
//     {
//         return nullptr;
//     }
//     std::string op = tokens[3];
//     Expression *rhs = parseExp(tokens, 4);
//     if (rhs == nullptr)
//     {
//         return nullptr;
//     }
//     int dest = std::stoi(tokens[5]);
//     return new IfStatement(std::stoi(tokens[0]), lhs, op, rhs, dest);
// }

// Statement *Parser::parseGoto(std::vector<std::string> &tokens)
// {
//     if (tokens.size() < 3)
//     {
//         return nullptr;
//     }
//     int dest = std::stoi(tokens[2]);
//     return new GotoStatement(std::stoi(tokens[0]), dest);
// }

// Statement *Parser::parseEnd(std::vector<std::string> &tokens)
// {
//     return new EndStatement(std::stoi(tokens[0]));
// }
// //unchecked


