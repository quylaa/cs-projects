// Written by Aleks Christensen

#include "fsmbox.h"

FSMBox::FSMBox(){}

FSMBox::~FSMBox(){}

string FSMBox::tokens(string input, int line)
{
    stringstream out;
    for (string::iterator tk = input.begin(); tk != input.end(); ++tk) {
        if ((*tk) == ',') out << makeOutput((*tk), "COMMA", line);
        else if ((*tk) == '.') out << makeOutput((*tk), "PERIOD", line);
        else if ((*tk) == '?') out << makeOutput((*tk), "Q_MARK", line);
        else if ((*tk) == '(') out << makeOutput((*tk), "LEFT_PAREN", line);
        else if ((*tk) == ')') out << makeOutput((*tk), "RIGHT_PAREN", line);
        else if ((*tk) == '*') out << makeOutput((*tk), "MULTIPLY", line);
        else if ((*tk) == '+') out << makeOutput((*tk), "ADD", line);
        else if ((*tk) == ' ') out << makeOutput((*tk), "WHITESPACE", line);
        else if ((*tk) == ':') {
            string c = (*tk);
            c.push_back((*tk.next));
            string co = colon(c);
            if (co == ":") out << makeOutput(co, "COLON", line);
            else if (co == ":-") out << makeOutput(co, "COLON_DASH", line);
        }
        else if ((*tk) == '\'') {
            string st = "'";
            for (tk; tk != input.end(); ++tk) {
                st.push_back((*tk));
                if ((*tk) == '\'') break;
            }
        }
    }
    return " ";
}

string FSMBox::colon(string c)
{

}

string FSMBox::makeOutput(string out, string token, int line)
{
    stringstream o;
    o << "(" << token << ",\"" << out << "\"," << line << ")" << endl;
    return o.str();
}

string FSMBox::makeOutput(char out, string token, int line)
{
    stringstream o;
    o << "(" << token << ",\"" << out << "\"," << line << ")" << endl;
    return o.str();
}
