#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include "Stack.cpp"
#include "Cell.cpp"
#include "Maze.cpp"

void showMenu() {
    std::cout << "\nEscolha o tipo de entrada: " << std::endl;
    std::cout << "1 - Arquivo" << std::endl;
    std::cout << "2 - Teclado" << std::endl;
    std::cout << "3 - Sair" << std::endl;
    std::cout << "Opcao: ";
}

void animateExit() {
    std::cout << "Saindo";
    for (int i = 0; i < 3; i++) {
        Sleep(500);
        std::cout << ".";
    }
    std::cout << std::endl;
}

int getInputType() {
    int opcao;
    while (true) {
        std::cin >> opcao;
        if (std::cin.fail() || (opcao < 1 || opcao > 3)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Entrada invalida. Tente novamente: ";
        } else {
            std::cin.ignore(); // esse nao precisa de 1000 pq so tem um caractere
            return opcao;
        }
    }
}

void solveTXT(Maze& maze) {
    int mazeCounter = 1;

    std::ifstream file("labirinto.txt");
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return;
    }

    std::cout << "Arquivo carregado..." << std::endl;
    while (file.good()) {
        maze.initMaze(file);
        std::cout << "\nLabirinto " << mazeCounter++ << ":" << std::endl;
        maze.printMaze();

        //std::cout << "\nTentando resolver o labirinto..." << std::endl;

        // os couts estao dentro do metodo
        maze.exitMaze();

        maze.clear();
    }

    file.close();
}

void solveManual(Maze& maze) {
    std::cout << "Digite as linhas do labirinto (enter para concluir): " << std::endl;
    maze.initMaze(std::cin);

    std::cout << "\nLabirinto: " << std::endl;
    maze.printMaze();

    //std::cout << "\nTentando resolver o labirinto..." << std::endl;

    maze.exitMaze();

    maze.clear();
}

int main() {
    Maze maze;

    while (true) {
        showMenu();
        int inputType = getInputType();

        if (inputType == 1) {
            solveTXT(maze);
        } else if (inputType == 2) {
            solveManual(maze);
        } else if (inputType == 3) {
            animateExit();
            break;
        }
    }

    return 0;
}