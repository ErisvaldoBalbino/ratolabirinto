#include <iostream>
#include <string>
#include <algorithm>

class Node {
public:
    int x;
    int y;
    Node* next;

    Node(int row, int col){
        this->x = row;
        this->y = col;
        next = nullptr;
    };
};

class Stack {
public:
    Node* top;

    Stack(){
        top = nullptr;
    };

    void push(int x, int y){
        Node* newNode = new Node(x, y);

        newNode->next = top;
        top = newNode;
    }

    void pop(){
        if(top != nullptr){
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    std::pair<int, int> peek(){
        if (top != nullptr)
        {
            return {top->x, top->y};
        }

        // vazio
        return {-1, -1};
    }

    bool isEmpty(){
        // mesma coisa
        // return top == nullptr;
        if (top == nullptr)
        {
            return true;
        }
        
        return false;
    }

};

//TODO: adicionar os caracteres na ordem certa
bool solveMaze(Stack& stack, int maze[4][4], int x, int y,int qx,int qy, int rows, int cols, std::string& result){

    // agora o usuario pode escolher a posicao do queioj
    //std::cout << "x: " << x << ", y: " << y << " | qx: " << qx << ", qy: " << qy << std::endl;
    if (x == qx && y == qy)
    {
        stack.push(x, y);
        return true;
    }

    // verifica se a posicao e valida
    // x e y precisam estar dentro da matriz
    // e nao podem ser < 0, se nao seriam uma posicao ja visitada
    // a posicao tambem precisa ser = 1, o que indica que esta livre
    if (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == 1)
    {
        // marca a posicao como visitada
        maze[x][y] = -1;

        // adiciona a pilha
        stack.push(x, y);

        // direita
        if (solveMaze(stack, maze, x, y + 1,qx,qy, rows, cols, result))
        {
            result += "D";
            return true;
        }

        // esquerda
        if (solveMaze(stack, maze, x, y - 1,qx,qy, rows, cols, result))
        {
            result += "E";
            return true;
        }

        // cima
        if (solveMaze(stack, maze, x - 1, y,qx,qy, rows, cols, result))
        {
            result += "C";
            return true;
        }

        // baixo
        if (solveMaze(stack, maze, x + 1, y,qx,qy, rows, cols, result))
        {
            result += "B";
            return true;
        }
        
        // se nenhum retornar true
        // tira da pilha
        stack.pop();

        // e marca a posicao como livre
        maze[x][y] = 1;
        
    }
    
    // nenhum caminho encontrado
    return false;
    

};

//void findAndPushArray(Stack& stack, int arr[], int x, int sizeArr, int index = 0){
//    // se o index chegar no final da lista para a recursao
//    if (index == sizeArr)
//    {
//        return;
//    }
//
//    // se o numero no indice for igual a x
//    // adiciona a pilha e para a funcao
//    if (arr[index] == x)
//    {
//        stack.push(arr[index]);
//        std::cout << "Numero encontrado no indice " << index << " do vetor." << std::endl;
//        return;
//    }
//    
//    findAndPushArray(stack, arr, x, sizeArr, index + 1);
//};

//TODO: visualizar caminho
int main() {
    int maze[4][4] = {
        {1, 0, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1},
        {1, 1, 0, 1}
    };

    Stack stack;
    std::string result;
    int x = 0, y = 0;
    int qx = 0, qy = 0;

    //rato
    while (true) {
        std::cout << "Escolha a posicao do rato (x, y): ";
        std::cin >> x >> y;
        if (x >= 0 && x < 4 && y >= 0 && y < 4 && maze[x][y] == 1) {
            break;
        }
        std::cerr << "essa posicao nao e valida" << std::endl;
    }

    // queijo
    while (true) {
        std::cout << "Escolha a posicao do queijo (x, y): ";
        std::cin >> qx >> qy;
        if (qx >= 0 && qx < 4 && qy >= 0 && qy < 4 && maze[qx][qy] == 1) {
            if (qx == x && qy == y) {
                std::cerr << "o rato esta na mesma posicao do queijo...";
                return 0;
            }
            break;
        }
        std::cerr << "essa posicao nao e valida";
    }

    if (solveMaze(stack, maze, x, y, qx, qy, 4, 4, result)) {
        std::cout << "o rato encontrou o queijo" << std::endl;
        // precisa inverter pq a funcao adiciona os caminhos
        // ao contrario
        std::reverse(result.begin(), result.end());
        std::cout << "caminho: " << result << std::endl;
    } else {
        std::cout << "nenhum caminho para o queijo encontrado" << std::endl;
    }

    return 0;
}