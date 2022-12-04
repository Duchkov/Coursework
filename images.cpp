#include "images.h"

Images::Images()
{
    images.insert("background",QImage(":/Images/Images/background.png"));
    images.insert("field",QImage(":/Images/Images/field.jpg"));
    images.insert("ship",QImage(":/Images/Images/ship.jpg"));
    images.insert("shot",QImage(":/Images/Images/shot.jpg"));
    images.insert("hit",QImage(":/Images/Images/hit.jpg"));
}

QImage& Images::get(const QString &name)
{
    QMap<QString,QImage>::iterator i=images.find(name);
    if (i==images.end()) throw 1;
    return i.value();
}
