#ifndef STACK_H
#define STACK_H
#include <string>

class Stack
{
public:
    // vou definir o struct aqui mesmo pq e publico
    struct Node
    {
        std::string data;
        Node *next;
    };

    Stack()
    {
        top = nullptr;
    }

    Node *top;
    void push(const std::string &data);
    std::string pop();
    std::string peek() const;
    bool isEmpty() const;
    ~Stack();

};

#endif