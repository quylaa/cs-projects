// Written by Aleks Christensen

#include "ExpMan.h"
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

ExpMan::ExpMan(){}

ExpMan::~ExpMan(){}

bool ExpMan::isNumber(const string exp)
{
    return !exp.empty() && find_if(exp.begin(), 
            exp.end(), [](char c) { return !isdigit(c); }) == exp.end();
}

void ExpMan::untilMatch(char sep) // pops operators off the stack until matching parenthesis is found
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
        output.push_back(ops.top());
        ops.pop();
    }
    ops.pop();
}

bool ExpMan::isSeparator(char exp) // returns true if given char is a parenthesis, bracket, or brace
{
    for (size_t i = 0; i < sizeof(separators); i++) {
        if (exp == separators[i]) return true;
    }
    return false;
}

bool ExpMan::isOperator(char op) // returns true if given char is +, -, *, /, or %
{
    for (size_t i = 0; i < sizeof(operators); i++) {
        if (op == operators[i]) return true;
    }
    return false;
}

int ExpMan::getPrecedence(char op) // returns precedence of given operator
{ 
    for (size_t i = 0; i < sizeof(operators); i++) {
        if (op == operators[i]) return precedence[i];
    }
    return -1;
}

bool ExpMan::isInfixValid(string expression) // returns true if given infix expression is valid
{
    char e;
    stack<char> things;
    if (expression.size() < 5) return false; // the shortest possible valid expression (2 + 2) is 5 characters long, anything shorter is invalid
    for (size_t i = 0; i < expression.size(); i++) {
        e = expression[i];
        if (!ExpMan::isSeparator(e) && !ExpMan::isOperator(e) && 
                !isdigit(e) && e != ' ' && e != '0') return false; // if given char is not an acceptable character, fail
        if (e == ' ') continue; // skip spaces
        if (isdigit(e)) things.push(e);
        if (ExpMan::isOperator(e)) { // check if trying to add to a close brace/parenthesis/bracket
            char next = expression[i+2];
            if (!isdigit(next) && next != '(' && 
                    next != '{' && next != '[') return false;
        }
    }
    return true;
}

bool ExpMan::isPostfixValid(string expression) // returns true if given postfix expression if valid
{
    istringstream iss(expression);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};

    int numNums = 0;
    for (size_t i = 0; i < tokens.size(); i++) {
        if (ExpMan::isNumber(tokens.at(i))) numNums++; // count amount of numbers
        if (ExpMan::isSeparator((*tokens.at(i).c_str()))) return false; // there should be no separators in a postfix expression
    }
    if (numNums > 0) return true; // if there are no numbers, something's wrong with the user
    return false;
}

bool ExpMan::isBalanced(string expression) // checks if the given expression's separators are balanced
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



string ExpMan::infixToPostfix(string infixExpression) // convert infix expression to postfix
{

    stringstream out;

    if (!ExpMan::isInfixValid(infixExpression)) return "invalid";

    if (!ExpMan::isBalanced(infixExpression)) return "invalid";

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
            while (!ops.empty() && 
                    ExpMan::getPrecedence(exp) <= ExpMan::getPrecedence(ops.top())) {
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

    output = out.str();
    output.pop_back();
    return output;
}

string ExpMan::postfixToInfix(string postfixExpression) // convert postfix expression to infix
{
    if (!ands.empty()) {
        while (!ands.empty()) {
            ands.pop();
        }
    }

    if (!ExpMan::isPostfixValid(postfixExpression)) return "invalid";

    istringstream iss(postfixExpression);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};

    for (size_t i = 0; i < tokens.size(); i++) {
        
        string exp = tokens.at(i);

        if (ExpMan::isNumber(exp)) ands.push(exp);
        else if (ExpMan::isOperator((*exp.c_str()))) {
            string first, second;
            if (!ands.empty()) {
                first = ands.top();
                ands.pop();
            } else return "invalid";
            if (!ands.empty()) {
                second = ands.top();
                ands.pop();
            } else return "invalid";

            stringstream temp;
            temp << "( " << first << " " << exp << " " << second << " )";
            ands.push(temp.str());
        }
    }
    istringstream oss(ands.top());
    vector<string> postfix{istream_iterator<string>{oss}, istream_iterator<string>{}};

    reverse(postfix.begin(), postfix.end());
    stringstream out;
    ands.pop();
    if (!ands.empty()) return "invalid";
    for (size_t j = 0; j < postfix.size(); j++) {
        if (postfix.at(j) == "(") out << ") ";
        else if (postfix.at(j) == ")") out << "( ";
        else out << postfix.at(j) << " ";
    }
    string put = out.str();
    put.pop_back();
    return put;
}

string ExpMan::postfixEvaluate(string postfixExpression) // evaluate given postfix expression
{
    if (!ExpMan::isPostfixValid(postfixExpression)) return "invalid";

    istringstream iss(postfixExpression);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};

    for (size_t i = 0; i < tokens.size(); i++) {

        string exp = tokens.at(i);
        
        if (ExpMan::isNumber(exp)) num.push(stoi(exp));
        else if (ExpMan::isOperator((*exp.c_str()))) {
            int first, second, result;
            if (!num.empty()) {
                first = num.top();
                num.pop();
            } else return "invalid";
            if (!num.empty()) {
                second = num.top();
                num.pop();
            } else return "invalid";

            if (exp == "+") result = second + first;
            else if (exp == "-") result = second - first;
            else if (exp == "*") result = second * first;
            else if (exp == "/") {
                if (first == 0) return "invalid";
                else result = second / first;
            }
            else if (exp == "%") result = second % first;

            num.push(result);
        }
    }
    ostringstream out;
    out << num.top();
    num.pop();
    if (!num.empty()) return "invalid";
    return out.str();
}
