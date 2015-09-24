// Written by Aleks Christensen

#include "fsmbox.h"

FSMBox::FSMBox(){}

FSMBox::~FSMBox(){}

string FSMBox::tokens(string input)
{
    string::iterator tk;
    for (tk = input.begin(); tk != input.end(); ++tk) {
        if (*(tk) == '\n') { line++; continue; }// increment line counter when newline is found
        else if (isspace(*(tk))) continue;
        else if (*(tk) == ',') out << makeOutput(*(tk), "COMMA", line);
        else if (*(tk) == '.') out << makeOutput(*(tk), "PERIOD", line);
        else if (*(tk) == '?') out << makeOutput(*(tk), "Q_MARK", line);
        else if (*(tk) == '(') out << makeOutput(*(tk), "LEFT_PAREN", line);
        else if (*(tk) == ')') out << makeOutput(*(tk), "RIGHT_PAREN", line);
        else if (*(tk) == '*') out << makeOutput(*(tk), "MULTIPLY", line);
        else if (*(tk) == '+') out << makeOutput(*(tk), "ADD", line);
        else if (*(tk) == ':') isColon(input, tk);
        else if (*(tk) == '\'') isString(input, tk);
        else if (*(tk) == '#') isComment(input, tk);
        else if (isalpha(*(tk))) isID(input, tk);
        else out << makeOutput(*(tk), "UNDEFINED", line);
    }
    if (tk == input.end()) out << makeOutput("", "EOF", line); // format EOF
    out << "Total Tokens = " << num << endl; // num is initialized in header, tracks number of tokens
    return out.str();
}

void FSMBox::isColon(string input, string::iterator &tk)
{
    string co; // create string to hold colon
    co.push_back(*(tk)); // append colon to string
    if (*(tk+1) == '-') { // if next char is dash
        co.push_back(*(tk+1)); // append dash to string
        out << makeOutput(co, "COLON_DASH", line); // format colon_dash
        tk++; // increment pointer away from dash
    }
    else out << makeOutput(co, "COLON", line); // otherwise format colon
}

void FSMBox::isString(string input, string::iterator &tk)
{
    bool undef = false;
    string st = "'"; // initialize string string (lol)
    ++tk; // increment pointer away from first quotation mark
    int l = line; // remember starting line number
    for (; tk != input.end(); ++tk) {
        if (*(tk) == '\000') {
            undef = true;
            break;
        }
        st.push_back(*(tk)); // add next char to string
        if (*(tk) == '\n') line++; // if newline, increment counter
        else if (*(tk) == '\'') { // if quotation mark found
            if (*(tk+1) == '\'') { // and next char is quotation mark
                st.push_back('\''); // add next quotation mark to string
                ++tk; // and increment away from it
            }
            else break; // otherwise it's the end of the string
        }
    }
    if (tk == input.end() || undef == true) { // if EOF was found before end of string
        out << makeOutput(st, "UNDEFINED", l); // format as undef
        --tk; // decrement so that for loop places pointer on EOF and not after
    }
    else out << makeOutput(st, "STRING", l); // format as string
}

void FSMBox::isComment(string input, string::iterator &tk)
{
    string st = "#"; // initialize comment string
    int l = line; // remember initial line number
    ++tk; // increment away from starting char
    if (*(tk) == '|') { // multiline comment
        st.push_back(*(tk)); // place it in string
        ++tk;
        for (; tk != input.end(); ++tk) { // iterate until end token is found
            if (*(tk) == '\n') line++; // if newline found, increment line
            st.push_back(*(tk));
            if (*(tk) == '|' && *(tk+1) == '#') { // if char is pipe and next char is hash
                st.push_back('#'); // place hash in string
                ++tk; // increment away from hash
                break;
            }
        }
        if (tk == input.end()) { // if EOF found before end of comment
            out << makeOutput(st, "UNDEFINED", l); // format as undef
            --tk; // decrement so that for loop places pointer on EOF and not after
        }
        else out << makeOutput(st, "COMMENT", l); // format as comment
    }
    else { // single line comment
        for (;tk != input.end(); ++tk) { // iterate until newline
            if (*(tk) == '\n') { // if char is newline
                line++; // increment counter
                break;
            }
            st.push_back(*(tk)); // else put char in comment string
        }
        out << makeOutput(st, "COMMENT", l); // format as comment
    }
}

void FSMBox::isID(string input, string::iterator &tk)
{
    string st;
    st.push_back(*(tk));
    ++tk;
    bool undef = false; // tracks if token is undefined
    int l = line; // remember initial line
    for (; tk != input.end(); ++tk) {
        if (isalpha(*(tk)) || isdigit(*(tk))) st.push_back(*(tk));
        else if (isspace(*(tk)) && *(tk) != '\n') break; // break on space
        else if (*(tk) == '\n') { // break on newline and increment line counter
            line++;
            break;
        }
        else { --tk; break;} // illegal character, decrement counter to allow global for loop to work
    }
    if (undef == true) out << makeOutput(st, "UNDEFINED", line); // format as undef
    else {
        if (st == "Schemes") out << makeOutput(st, "SCHEMES", l);
        else if (st == "Facts") out << makeOutput(st, "FACTS", l);
        else if (st == "Rules") out << makeOutput(st, "RULES", l);
        else if (st == "Queries") out << makeOutput(st, "QUERIES", l);
        else out << makeOutput(st, "ID", l);
    }
}

string FSMBox::makeOutput(string out, string token, int line) // format token output string
{
    stringstream o;
    o << "(" << token << ",\"" << out << "\"," << line << ")" << endl;
    num++;
    return o.str();
}

string FSMBox::makeOutput(char out, string token, int line) //overload function to allow char input
{
    stringstream o;
    o << "(" << token << ",\"" << out << "\"," << line << ")" << endl;
    num++;
    return o.str();
}
