// Written by Aleks Christensen

#ifndef DATALOGPROGRAM_H_
#define DATALOGPROGRAM_H_

#include <stack>
#include <string>
#include <vector>

using namespace std;

class datalogProgram
{
    private:

        vector<string> schemes;
        vector<string> facts;
        vector<string> rules;
        vector<string> queries;


    public:

        datalogProgram();
        ~datalogProgram();

        parser()

        toString();
}

#endif
