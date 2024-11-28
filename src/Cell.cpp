#include "../include/Cell.h"

Cell::Cell(int x, int y) : x(x), y(y) {}

int Cell::getX() const {
    return x;
}

int Cell::getY() const {
    return y;
}

bool operator==(const Cell& esquerda, const Cell& direita) {
    return esquerda.getX() == direita.getX() && esquerda.getY() == direita.getY();
}

bool operator!=(const Cell& esquerda, const Cell& direita) {
    return !(esquerda == direita);
}