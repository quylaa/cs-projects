// Written by Aleks Christensen

#include "Path.h"

Path::Path()
{
    srand(time(0));
}

Path::~Path(){}

string Path::makeString()
{
    ostringstream smaze;
    for (int z = 0; z < 5; z++) {
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                smaze << maze[z][y][x] << " ";
            }
            smaze << "\n";
        }
        smaze << "\n";
    }
    return smaze.str();
}

bool Path::traverse(Maze<int, 5, 5, 5>& m, int x, int y, int z)
{    
    ostringstream coord;
    coord << "(" << x << ", " << y << ", " << z << ")";
    if (x == 4 && y == 4 && z == 4) {
        solution.push_back("(4, 4, 4)");
        return true;
    }
    if (m[z][y][x] == 2) return false;
    m[z][y][x] = 2;

    solution.push_back(coord.str());

    if ((z+1) < 5 && m[z+1][y][x] == 1) {
        if (traverse(m, x, y, z+1)) return true;
        else solution.pop_back();
    }
    if ((y+1) < 5 && m[z][y+1][x] == 1) {
        if (traverse(m, x, y+1, z)) return true;
        else solution.pop_back();
    }
    if ((x+1) < 5 && m[z][y][x+1] == 1) {
        if (traverse(m, x+1, y, z)) return true;
        else solution.pop_back();
    }
    if ((z-1) >= 0 && m[z-1][y][x] == 1) {
        if (traverse(m, x, y, z-1)) return true;
        else solution.pop_back();
    }
    if ((y-1) >= 0 && m[z][y-1][x] == 1) {
        if (traverse(m, x, y-1, z)) return true;
        else solution.pop_back();
    }
    if ((x-1) >= 0 && m[z][y][x-1] == 1) {
        if (traverse(m, x-1, y, z)) return true;
        else solution.pop_back();
    }

    return false;
}

string Path::getMaze()
{
    if (currentMaze.empty()) {
        if (maze[0][0][0] != 1) {
            return defaultMaze;
        } else {
            return makeString();
        }
    } else return currentMaze;
}

void Path::createRandomMaze()
{
    int ones = 0;
    int zeroes = 0;

    for (int z = 0; z < 5; z++) {
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                int r = rand() % 2;
                if (z == 0 && y == 0 && x == 0) r = 1;
                if (z == 4 && y == 4 && x == 4) r = 1;
                maze[z][y][x] = r;
                (r == 1) ? ones++ : zeroes++;
            }
        }
    }
    if (ones > zeroes) {
        if ((ones / 125.0) > 0.6) createRandomMaze();
    } else {
        if ((zeroes / 125.0) > 0.6) createRandomMaze();
    }
}

bool Path::importMaze(string fileName)
{
    vector<int> nums;
    Maze<int, 5, 5, 5> tmp;
    ifstream file(fileName);
    if (file) {
        for (string line; getline(file, line);) {
            istringstream iss(line);
            vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
            for (size_t i = 0; i < tokens.size(); i++) {
                if (tokens.at(i) == "1" || tokens.at(i) == "0") {
                    nums.push_back(stoi(tokens.at(i)));
                } else return false;
            }
        }
    } else return false;

    if (nums.size() != 125) return false;

    int n = 0;
    for (int z = 0; z < 5; z++) {
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                tmp[z][y][x] = nums.at(n);
                n++;
            }
        }
    }
    if (tmp[0][0][0] != 1) return false;
    if (tmp[4][4][4] != 1) return false;

    maze = tmp;
    return true;
}

vector<string> Path::solveMaze()
{
    vector<string> sol;
    solution.clear();

    Maze<int, 5, 5, 5> tmp = maze;
    if (traverse(tmp, 0, 0, 0)) {
        return solution;
    } else return sol;
}




