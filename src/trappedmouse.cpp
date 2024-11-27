#include <iostream>
#include <string>
#include <vector>

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

class Maze {
    public:
        // Stack mazeRows;
        Stack mazeRows;

        // Arrays de String maze;
        std::vector<std::string> maze;

        void initMaze() {
            std::string line;
            // enquanto houver linhas para serem lidas faça
            // acho que esta funcionando :D
            while (std::getline(std::cin, line)) {
                // se a linha estiver vazia, sai do loop
                if (line.empty()) {
                    break;
                }
                // adicionar paredes nas extremidades;
                line = "1" + line + "1";
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
            // percorre o vetor de strings de tras para frente
            // porque a primeira linha do labirinto e a ultima linha do vetor
            for (int i = maze.size() - 1; i >= 0; i--) {
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