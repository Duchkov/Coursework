#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include <QVector>
#include <QImage>
#include <QPainter>
#include "images.h"
#include <QDebug>
#include <QPoint>

enum Cell
{
    Empty,
    Ship,
    Hit,
    Shot

};

enum End
{
    Win,
    Lose,
    Not
};

struct statusShip{
    int num;
    bool alive;
};

class Battlefield
{
public:
    Battlefield(Images *images, int width, int height);
    ~Battlefield();
    void update(bool enemy);
    const QImage& get() const;
    void set(int x, int y, Cell cell);
    QPoint getCoordinates (int x, int y);
    bool canSet (int x, int y);
    Cell check(int x, int y);
    bool shot(int x, int y);
    void fill(QVector<Cell> combattlefield);
    End checkEnd();
    bool correct();
    QPoint monoShip(QPoint pos);
    statusShip status(QPoint pos);

private:
    QVector<Cell> battlefield;
    QVector<int> ships;
    QImage *image;
    Images *images;
    int width, height;
};

#endif // BATTLEFIELD_H
