// Written by Aleks Christensen

#include "ExpMan.h"
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

ExpMan::ExpMan(){}

ExpMan::~ExpMan(){}

void ExpMan::untilMatch(char sep)
{
    char trigger;

    if (sep == ')') {
        trigger = '(';
    } else if (sep == '}') {
        trigger = '{';
    } else if (sep == ']') {
        trigger = '[';
    }

    while (ops.top() != trigger) {
        //output.push(ops.top());
        output.push_back(ops.top());
        ops.pop();
    }
    ops.pop();
}

void ExpMan::printStack(stack<char> stak)
{
    while (!stak.empty()) {
        cout << stak.top();
        stak.pop();
    }
    cout << endl;
}

bool ExpMan::isSeparator(char exp)
{
    for (size_t i = 0; i < sizeof(separators); i++) {
        if (exp == separators[i]) return true;
    }
    return false;
}

bool ExpMan::isOperator(char op)
{
    for (size_t i = 0; i < sizeof(operators); i++) {
        if (op == operators[i]) return true;
    }
    return false;
}

int ExpMan::getPrecedence(char op)
{ 
    for (size_t i = 0; i < sizeof(operators); i++) {
        if (op == operators[i]) return precedence[i];
    }
    return -1;
}

bool ExpMan::isValid(string expression)
{
    char e;
    stack<char> things;
    if (expression.size() < 5) return false; // the shortest possible valid expression (2 + 2) is 5 characters long, anything shorter is invalid
    for (size_t i = 0; i < expression.size(); i++) {
        e = expression[i];
        if (!ExpMan::isSeparator(e) && !ExpMan::isOperator(e) && !isdigit(e) && e != ' ' && e != '0') return false;
        if (e == ' ') continue;
        if (isdigit(e)) things.push(e);
        if (ExpMan::isOperator(e)) {
            char next = expression[i+2];
            if (!isdigit(next) && next != '(' && next != '{' && next != '[') return false;
        }
    }
    return true;
}

bool ExpMan::isBalanced(string expression)
{
    if (!ops.empty()) {
        while (!ops.empty()) {
            ops.pop();
        }
    }

    if (expression.empty()) return false;

    char exp;

    for (size_t i = 0; i < expression.size(); i++) {
        exp = expression[i];
        if (exp == ' ') continue;
        if (ExpMan::isSeparator(exp)) {
            if (exp == '(') {
                ops.push(exp);
            } else if (exp == ')') {
                if (!ops.empty() && ops.top() == '(') {
                    ops.pop();
                }
                else return false;
            } else if (exp == '{') {
                ops.push(exp);
            } else if (exp == '}') {
                if (!ops.empty() && ops.top() == '{') {
                    ops.pop();
                }
                else return false;
            } else if (exp == '[') {
                ops.push(exp);
            } else if (exp == ']') {
                if (!ops.empty() && ops.top() == '[') {
                    ops.pop();
                }
                else return false;
            }
        }
    }
    if (ops.empty()) return true;
    else return false;
}



string ExpMan::infixToPostfix(string infixExpression)
{

    stringstream out;

    if (!ExpMan::isValid(infixExpression)) return "invalid";

    if (!ExpMan::isBalanced(infixExpression)) {
        return "invalid";
    }

    istringstream iss(infixExpression);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};

    if (tokens.empty()) return "invalid";

    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens.at(i).size() > 1) {
            out << tokens.at(i) << ' ';
            continue;
        }
        const char* conv = tokens.at(i).c_str();
        char exp = (*conv);

        if (exp == ' ') continue;
        if (isdigit(exp) || exp == '0') {
            out << exp << ' ';
        }
        else if (ExpMan::isOperator(exp)) {
            while (!ops.empty() && ExpMan::getPrecedence(exp) <= ExpMan::getPrecedence(ops.top())) {
                out << ops.top() << ' ';
                ops.pop();
            }
            ops.push(exp);
        }
        else if (ExpMan::isSeparator(exp)) {
            if (exp == '(' || exp == '{' || exp == '[') {
                ops.push(exp);
            } else {
                char trigger;
                if (exp == ')') trigger = '(';
                else if (exp == '}') trigger = '{';
                else if (exp == ']') trigger = '[';

                while (ops.top() != trigger) {
                    out << ops.top() << ' ';
                    ops.pop();
                }
                ops.pop();
            }
        }
    }

    if (!ops.empty()) {
        while (!ops.empty()) {
            out << ops.top() << ' ';
            ops.pop();
        }
    }

    //cout << "output: " << out.str() << endl;
    output = out.str();
    output.pop_back();
    return output;
}

string ExpMan::postfixToInfix(string postfixExpression)
{
    return "invalid";
}
string ExpMan::postfixEvaluate(string postfixExpression)
{
    return "invalid";
}
