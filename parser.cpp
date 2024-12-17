#include "parser.h"

Parser::Parser() {
    tk = new Tokenizer();
}

Parser::~Parser() {
    delete tk;
}

Statement *Parser::getStatement(std::string &stmt)
{
    std::vector<Token> tokens = tk->tokenize(stmt);
    if (tokens.empty())
    {
        return nullptr;
    }
    Token lineNumber = tokens[0];
    if (lineNumber.type != TokenType::NUMBER)
    {
        return parseImmediate(tokens);
    }
    return parseStatement(tokens);

}

Statement *Parser::parseImmediate(std::vector<Token> &tokens)
{
    if (tokens.size() < 1)
    {
        return nullptr;
    }
    // if (tokens[0].value == "RUN")
    // {
    //     return new RunStatement();
    // }
    // else if (tokens[0].value == "LIST")
    // {
    //     return new ListStatement();
    // }
    // else if (tokens[0].value == "CLEAR")
    // {
    //     return new ClearStatement();
    // }
    // else if (tokens[0].value == "QUIT")
    // {
    //     return new QuitStatement();
    // }
    // else if (tokens[0].value == "HELP")
    // {
    //     return new HelpStatement();
    // }
    else
    {
        return nullptr;
    }
}

Statement* Parser::parseStatement(std::vector<Token> &tokens)
{
    std::string cmd = tokens[1].value;
    if (cmd == "LET") {
        return parseLet(tokens);
    }

}
Expression *Parser::parseExp(std::vector<Token> &expTokens)
{
    std::vector<ExpToken> tokens = tk->tokenizeExp(expTokens);
    if (tokens.empty())
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
        else if (token.type == LEFT_PAREN)
        {
            opStack.push(token);
        }
        else if (token.type == RIGHT_PAREN)
        {
            while (opStack.top().type != LEFT_PAREN)
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

Statement *Parser::parseLet(std::vector<Token> &tokens)
{
    if (tokens.size() < 4)
    {
        return nullptr;
    }
    std::string var = tokens[2].value;
    std::vector<Token> expTokens(tokens.begin() + 3, tokens.end());
    Expression *exp = parseExp(expTokens);
    if (exp == nullptr)
    {
        return nullptr;
    }

    return new LetStatement(std::stoi(tokens[0].value), var, exp);
}

// //unchecked
Statement *Parser::parsePrint(std::vector<Token> &tokens)
{
    if (tokens.size() < 3)
    {
        return nullptr;
    }
    std::vector<Token> expTokens(tokens.begin() + 2, tokens.end());
    Expression *exp = parseExp(expTokens);
    if (exp == nullptr)
    {
        return nullptr;
    }
    return new PrintStatement(std::stoi(tokens[0].value), exp);
}




