#ifndef COMPUTER_H
#define COMPUTER_H
#include "battlefield.h"
#include <QTime>
#include <QPoint>

class Computer
{
public:
    Computer();
    QVector<Cell> create();
    QPoint attack(Battlefield *field);
};

#endif // COMPUTER_H
