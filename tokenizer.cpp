#include "tokenizer.h"

Tokenizer::Tokenizer() {}



bool isdigit(char c)
{
    return c >= '0' && c <= '9';
}
bool isPositiveNum(std::string &str)
{
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
}

bool isNum(std::string &str)
{
    if (str[0] == '-')
    {
        std::string number = str.substr(1);
        return isPositiveNum(number);
    }
    return isPositiveNum(str);

}

std::vector<std::string> Tokenizer::tokenize(std::string &str)
{
    std::vector<std::string> tokens;
    std::string token;
    for (char c : str)
    {
        if (isspace(c))
        {
            if (!token.empty())
            {
            tokens.push_back(token);
            token.clear();
            }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '=')
        {
            if (!token.empty())
            {
            tokens.push_back(token);
            token.clear();
            }
            tokens.push_back(std::string(1, c));
        }
        else
        {
            token += c;
        }
        
        
    }
    if (!token.empty())
    {
        tokens.push_back(token);
    }
// Handle negative numbers and minus operator
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i] == "-" && (i == 0 || tokens[i-1] == "(" || tokens[i-1] == "=")) {
        // It's a negative number
        tokens[i+1] = "-" + tokens[i+1];
        tokens.erase(tokens.begin() + i);
        }
    }
}

std::vector<ExpToken> Tokenizer::tokenizeExp(std::vector<std::string> &expTokens)
{
    std::vector<ExpToken> tokens;
    for (std::string &token : expTokens)
    {
        if (token == "+")
        {
            tokens.push_back({ADD, token, 1});
        }
        else if (token == "-")
        {
            tokens.push_back({SUB, token, 1});
        }
        else if (token == "*")
        {
            tokens.push_back({MUL, token, 2});
        }
        else if (token == "/")
        {
            tokens.push_back({DIV, token, 2});
        }
        else if (token == "MOD")
        {
            tokens.push_back({MOD, token, 2});
        }
        else if (token == "**")
        {
            tokens.push_back({POW, token, 3});
        }
        else if (token == "(")
        {
            tokens.push_back({LPAREN, token, 0});
        }
        else if (token == ")")
        {
            tokens.push_back({RPAREN, token, 0});
        }
        else if (isdigit(token[0]))
        {
            tokens.push_back({NUM, token, 0});
        }
        else
        {
            tokens.push_back({VAR, token, 0});
        }
    }
    tokens.push_back({END, "", 0});
    return tokens;
}
