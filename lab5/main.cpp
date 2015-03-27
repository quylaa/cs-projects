#include "Path.h"

int main()
{
    Path* p = new Path();

    //cout << p->getMaze();
    /*p->createRandomMaze();*/
    //cout << p->getMaze();
    //cout << "--------------------" << endl;
    //p->createRandomMaze();
    /*cout << p->getMaze();*/
    if (p->importMaze("Solvable1.txt")) cout << p->getMaze();
    else if (p->importMaze("Mazes/Unsolvable3.txt")) cout << p->getMaze();
    else cout << "nope" << endl;

    vector<string> s;
    s = p->solveMaze();
    if (s.empty()) cout << "nosol" << endl;
    else {
        for (size_t i = 0; i < s.size(); i++) {
            cout << s.at(i) << endl;
        }
    }

    return 0;
}
