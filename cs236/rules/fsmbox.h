// Written by Aleks Christensen

#ifndef FSMBOX_H_
#define FSMBOX_H_

#include <stack>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include "token.h"

using namespace std;

class FSMBox
{
    public:

        int num = 0; // Number of tokens
        // ostringstream out; // output stringstream
        vector<Token> out;
        // stack<Token> out;
        int line = 1; // initialize line counter
        char symbols[7] = {',', '.', '?', '(', ')', '*', '+'};

        FSMBox();
        ~FSMBox();

        /*
         * tokens
         *
         * Attempts to find and return as many tokens from the given string
         * as it can.
         *
         */
        vector<Token> tokens(stack<char> input);

        /*
         * doLoop
         *
         * Loop through everything else
         *
         */
        void doLoop(stack<char> &input, char &t);

        /*
         * isSymbol
         *
         * Checks to see if char is a defined symbol token
         *
         */
        bool isSymbol(char input);

        /*
         * doSymbol
         *
         * If it is, handle it.
         *
         */
        void doSymbol(char input);

        /*
         * isColon
         *
         * Figure if token is colon or colon_dash
         *
         */
        void isColon(stack<char> &input, char &t);

        /*
         * isString
         *
         * Find and format string token
         *
         */
        void isString(stack<char> &input, char &t);

        /*
         * isComment
         *
         * Find and format comment
         *
         */
        void isComment(stack<char> &input, char &t);

        /*
         * lineComment
         *
         * Format single line comment
         *
         */
        void lineComment(stack<char> &input, char &t);

        /*
         * multiComment
         *
         * Format multiline comment
         *
         */
        void multiComment(stack<char> &input, char &t);

        /*
         * isID
         *
         * Find and format ID token
         *
         */
        void isID(stack<char> &input, char &t);

        /*
         * makeID
         *
         * Find and return ID token
         *
         */
        string makeID(stack<char> &input, char &t);

        /*
         * makeOutput
         *
         * Formats an output string to append to the output stringstream
         *
         * Inputs: string recognized as token, type of token recognized,
         *         line number
         *
         */
        Token makeOutput(string out, string token, int line);

        Token makeOutput(char out, string token, int line);

        char topnpop(stack<char> &input);
};

#endif
