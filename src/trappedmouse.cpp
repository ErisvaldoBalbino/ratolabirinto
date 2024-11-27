#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Stack {
    public:
        struct Node {
            std::string data;
            Node* next;
        };

        Node* top;

        Stack() {
            top = nullptr;
        }

        void push(const std::string& data) {
            Node* newNode = new Node();
            newNode->data = data;
            newNode->next = top;
            top = newNode;
        }

        std::string pop() {
            if (top == nullptr) {
                return "";
            }

            // guarda o topo da pilha
            Node* temp = top;
            // atualiza o topo da pilha
            top = top->next;
            // retorna o valor do topo da pilha
            std::string data = temp->data;
            // deleta o antigo topo da pilha
            delete temp;
            return data;
        }

        std::string peek() const {
            if (top == nullptr) {
                return "";
            }

            return top->data;
        }

        bool isEmpty() const {
            return top == nullptr;
        }

        ~Stack() {
            while (!isEmpty()) {
                pop();
            }
        }
};

class Cell {
    private:
        int x;
        int y;

    public:
        bool operator==(const Cell& outro) const {
            return x == outro.x && y == outro.y;
        }

        Cell(int x, int y) : x(x), y(y) {}
};

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

        // pilha de cell
        Stack mazeStack;

        // Stack mazeRows;
        Stack mazeRows;

        // Arrays de String maze;
        std::vector<std::string> maze;

    public:
        Maze() : currentCell(0, 0), exitCell(0, 0), entryCell(0, 0) {}

        void initMaze() {
            std::string line;

            //TODO: aceitar apenas 1,0,e,m
            // enquanto houver linhas para serem lidas faça
            while (std::getline(std::cin, line)) {
                // se a linha estiver vazia, sai do loop
                if (line.empty()) {
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

        void printMaze() {
            // melhor reverter do que percorrer de tras pra frente
            std::reverse(maze.begin(), maze.end());
            for (int i = 0; i < maze.size(); i++) {
                std::cout << maze[i] << std::endl;
            }
        }
};

int main() {
    Maze maze;

    int inputType;

    std::cout << "Escolha o tipo de entrada: " << std::endl;
    std::cout << "1 - Arquivo" << std::endl;
    std::cout << "2 - Teclado" << std::endl;

    std::cin >> inputType;
    std::cin.ignore(); // limpa o buffer do teclado, para evitar ler o '\n'

    if (inputType == 1) {
        std::cout << "Arquivo..." << std::endl;
        //TODO: implementar r  r rrrr r rrr :(
    } else if (inputType == 2) {
        std::cout << "Digite as linhas do labirinto" << std::endl;
        maze.initMaze();
    }

    std::cout << "Labirinto: " << std::endl;
    maze.printMaze();

    return 0;
}