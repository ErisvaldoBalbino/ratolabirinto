#include "../include/Maze.h"
#include "../include/Cell.h"
#include "../include/Stack.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <iterator>

void Maze::initMaze(std::istream& input) {
    std::string line;
    std::string invalidChar; // caracteres invalidos

    // enquanto houver linhas para serem lidas faça
    while (std::getline(input, line)) {
        // a linha vazia e melhor
        if (line.empty()) {
            break;
        }

        // verifica se a linha contem caracteres invalidos
        invalidChar.clear(); // limpa antes pq pode ter caracteres invalidos de outra linha
        // verifica se a linha contem caracteres invalidos
        // se sim, adiciona na string invalidChar
        for (char c : line) {
            if (c != '0' && c != '1' && c != 'e' && c != 'm') {
                invalidChar += c;
            }
        }

        // se tiver algo na string
        // printa os caracteres invalidos
        if (!invalidChar.empty()) {
            std::cerr << "Caracteres invalidos: " << invalidChar << std::endl;
            continue;
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

// mudei o metodo pq ele estava invertendo o vetor
// e estava dando erro no exitMaze
void Maze::printMaze() {
    // mesma coisa que o reverse_copy
    //std::copy(maze.rbegin(), maze.rend(), std::ostream_iterator<std::string>(std::cout, "\n"));
    std::reverse_copy(maze.begin(), maze.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

// criei esse metodo para resetar as celulas
// antes de fazer as verificacoes
void Maze::resetCells() {
    entryCell = Cell(-1, -1);
    exitCell = Cell(-1, -1);
    currentCell = Cell(-1, -1);
}

bool Maze::exitMaze(Cell cell) {
    resetCells(); // reseta as celulas antes de resolver o labirinto
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

    if (entryCell == Cell(-1, -1) && exitCell == Cell(-1, -1)) {
        std::cerr << "Labirinto sem entrada e saida." << std::endl;
        return false;
    }
    
    if (entryCell == Cell(-1, -1)) {
        std::cerr << "Labirinto sem entrada." << std::endl;
        return false;
    }

    if (exitCell == Cell(-1, -1)) {
        std::cerr << "Labirinto sem saida." << std::endl;
        return false;
    }

    // esse nem precisa
    if (entryCell == exitCell) {
        std::cerr << "Entrada e saida iguais." << std::endl;
        return false;
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
            std::cout << "Caminho nao encontrado" << std::endl;
            return false;
        } else {
            // senao, atualiza a currentCell
            currentCell = mazeStack.top();
            mazeStack.pop();
        }

        // animacao
        // nao fica muito bom se forem varios labirintos
        // depois vou colocar o numero do labirinto
        // acima da animcao
        system("cls"); // limpa a tela
        printMaze(); // printa o labirinto
        Sleep(500); // espera Xms, ainda nao defini exatamente quanto
        
    }
        // printa o labirinto
        std::cout << "Labirinto resolvido: " << std::endl;
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