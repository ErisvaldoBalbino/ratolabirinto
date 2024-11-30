#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include <string>
#include <stack>
#include "Cell.h"
#include "Stack.h"

class Maze {
    private:
        // atributos 
        Cell currentCell;
        Cell exitCell;
        Cell entryCell;

        // constantes
        const char exitMarker = 'e';
        const char entryMarker = 'm';
        const char visited = '.';
        const char passage = '0';
        const char wall = '1';

        std::vector<std::string> maze;

    public:
        Maze() : currentCell(-1, -1), exitCell(-1, -1), entryCell(-1, -1) {};
        Stack mazeRows;

        void initMaze(std::istream& input);
        void printMaze();
        void resetCells();
        bool exitMaze(Cell cell = Cell(1, 1));
        void clear();
        ~Maze();
};

#endif