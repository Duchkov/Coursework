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
    Battlefield(Images *images);
    ~Battlefield();
    void update();
    const QImage& get() const;

private:
    QVector<Cell> battlefield;
    QImage *image;
    Images *images;
};

#endif // BATTLEFIELD_H
