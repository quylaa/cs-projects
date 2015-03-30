// Written by Aleks Christensen

#ifndef PATH_H_
#define PATH_H_

#include "PathfinderInterface.h" // includes iostream, string, vector
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <array>

class Path : public PathfinderInterface
{
    private:

        template <class T, size_t x, size_t y, size_t z>
            using Maze = array<array<array<T, z>, y>, x>;

        vector<string> solution;
        string currentMaze;
        Maze<int, 5, 5, 5> maze;

        string defaultMaze = "1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n\n";

        /*
         * makeString
         *
         * Returns a string representation of the maze array
         */
        string makeString();

        /*
         * traverse
         *
         * Move through maze, attempting to find path
         * Returns true if path found, false otherwise
         */
        bool traverse(Maze<int, 5, 5, 5>& m, int x, int y, int z);

    public:

        Path();
        ~Path();

        /*
         * getMaze
         *
         * Returns a string of the current maze. Returns a maze of all 1s if no maze
         * has been imported or generated yet.
         * A valid string representation of a maze has only 125 1s and 0s (each separated
         * by spaces) arranged in five 5x5 grids (separated by newlines) A valid maze
         * must also have a 1 in the entrance cell (0,0,0) and exit cell (4,4,4).
         * Cell (0,0,0) is represented by the first number in the string of the maze.
         * Moving x means moving east, so (1,0,0) is the second number. 
         * Moving y means moving south, so (0,1,0) is the sixth number. 
         * Moving z means moving to a new grid, so (0,0,1) is the 26th number.
         *
         * Returns:     string
         *              A single string representing the current maze
         */
        string getMaze();

        /*
         * createRandomMaze
         *
         * Generates a random maze and stores is as the current maze
         * The generated maze must have a roughly equal number of 1s and 0s and
         * must have a 1 in the entrance and exit cells.
         * The maze may be solvable or unsolvable, and this should produce both.
         */
        void createRandomMaze();

        /*
         * importMaze
         * Reads a maze from a file with the given name and stores it as the current maze.
         * Does nothing if the file does not exist or if the maze is invalid.
         * The file's contents must be of the format described above to be valid.
         *
         * Parameter:   fileName
         *              Name of file containing maze
         * Returns:     bool
         *              True if imported correctly, false, otherwise
         */
        bool importMaze(string fileName);

        /*
         * solveMaze
         * 
         * Attempts to solve current maze and returns solution if one is found.
         * A solution is a list of coordinates for the path from the entrance to the exit,
         * or an empty vector if no solution is found. This list cannot contain duplicates, 
         * and any two consecutive coordinates in the list can only differ by 1 for only 
         * one coordinate. The entrance and exit cells should be included int the solution.
         * Each string in the solution vector must be of the format "(x, y, z)".
         * Most mazes will contain multiple solutions.
         *
         * Returns:     vector<string>
         *              A solution to the current maze, or an empty vector if none exists
         */
        vector<string> solveMaze();

};

#endif
