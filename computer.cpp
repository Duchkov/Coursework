#include "computer.h"

Computer::Computer()
{

}

QVector<Cell> Computer::create()
{
    QVector<Cell> comfield;
    comfield.fill(Empty,100);
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    for (int i=0; i<30;i++)
    {
        int random = qrand()% 100;
        comfield[random] = Ship;
    }
    return comfield;
}
