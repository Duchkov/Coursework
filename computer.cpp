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
        if (comfield[random] != Hit)
        {
            comfield[random] = Ship;
            int t = random +9;
            if ((t>0) && (t<100))
            comfield[random+9] = Hit;
            t = random +11;
            if ((t>0) && (t<100))
            comfield[random+11] = Hit;
            t = random -11;
            if ((t>0) && (t<100))
            comfield[random-11] = Hit;
            t = random -9;
            if ((t>0) && (t<100))
            comfield[random-9] = Hit;
        }
    }
    for (int i=0; i<100;i++)
    {
        if (comfield[i] == Hit)
            comfield[i] = Empty;
    }
    return comfield;
}

QPoint Computer::attack(Battlefield *field)
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    QPoint pos;
    int random = qrand()% 10;
    pos.setX(random);
    random = qrand()% 10;
    pos.setY(random);
    return pos;
}