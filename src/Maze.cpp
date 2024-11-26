#include "../include/Maze.h"
#include "../include/Cell.h"
#include "../include/Stack.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void Maze::initMaze(std::istream& input) {
    std::string line;

    //TODO: aceitar apenas 1,0,e,m
    // enquanto houver linhas para serem lidas faça
    while (std::getline(input, line)) {
        // se a linha for igual a "-" para o input
        if (line == "-") {
            break;
        }
        // adicionar paredes nas extremidades;
        line = wall + line + wall;
        // fazer um push na pilha;
        mazeRows.push(line);
    }	
    
    // adicionar em maze a primeira linha de paredes;
    if (!mazeRows.isEmpty()) {
        // peek() retorna o topo da pilha
        // length() retorna o tamanho da string
        int rowSize = mazeRows.peek().length();
        // cria uma string com tamanho da linha preenchida com '1'
        std::string wall(rowSize, '1');
        maze.push_back(wall);
    }
    
    // realizar pops na pilha adicionando em maze;
    while (!mazeRows.isEmpty()) {
        maze.push_back(mazeRows.pop());
    }
    
    // adicionar em maze a última linha de paredes;
    if (!maze.empty()) {
        // back() retorna a ultima linha do vetor
        // length() retorna o tamanho da string
        int rowSize = maze.back().length();
        // cria uma string com tamanho da linha preenchida com '1'
        std::string wall(rowSize, '1');
        maze.push_back(wall);
    }
}

void Maze::printMaze() {
    // melhor reverter do que percorrer de tras pra frente
    std::reverse(maze.begin(), maze.end());
    for (int i = 0; i < maze.size(); i++) {
        std::cout << maze[i] << std::endl;
    }
}

bool Maze::exitMaze(Cell cell) {
    // eu acho que tenho que usar aquela pilha privada
    // mas nao sei como
    std::stack<Cell> mazeStack;
    // percorre o labirinto procurando a entrada e a saída
    if (cell == Cell(1, 1)) {
        // linha
        for (int i = 0; i < maze.size(); i++) {
            // coluna
            for (int j = 0; j < maze[i].length(); j++) {
                if (maze[i][j] == entryMarker) {
                    // seta a entrada como a cell atual
                    entryCell = Cell(i, j);
                    currentCell = entryCell;
                } else if (maze[i][j] == exitMarker) {
                    // saida
                    exitCell = Cell(i, j);
                }
            }
        }
    }

    // enquanto currentCell nao for exitCell faca
    while (currentCell != exitCell) {

        // variaveis
        int x = currentCell.getX();
        int y = currentCell.getY();

        // marca current cell como visitada
        if (maze[x][y] != entryMarker && maze[x][y] != exitMarker) {
            maze[x][y] = visited;
        }

        // coloca os vizinhos na pilha
        // ordem: direita, esquerda, baixo e cima
        if (maze[x][y + 1] != wall && maze[x][y + 1] != visited) {
            mazeStack.push(Cell(x, y + 1));
        }
        if (maze[x][y - 1] != wall && maze[x][y - 1] != visited) {
            mazeStack.push(Cell(x, y - 1));
        }
        if (maze[x + 1][y] != wall && maze[x + 1][y] != visited) {
            mazeStack.push(Cell(x + 1, y));
        }
        if (maze[x - 1][y] != wall && maze[x - 1][y] != visited) {
            mazeStack.push(Cell(x - 1, y));
        }

        // se a pilha estiver vazia, caminho nao encontrado
        if (mazeStack.empty()) {
            std::cout << "caminho nao encontrado" << std::endl;
            return false;
        } else {
            // senao, atualiza a currentCell
            currentCell = mazeStack.top();
            mazeStack.pop();
        }
    }

        // printa o labirinto
        std::reverse(maze.begin(), maze.end());
        printMaze();
        return true;
}

void Maze::clear() {
    maze.clear();
}

Maze::~Maze() {
    while (!mazeRows.isEmpty()) {
        mazeRows.pop();
    }
}