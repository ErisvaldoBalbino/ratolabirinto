#include <iostream>

class Node {
public:
    int data;
    Node* next;

    Node(int value){
        this->data = value;
        next = nullptr;
    };
};

class Stack {
public:
    Node* top;

    Stack(){
        top = nullptr;
    };

    void push(int value){
        Node* newNode = new Node(value);

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

    int peek(){
        if (top != nullptr)
        {
            return top->data;
        }

        // vazio
        return -1;
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

void findAndPushArray(Stack& stack, int arr[], int x, int sizeArr, int index = 0){
    // se o index chegar no final da lista para a recursao
    if (index == sizeArr)
    {
        return;
    }

    // se o numero no indice for igual a x
    // adiciona a pilha e para a funcao
    if (arr[index] == x)
    {
        stack.push(arr[index]);
        std::cout << "Numero encontrado no indice " << index << " do vetor." << std::endl;
        return;
    }
    
    findAndPushArray(stack, arr, x, sizeArr, index + 1);
};

int main(){
    Stack stack;
    int x = 9;
    int arr[5] = {1,2,3,4,9};
    int size = 5;

    findAndPushArray(stack, arr, x, size);

    return 0;
};