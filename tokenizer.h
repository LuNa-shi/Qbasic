#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <vector>
class tokenizer
{
public:
    tokenizer();
    ~tokenizer();
    std::vector<std::string> tokenize(std::string &str);

private:
    std::vector<std::string> tokens;
};

#endif // TOKENIZER_H
