#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include <QVector>
#include <QImage>
#include <QPainter>
#include "images.h"

enum Cell
{
    Empty,
    Ship,
    Hit,
    Shot

};

class Battlefield
{
public:
    Battlefield(Images *images, int width, int height);
    ~Battlefield();
    void update();
    const QImage& get() const;
    void set(int x, int y, Cell cell);

private:
    QVector<Cell> battlefield;
    QImage *image;
    Images *images;
    int width, height;
};

#endif // BATTLEFIELD_H
