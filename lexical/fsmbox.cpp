// Written by Aleks Christensen

#include "fsmbox.h"

FSMBox::FSMBox(){}

FSMBox::~FSMBox(){}

string FSMBox::tokens(string input)
{
    ostringstream out;
    int line = 1;
    for (string::iterator tk = input.begin(); tk != input.end(); ++tk) {
        cout << line;
        if ((*tk) == ',') out << makeOutput((*tk), "COMMA", line);
        else if ((*tk) == '.') out << makeOutput((*tk), "PERIOD", line);
        else if ((*tk) == '?') out << makeOutput((*tk), "Q_MARK", line);
        else if ((*tk) == '(') out << makeOutput((*tk), "LEFT_PAREN", line);
        else if ((*tk) == ')') out << makeOutput((*tk), "RIGHT_PAREN", line);
        else if ((*tk) == '*') out << makeOutput((*tk), "MULTIPLY", line);
        else if ((*tk) == '+') out << makeOutput((*tk), "ADD", line);
        // else if ((*tk) == ' ') out << makeOutput((*tk), "WHITESPACE", line);
        else if (isspace((*tk))) continue;
        else if ((*tk) == ':') {
            string co;
            co.push_back((*tk));
            ++tk;
            if ((*tk+1) == '-') {
                co.push_back(*tk+1);
                out << makeOutput(co, "COLON_DASH", line);
            }
            else out << makeOutput(co, "COLON", line);
        }
        else if ((*tk) == '\'') {
            string st = "'";
            ++tk;
            for (;tk != input.end(); ++tk) {
                st.push_back((*tk));
                if ((*tk) == '\n') line++;
                if ((*tk) == '\'') break;
            }
            if (tk == input.end()) {
                out << makeOutput(st, "UNDEFINED", line);
            }
            else out << makeOutput(st, "STRING", line);
        }
        else if ((*tk) == '#') {
            string st = "#";
            int l = line;
            ++tk;
            if ((*tk+1) == '|') {
                st.push_back('|');
                for (;tk != input.end(); ++tk) {
                    st.push_back((*tk));
                    if ((*tk) == '\n') line++;
                    if ((*tk) == '|' && (*tk+1) == '#') {
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
                    st.push_back((*tk));
                    if ((*tk) == '\n') {
                        line++;
                        break;
                    }
                }
                out << makeOutput(st, "COMMENT", l);
            }
        }
        else if (isalpha((*tk))) {
            string st;
            st.push_back((*tk));
            ++tk;
            bool undef = false;
            for (;(*tk) != '\n'; ++tk) {
                if (isalpha((*tk)) || isdigit((*tk))) st.push_back((*tk));
                else if (st == "Schemes") {
                    out << makeOutput(st, "SCHEMES", line);
                    break;
                }
                else if (st == "Facts") {
                    out << makeOutput(st, "FACTS", line);
                    break;
                }
                else if (st == "Rules") {
                    out << makeOutput(st, "RULES", line);
                    break;
                }
                else if (st == "Queries") {
                    out << makeOutput(st, "QUERIES", line);
                    break;
                }
                else if (isspace((*tk))) break;
                else {
                    st.push_back((*tk));
                    undef = true;
                }
            }
            if (undef == true) out << makeOutput(st, "UNDEFINED", line);
            else {
                if (st != "Schemes" && st != "Facts" && st != "Rules" && st != "Queries")
                    out << makeOutput(st, "ID", line);
            }
        }
        else if ((*tk) == '\n') {
            cout << "NEWLINE";
            ++line;
        }
        else {
            string st;
            st.push_back((*tk));
            for (;(*tk) != '\n'; ++tk) {
                if (isspace((*tk))) break;
                st.push_back((*tk));
            }
            out << makeOutput(st, "UNDEFINED", line);
        }
    }
    return out.str();
}

string FSMBox::makeOutput(string out, string token, int line)
{
    stringstream o;
    o << "(" << token << ",\"" << out << "\"," << line << ")" << endl;
    cout << "I FOUND A " << out << endl;
    return o.str();
}

string FSMBox::makeOutput(char out, string token, int line)
{
    stringstream o;
    o << "(" << token << ",\"" << out << "\"," << line << ")" << endl;
    cout << "I FOUND A " << out << endl;
    return o.str();
}
