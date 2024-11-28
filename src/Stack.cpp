#include "../include/Stack.h"
#include <string>

void Stack::push(const std::string &data)
{
    Node *newNode = new Node();
    newNode->data = data;
    newNode->next = top;
    top = newNode;
}

std::string Stack::pop()
{
    if (top == nullptr)
    {
        return "";
    }

    // guarda o topo da pilha
    Node *temp = top;
    // atualiza o topo da pilha
    top = top->next;
    // retorna o valor do topo da pilha
    std::string data = temp->data;
    // deleta o antigo topo da pilha
    delete temp;
    return data;
}

std::string Stack::peek() const
{
    if (top == nullptr)
    {
        return "";
    }

    return top->data;
}

bool Stack::isEmpty() const
{
    return top == nullptr;
}

Stack::~Stack()
{
    while (!isEmpty())
    {
        pop();
    }
}