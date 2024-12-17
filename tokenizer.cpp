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

std::vector<Token> Tokenizer::tokenize(std::string &str)
{
     // 定义正则表达式模式
    std::string token_pattern = R"(
        (?P<NUMBER>-?\d+)                # 整数或负整数
      | (?P<OPERATOR>\+|-|\*{1,2}|\/|mod) # 操作符
      | (?P<VARIABLE>[a-zA-Z_]\w*)       # 变量名
      | (?P<LPAREN>\()                   # 左括号
      | (?P<RPAREN>\))                   # 右括号
      | (?P<EQUALS>=)                    # 等号
      |(?P<LESS><)                       # 小于号
      |(?P<GREATER>>)                    # 大于号
    )";

    // 去掉注释和空白，以便 C++ 正则引擎可以正确解析
    std::string cleaned_pattern = R"((\-?\d+)|(\+|-|\*{1,2}|\/|mod)|([a-zA-Z_]\w*)|(\()|(\))|(=)|(<)|(>))";

    // 定义输入表达式
    std::string expression = str;

    // 定义正则表达式
    std::regex token_regex(cleaned_pattern);

    // 开始匹配
    std::sregex_iterator begin(expression.begin(), expression.end(), token_regex);
    std::sregex_iterator end;

    // 定义分类名称
    std::vector<TokenType> categories = {
        TokenType::NUMBER,
        TokenType::OPERATOR,
        TokenType::VARIABLE,
        TokenType::LPAREN,
        TokenType::RPAREN,
        TokenType::EQUALS,
        TokenType::LESS,
        TokenType::GREATER
        };

    std::vector<Token> tokens;

    // 输出匹配结果
    // std::cout << "Matched tokens:\n";
    for (std::sregex_iterator i = begin; i != end; ++i) {
        std::smatch match = *i;

        // 查找匹配的分类
        for (size_t j = 1; j < match.size(); ++j) {
            if (match[j].matched) {
                // 保存匹配结果
                tokens.push_back({categories[j - 1], match[j].str()});
                break;
            }
        }
    }
}

std::vector<ExpToken> Tokenizer::tokenizeExp(std::vector<Token> &expTokens)
{
    std::vector<ExpToken> tokens;
    for (Token &token : expTokens)
    {
        switch (token.type)
        {
        case TokenType::NUMBER:
            tokens.push_back({NUM, token.value, 0});
            break;
        case TokenType::OPERATOR:
            if (token.value == "+")
            {
                tokens.push_back({ADD, "+", 1});
            }
            else if (token.value == "-")
            {
                tokens.push_back({SUB, "-", 1});
            }
            else if (token.value == "*")
            {
                tokens.push_back({MUL, "*", 2});
            }
            else if (token.value == "/")
            {
                tokens.push_back({DIV, "/", 2});
            }
            else if (token.value == "mod")
            {
                tokens.push_back({MOD, "mod", 2});
            }else if (token.value == "**")
            {
                tokens.push_back({POW, "**", 3});
            }
            break;
        case TokenType::VARIABLE:
            tokens.push_back({VAR, token.value, 0});
            break;
        case TokenType::LPAREN:
            tokens.push_back({LEFT_PAREN, "(", 0});
            break;
        case TokenType::RPAREN:
            tokens.push_back({RIGHT_PAREN, ")", 0});
            break;
        default: //do nothing
            break;
        }
    }
    tokens.push_back({END, "", 0});
    return tokens;
}
