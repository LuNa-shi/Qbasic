#include "tokenizer.h"

tokenizer::tokenizer() {}

tokenizer::~tokenizer() {}

std::vector<std::string> tokenizer::tokenize(std::string &str)
{
    std::vector<std::string> tokens;
    std::string token;
    for (char c : str)
    {
        if (c == ' ')
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
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
    return tokens;
}