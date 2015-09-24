// Written by Aleks Christensen

#ifndef FSMBOX_H_
#define FSMBOX_H_

// #define COMMA ","
// #define PERIOD "."
// #define Q_MARK "?"
// #define LEFT_PAREN "("
// #define RIGHT_PAREN ")"
// #define COLON ":"
// #define COLON_DASH ":-"
// #define MULTIPLY "*"
// #define ADD "+"
// #define SCHEMES "Schemes"
// #define FACTS "Facts"
// #define RULES "Rules"
// #define QUERIES "Queries"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <iterator>
#include <cctype>

using namespace std;

class FSMBox
{
    public:

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
