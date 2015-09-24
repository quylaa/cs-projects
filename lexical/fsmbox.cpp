// Written by Aleks Christensen

#include "fsmbox.h"

FSMBox::FSMBox(){}

FSMBox::~FSMBox(){}

stringstream FSMBox::tokens(stringstream input, int line)
{
    stringstream out;
    int line = 1;
    for (stringstream::iterator tk = input.begin(); tk != input.end(); ++tk) {
        if ((*tk) == ',') out << makeOutput((*tk), "COMMA", line);
        else if ((*tk) == '.') out << makeOutput((*tk), "PERIOD", line) << endl;
        else if ((*tk) == '?') out << makeOutput((*tk), "Q_MARK", line) << endl;
        else if ((*tk) == '(') out << makeOutput((*tk), "LEFT_PAREN", line) << endl;
        else if ((*tk) == ')') out << makeOutput((*tk), "RIGHT_PAREN", line) << endl;
        else if ((*tk) == '*') out << makeOutput((*tk), "MULTIPLY", line) << endl;
        else if ((*tk) == '+') out << makeOutput((*tk), "ADD", line) << endl;
        // else if ((*tk) == ' ') out << makeOutput((*tk), "WHITESPACE", line) << endl;
        else if (isspace((*tk))) continue;
        else if ((*tk) == ':') {
            if ((*tk+1) == '-') out << makeOutput(co, "COLON_DASH", line) << endl;
            else out << makeOutput(co, "COLON", line) << endl;
        }
        else if ((*tk) == '\'') {
            string st = "'";
            for (tk; tk != input.end(); ++tk) {
                st.push_back((*tk));
                if ((*tk) == '\n') line++;
                if ((*tk) == '\'') break;
            }
            if (tk == input.end()) {
                out << makeOutput(st, "UNDEFINED", line) << endl;
            }
            else out << makeOutput(st, "STRING", line) << endl;
        }
        else if ((*tk) == '#') {
            string st = "#";
            int l = line;
            if ((*tk+1) == '|') {
                st.push_back("|");
                for (tk; tk != input.end(); ++tk) {
                    st.push_back((*tk));
                    if ((*tk) == '\n') line++;
                    if ((*tk) == '|' && (*tk+1) == '#') {
                        st.push_back("#");
                        break;
                    }
                }
                if (tk == input.end()) {
                    out << makeOutput(st, "UNDEFINED", line) << endl;
                }
                else out << makeOutput(st, "COMMENT", l) << endl;
            }
            else {
                for (tk; tk != input.end(); ++tk) {
                    st.push_back((*tk));
                    if ((*tk) == '\n') {
                        line++;
                        break;
                    }
                }
                out << makeOutput(st, "COMMENT", l) << endl;
            }
        }
        else if (isalpha((*tk))) {
            string st = (*tk);
            for (tk; (*tk) != "\n"; ++tk) {
                bool undef = false;
                if (isalpha((*tk)) || isdigit((*tk))) st.push_back((*tk));
                if (st == "Schemes") {
                    out << makeOutput(st, "SCHEMES", line) << endl;
                    break;
                }
                else if (st == "Facts") {
                    out << makeOutput(st, "FACTS", line) << endl;
                    break;
                }
                else if (st == "Rules") {
                    out << makeOutput(st, "RULES", line) << endl;
                    break;
                }
                else if (st == "Queries") {
                    out << makeOutput(st, "QUERIES", line) << endl;
                    break;
                }
                else if (isspace((*tk))) break;
                else {
                    st.push_back((*tk));
                    undef = true;
                }
            }
            if (undef == true) out << makeOutput(st, "UNDEFINED", line) << endl;
            else {
                if (st != "Schemes" && st != "Facts" && st != "Rules" && st != "Queries")
                    out << makeOutput(st, "ID", line) << endl;
            }
        }
        else if ((*tk) == '\n') line++;
        else {
            string st = (*tk);
            for (tk; (*tk) != '\n'; ++tk) {
                if (isspace((*tk))) break;
                st.push_back((*tk));
            }
            out << makeOutput(st, "UNDEFINED", line);
        }
        return out;
    }
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
