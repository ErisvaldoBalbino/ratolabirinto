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
        Maze() : currentCell(0, 0), exitCell(0, 0), entryCell(0, 0) {};
        Stack mazeRows;

        void initMaze(std::istream& input);
        void printMaze();
        bool exitMaze(Cell cell = Cell(1, 1));
        void clear();
        ~Maze();
};

#endif