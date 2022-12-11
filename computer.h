#ifndef COMPUTER_H
#define COMPUTER_H
#include "battlefield.h"
#include <QTime>
#include <QPoint>

struct Memory
{
    QPoint pos;
    int direction;
};

class Computer
{
public:
    Computer(int size);
    QVector<Cell> create();
    QPoint attack(Battlefield *field);
    Memory memory;
    Cell check(int x, int y);
    QVector<Cell> comfield;
    int fieldSize;

};

#endif // COMPUTER_H
