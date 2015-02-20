// Written by Aleks Christensen

#ifndef EXPMAN_H_
#define EXPMAN_H_

#include "ExpressionManagerInterface.h"
#include <vector>

class ExpMan : public ExpressionManagerInterface
{
    private:
        stack<char> ops;
        stack<string> ands;
        stack<string> post;
        string output;

        char separators[6] = {'(', ')', '{', '}', '[', ']'};   
        char operators[5] = {'%', '*', '/', '+', '-'};
        int precedence[5] = {2, 2, 2, 1, 1};


    public:
        ExpMan();
        ~ExpMan();

        bool isNumber(const string exp);

        void untilMatch(char sep);

        void printStack(stack<char> stak);

        bool isSeparator(char exp);

        bool isOperator(char op);

        int getPrecedence(char op);

        bool isInfixValid(string expression);

        bool isPostfixValid(string expression);

        bool isBalanced(string expression);

        string postfixToInfix(string postfixExpression);

        string infixToPostfix(string infixExpression);

        string postfixEvaluate(string postfixExpression);

        void print(stack<char> stak);

};
#endif
