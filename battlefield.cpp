#include "battlefield.h"

Battlefield::Battlefield(Images *images,int width, int height):
    images(images), width(width), height(height)
{
    battlefield.fill(Empty,100);
    ships.fill(0,4);
    image = new QImage(width,height,QImage::Format_ARGB32);
}

Battlefield::~Battlefield()
{
    delete image;
}

void Battlefield::update()
{
    image->fill(0);
    QPainter painter(image);
    painter.drawImage(0,0,images->get("field"));
    for (int i=0; i<10; i++)
         for (int j=0; j<10; j++)
             switch(battlefield[i+10*j])
             {
                 case Ship:
                 painter.drawImage(i*32+50,j*32+52,images->get("ship"));
                 break;
                 default: break;
             }
}

const QImage& Battlefield::get() const
{
    return *image;
}

void Battlefield::set(int x, int y, Cell cell)
{
    qDebug() << "Ship" << x << y;
    QPoint Coord = getCoordinates(x, y);
    qDebug() << "Ship" << Coord.x() << Coord.y();
    int num = Coord.x()+Coord.y()*10;
    if (Coord.x() != -1)
    {
        if (battlefield[num] == Empty && canSet(Coord.x() ,Coord.y()))
        {
            battlefield[num] = cell;
        }else
        {
            battlefield[num] = Empty;
        }
    }
}

QPoint Battlefield::getCoordinates(int xx, int yy)
{
    QPoint Coordinates;
    Coordinates.setX(-1);
    Coordinates.setY(-1);
    int x = xx-50-50;
    int y = yy-50-52;
    qDebug() << "Ship" << x << y;
    if ((x>0)&& (y>0) && (x<320) && (y<320))
    {
       Coordinates.setX(x/32);
       Coordinates.setY(y/32);
       return Coordinates;
    }
    else
        return Coordinates;
}

bool Battlefield::canSet(int x, int y)
{
    if (check(x+1, y+1) == Empty && check(x-1, y+1) == Empty &&check(x+1, y-1) == Empty && check(x-1, y-1) == Empty)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Cell Battlefield::check(int x, int y)
{
    if (x>=0 && y>=0 && x<10 && y<10)
        return battlefield[x+y*10];
    return Empty;
}
