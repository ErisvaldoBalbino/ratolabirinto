#include <iostream>
#include <string>

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

// TODO: string com as direcoes
bool solveMaze(Stack& stack, int maze[4][4], int x, int y, int rows, int cols){

    // o queijo esta numa posicao fixa nesse caso
    // que e o final da matriz
    // TODO: deixar o usuario escolher a posicao do queijo, e do rato
    if (x == rows - 1 && y == cols - 1)
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
        if (solveMaze(stack, maze, x, y + 1, rows, cols))
        {
            //result += "D";
            return true;
        }

        // esquerda
        if (solveMaze(stack, maze, x, y - 1, rows, cols))
        {
            //result += "E";
            return true;
        }

        // cima
        if (solveMaze(stack, maze, x - 1, y, rows, cols))
        {
            //result += "C";
            return true;
        }

        // baixo
        if (solveMaze(stack, maze, x + 1, y, rows, cols))
        {
            //result += "B";
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


int main(){
    int maze[4][4] = {
        {1, 0, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1},
        {1, 1, 0, 1}
    };

    Stack stack;

    if (solveMaze(stack, maze, 0, 0, 4, 4)){
        std::cout << "o rato encontrou o queijo";
    } else {
        std::cout << "nenhum caminho para o queijo encontrado";
    }

    return 0;
};