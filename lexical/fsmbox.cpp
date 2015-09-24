// Written by Aleks Christensen

#include "fsmbox.h"

FSMBox::FSMBox(){}

FSMBox::~FSMBox(){}

string FSMBox::tokens(string input)
{
    ostringstream out;
    string::iterator tk;
    int line = 1;
    for (tk = input.begin(); tk != input.end(); ++tk) {
        if (*(tk) == '\n') {
            line++;
        }
        else if (*(tk) == ',') out << makeOutput(*(tk), "COMMA", line);
        else if (*(tk) == '.') out << makeOutput(*(tk), "PERIOD", line);
        else if (*(tk) == '?') out << makeOutput(*(tk), "Q_MARK", line);
        else if (*(tk) == '(') out << makeOutput(*(tk), "LEFT_PAREN", line);
        else if (*(tk) == ')') out << makeOutput(*(tk), "RIGHT_PAREN", line);
        else if (*(tk) == '*') out << makeOutput(*(tk), "MULTIPLY", line);
        else if (*(tk) == '+') out << makeOutput(*(tk), "ADD", line);
        else if (isspace(*(tk))) continue;
        else if (*(tk) == ':') {
            string co;
            co.push_back(*(tk));
            if (*(tk+1) == '-') {
                co.push_back(*(tk+1));
                out << makeOutput(co, "COLON_DASH", line);
                tk++;
            }
            else out << makeOutput(co, "COLON", line);
        }
        else if (*(tk) == '\'') {
            string st = "'";
            ++tk;
            for (; tk != input.end(); ++tk) {
                if (*(tk) == '\n') {
                    line++;
                    continue;
                }
                st.push_back(*(tk));
                if (*(tk) == '\'') break;
            }
            if (tk == input.end()) {
                out << makeOutput(st, "UNDEFINED", line);
            }
            else out << makeOutput(st, "STRING", line);
        }
        else if (*(tk) == '#') {
            string st = "#";
            int l = line;
            ++tk;
            if (*(tk) == '|') {
                st.push_back(*(tk));
                for (; tk != input.end(); ++tk) {
                    if (*(tk) == '\n') {
                        line++;
                        continue;
                    }
                    st.push_back(*(tk));
                    if (*(tk) == '|' && (*tk+1) == '#') {
                        st.push_back('#');
                        break;
                    }
                }
                if (tk == input.end()) {
                    out << makeOutput(st, "UNDEFINED", line);
                }
                else out << makeOutput(st, "COMMENT", l);
            }
            else {
                for (;tk != input.end(); ++tk) {
                    if (*(tk) == '\n') {
                        line++;
                        break;
                    }
                    st.push_back(*(tk));
                }
                out << makeOutput(st, "COMMENT", l);
            }
        }
        else if (isalpha(*(tk))) {
            string st;
            st.push_back(*(tk));
            ++tk;
            bool undef = false;
            for (; tk != input.end(); ++tk) {
                if (isalpha(*(tk)) || isdigit(*(tk))) st.push_back(*(tk));
                else if (isspace(*(tk)) && *(tk) != '\n') break;
                else if (*(tk) == '\n') {
                    line++;
                    break;
                }
                else {
                    st.push_back(*(tk));
                    undef = true;
                }
            }
            if (undef == true) out << makeOutput(st, "UNDEFINED", line);
            else {
                if (st == "Schemes") out << makeOutput(st, "SCHEMES", line);
                else if (st == "Facts") out << makeOutput(st, "FACTS", line);
                else if (st == "Rules") out << makeOutput(st, "RULES", line);
                else if (st == "Queries") out << makeOutput(st, "QUERIES", line);
                else out << makeOutput(st, "ID", line);
            }
        }
        else {
            string st;
            st.push_back(*(tk));
            ++tk;
            for (;*(tk) != '\n'; ++tk) {
                if (isspace(*(tk))) break;
                st.push_back(*(tk));
            }
            out << makeOutput(st, "UNDEFINED", line);
        }
    }
    if (tk == input.end()) out << makeOutput("", "EOF", line);
    out << "Total Tokens = " << num << endl;
    return out.str();
}

string FSMBox::makeOutput(string out, string token, int line)
{
    stringstream o;
    o << "(" << token << ",\"" << out << "\"," << line << ")" << endl;
    num++;
    return o.str();
}

string FSMBox::makeOutput(char out, string token, int line)
{
    stringstream o;
    o << "(" << token << ",\"" << out << "\"," << line << ")" << endl;
    num++;
    return o.str();
}
