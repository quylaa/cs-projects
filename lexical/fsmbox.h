// Written by Aleks Christensen

#ifndef FSMBOX_H_
#define FSMBOX_H_

#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <cctype>
#include <iostream>

using namespace std;

class FSMBox
{
    public:

        int num = 0; // Number of tokens
        ostringstream out; // output stringstream
        int line = 1; // initialize line counter

        FSMBox();
        ~FSMBox();

        /*
         * tokens
         *
         * Attempts to find and return as many tokens from the given string
         * as it can.
         *
         */
        string tokens(string input);

        /*
         * isColon
         *
         * Figure if token is colon or colon_dash
         *
         */
        void isColon(string input, string::iterator &tk);

        /*
         * isString
         *
         * Find and format string token
         *
         */
        void isString(string input, string::iterator &tk);

        /*
         * isComment
         *
         * Find and format comment
         *
         */
        void isComment(string input, string::iterator &tk);

        /*
         * isID
         *
         * Find and format ID token
         *
         */
        void isID(string input, string::iterator &tk);

        /*
         * makeOutput
         *
         * Formats an output string to append to the output stringstream
         *
         * Inputs: string recognized as token, type of token recognized,
         *         line number
         *
         */
        string makeOutput(string out, string token, int line);

        string makeOutput(char out, string token, int line);
};

#endif
