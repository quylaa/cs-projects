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

        FSMBox();
        ~FSMBox();

        /*
         * tokens
         *
         * Attempts to find and return as many tokens from the given string
         * as it can.
         *
         * Inputs: input string to find tokens from
         *
         */
        string tokens(string input);

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
