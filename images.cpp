#include "images.h"

Images::Images()
{
    images.insert("background",QImage("C:/Curse/SeaBattle/Images/background"));
    images.insert("field",QImage("C:/Curse/SeaBattle/Images/field"));
    images.insert("ship",QImage("C:/Curse/SeaBattle/Images/ship"));
    images.insert("shot",QImage("C:/Curse/SeaBattle/Images/shot"));
    images.insert("hit",QImage("C:/Curse/SeaBattle/Images/hit"));
}

QImage& Images::get(const QString &name)
{
    QMap<QString,QImage>::iterator i=images.find(name);
    if (i==images.end()) throw 1;
    return i.value();
}
