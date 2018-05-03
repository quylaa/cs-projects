// Written by Aleks Christensen

#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>

class Token
{
public:
    std::string content;
    std::string type;
    int line;

    Token(std::string c, std::string t, int l) : content(c), type(t), line(l) {};

    std::string toString()
    {
        std::string o;
        o.append("(");
        o.append(content);
        o.append(",");
        o.append(type);
        o.append(",");
        o.append(std::to_string(line));
        o.append(")");
        return o;
    }
};

#endif
