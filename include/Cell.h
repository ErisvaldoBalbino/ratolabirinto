#ifndef CELL_H
#define CELL_H

class Cell {
    private:
        int x;
        int y;

    public:
        friend bool operator==(const Cell& esquerda, const Cell& direita);
        friend bool operator!=(const Cell& esquerda, const Cell& direita);
        int getX() const;
        int getY() const;
        Cell(int x, int y);
};

#endif