#include "images.h"

Images::Images(int size)
{
    switch(size)
    {
        case 8:
            images.insert("field",QImage(":/Images/Images/field8.jpg"));
            images.insert("enemy",QImage(":/Images/Images/enemy8.jpg"));
        break;
        case 10:
            images.insert("field",QImage(":/Images/Images/field.jpg"));
            images.insert("enemy",QImage(":/Images/Images/enemy.jpg"));
        break;
        case 12:
            images.insert("field",QImage(":/Images/Images/field12.jpg"));
            images.insert("enemy",QImage(":/Images/Images/enemy12.jpg"));
        break;
    }

    images.insert("background",QImage(":/Images/Images/background.png"));
    images.insert("ship",QImage(":/Images/Images/ship.jpg"));
    images.insert("shot",QImage(":/Images/Images/shot.jpg"));
    images.insert("hit",QImage(":/Images/Images/hit.jpg"));
    images.insert("start",QImage(":/Images/Images/start.jpg"));
    images.insert("win",QImage(":/Images/Images/win.png"));
    images.insert("lose",QImage(":/Images/Images/lose.png"));
    images.insert("menu",QImage(":/Images/Images/menu.jpg"));
}

QImage& Images::get(const QString &name)
{
    QMap<QString,QImage>::iterator i=images.find(name);
    if (i==images.end()) throw 1;
    return i.value();
}
