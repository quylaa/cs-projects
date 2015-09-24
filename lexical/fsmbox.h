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

using namespace std;

class FSMBox
{
    // private:
    //     enum token_chars_t {COMMA = ",", PERIOD = ".", Q_MARK = "'",
    //     LEFT_PAREN = "(", RIGHT_PAREN = ")", COLON = ":", MULTIPLY = "*",
    //     ADD = "+"};

    public:

        FSMBox();
        ~FSMBox();

        /*
         * tokens
         *
         * Attempts to find and return as many tokens from the given string
         * as it can.
         *
         * Inputs: input string to find tokens from, current line number
         *
         */

        string tokens(string input, int line);

        /*
         * colon
         *
         * FSM that detects if input is a lone colon or a colon-dash
         *
         * Inputs: string with a colon
         *
         */
        string colon(string c);

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
