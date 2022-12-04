#ifndef COMPUTER_H
#define COMPUTER_H
#include "battlefield.h"
#include <QTime>

class Computer
{
public:
    Computer();
    QVector<Cell> create();
};

#endif // COMPUTER_H
