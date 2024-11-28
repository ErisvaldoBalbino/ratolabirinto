#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <fstream>
#include <istream>
#include "Stack.cpp"
#include "Cell.cpp"
#include "Maze.cpp"

int main() {
    Maze maze;
    int inputType;
    int mazeCounter = 1;
    std::cout << "Escolha o tipo de entrada: " << std::endl;
    std::cout << "1 - Arquivo" << std::endl;
    std::cout << "2 - Teclado" << std::endl;
    std::cin >> inputType;
    std::cin.ignore(); // limpa o buffer do teclado, para evitar ler o '\n'
    
    if (inputType == 1) {
        std::ifstream file("labirinto.txt"); // abre o arquivo
        if (!file.is_open()) {
            std::cerr << "Erro ao abrir o arquivo!" << std::endl;
            return 1;
        }
    
        std::cout << "Arquivo carregado..." << std::endl;
        while (file.good()) // enquanto o arquivo estiver aberto
        {
            maze.initMaze(file); // passo o arquivo como argumento
            // printa e resolve
            std::cout << "Labirinto " << mazeCounter++ << std::endl;
            maze.printMaze();
            std::cout << "Labirinto resolvido: " << std::endl;
            maze.exitMaze();
            // limpa o labirinto
            maze.clear();
        }
        
        file.close(); // fecha o arquivo
    } else if (inputType == 2) {
        std::cout << "Digite as linhas do labirinto" << std::endl;
        maze.initMaze(std::cin); // passo o cin como argumento
        maze.exitMaze();
        maze.printMaze();
    }

    return 0;
}