// Written by Aleks Christensen

#include "fsmbox.h"

FSMBox::FSMBox(){}

FSMBox::~FSMBox(){}

vector<FSMBox::Token> FSMBox::tokens(stack<char> input)
{
    char t;
    do {
        t = topnpop(input);
        if (t == '\n') { line++; continue; }
        else if (t == '\000') break;
        else if (isspace(t)) continue;
        else doLoop(input, t);
    } while (!input.empty());
    if (t == '\000') out.push_back(makeOutput("", "EOF", line));
    //out << "Total Tokens = " << num << endl; // num is initialized in header, tracks number of tokens
    return out;
}

void FSMBox::doLoop(stack<char> &input, char &t)
{
    if (isSymbol(t)) doSymbol(t);
    else if (t == ':') isColon(input, t);
    else if (t == '\'') isString(input, t);
    else if (t == '#') isComment(input, t);
    else if (isalpha(t)) isID(input, t);
    else out.push_back(makeOutput(t, "UNDEFINED", line));
}

bool FSMBox::isSymbol(char input)
{
    for (int i = 0; i < 7; ++i) {
        if (input == symbols[i]) return true;
    }
    return false;
}

void FSMBox::doSymbol(char input)
{
    if (input == ',') out.push_back(makeOutput(input, "COMMA", line));
    else if (input == '.') out.push_back(makeOutput(input, "PERIOD", line));
    else if (input == '?') out.push_back(makeOutput(input, "Q_MARK", line));
    else if (input == '(') out.push_back(makeOutput(input, "LEFT_PAREN", line));
    else if (input == ')') out.push_back(makeOutput(input, "RIGHT_PAREN", line));
    else if (input == '*') out.push_back(makeOutput(input, "MULTIPLY", line));
    else if (input == '+') out.push_back(makeOutput(input, "ADD", line));
}

void FSMBox::isColon(stack<char> &input, char &t)
{
    string co; // create string to hold colon
    co.push_back(t); // append colon to string
    if (input.top() == '-') { // if next char is dash
        co.push_back(input.top()); // append dash to string
        out.push_back(makeOutput(co, "COLON_DASH", line)); // format colon_dash
        // tk++; // increment pointer away from dash
        t = topnpop(input);
    }
    else out.push_back(makeOutput(co, "COLON", line)); // otherwise format colon
}

void FSMBox::isString(stack<char> &input, char &t)
{
    bool undef = false;
    string st = "'"; // initialize string string (lol)
    int l = line; // remember starting line number
    while (!input.empty()) {
        t = topnpop(input);
        if (t == '\000') {
            undef = true;
            break;
        }
        st.push_back(t);
        if (t == '\n') { line++; continue; }
        else if (t == '\'') {
            if (input.top() == '\'') {
                st.push_back('\'');
                t = topnpop(input);
                continue;
            }
            else break;
        }
    }
    if (undef == true) {
        out.push_back(makeOutput(st, "UNDEFINED", l));
    }
    else out.push_back(makeOutput(st, "STRING", l)); // format as string
}

void FSMBox::isComment(stack<char> &input, char &t)
{
    if (input.top() == '|') multiComment(input, t); // multiline comment
    else lineComment(input, t); // single line comment
}

void FSMBox::lineComment(stack<char> &input, char &t)
{
    string st = "#"; // initialize comment string
    // int l = line; // remember initial line number
    while (!input.empty()) {
        t = topnpop(input);
        if (t == '\n') { line++; break; }
        st.push_back(t);
    }
    // out << makeOutput(st, "COMMENT", l); // format as comment
}

void FSMBox::multiComment(stack<char> &input, char &t)
{
    string st = "#"; // initialize comment string
    // int l = line; // remember initial line number
    bool undef = false;
    t = topnpop(input);
    st.push_back(t); // place it in string
    while (!input.empty()) {
        t = topnpop(input);
        if (t == '\n') line++;
        else if (t == '\000') { undef = true; break; }
        st.push_back(t);
        if (t == '|' && input.top() == '#') {
            st.push_back(input.top());
            t = topnpop(input);
            break;
        }
    }
    if (undef == true) { // if EOF found before end of comment
        // out << makeOutput(st, "UNDEFINED", l); // format as undef
    }
    // else out << makeOutput(st, "COMMENT", l); // format as comment
}

void FSMBox::isID(stack<char> &input, char &t)
{
    bool undef = false; // tracks if token is undefined
    int l = line; // remember initial line
    string st = makeID(input, t);
    if (undef == true) out.push_back(makeOutput(st, "UNDEFINED", line)); // format as undef
    else {
        if (st == "Schemes") out.push_back(makeOutput(st, "SCHEMES", l));
        else if (st == "Facts") out.push_back(makeOutput(st, "FACTS", l));
        else if (st == "Rules") out.push_back(makeOutput(st, "RULES", l));
        else if (st == "Queries") out.push_back(makeOutput(st, "QUERIES", l));
        else out.push_back(makeOutput(st, "ID", l));
    }
}

string FSMBox::makeID(stack<char> &input, char &t)
{
    string st;
    st.push_back(t);
    while (!input.empty()) {
        t = topnpop(input);
        if (isalpha(t) || isdigit(t)) st.push_back(t);
        else if (isspace(t) && t != '\n') break;
        else if (t == '\n') { line++; break; }
        else { input.push(t); break; }
    }
    return st;
}

FSMBox::Token FSMBox::makeOutput(string out, string token, int line) // format token output string
{
    Token o(out, token, line);
    // o << "(" << token << ",\"" << out << "\"," << line << ")" << endl;
    num++;
    return o;
}

FSMBox::Token FSMBox::makeOutput(char out, string token, int line) //overload function to allow char input
{
    string s(1, out);
    Token o(s, token, line);
    // o << "(" << token << ",\"" << out << "\"," << line << ")" << endl;
    num++;
    return o;
}

char FSMBox::topnpop(stack<char> &input)
{
    char i = input.top();
    input.pop();
    return i;
}
