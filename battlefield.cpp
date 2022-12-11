#include "battlefield.h"

Battlefield::Battlefield(Images *images,int width, int height, int size):
    images(images), width(width), height(height), fieldSize(size)
{
    ships.fill(0,4);
    battlefield.fill(Empty,fieldSize*fieldSize);
    switch(fieldSize)
    {
        case 8:
                image = new QImage(422-64,422-64,QImage::Format_ARGB32);
        break;
        case 10:
                image = new QImage(422,422,QImage::Format_ARGB32);
        break;
        case 12:
               image = new QImage(422+64,422+64,QImage::Format_ARGB32);
        break;
    }
}

Battlefield::~Battlefield()
{
    delete image;
}

void Battlefield::update(bool enemy)
{
    image->fill(0);
    QPainter painter(image);
    painter.drawImage(0,0,images->get("field"));
    for (int i=0; i<fieldSize; i++)
         for (int j=0; j<fieldSize; j++)
             if (enemy)
             {
                 switch(battlefield[i+fieldSize*j])
                 {
                     case Shot:
                     painter.drawImage(i*32+50,j*32+52,images->get("shot"));
                     break;
                     case Hit:
                     painter.drawImage(i*32+50,j*32+52,images->get("hit"));
                     break;
                     default: break;
                 }
             }
             else
             {
                 switch(battlefield[i+fieldSize*j])
                 {
                     case Ship:
                     painter.drawImage(i*32+50,j*32+52,images->get("ship"));
                     break;
                     case Shot:
                     painter.drawImage(i*32+50,j*32+52,images->get("shot"));
                     break;
                     case Hit:
                     painter.drawImage(i*32+50,j*32+52,images->get("hit"));
                     break;
                     default: break;
                 }
             }
}

const QImage& Battlefield::get() const
{
    return *image;
}

void Battlefield::set(int x, int y, Cell cell)
{
    //qDebug() << "Ship" << x+50 << y+50;
    QPoint Coord = getCoordinates(x, y);
    //qDebug() << "Ship" << Coord.x() << Coord.y();
    int num = Coord.x()+Coord.y()*fieldSize;
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
    int x = xx-50;
    int y = yy-52;
    //qDebug() << "Ship" << x << y;
    if ((x>=0)&& (y>=0) && (x<=32*fieldSize) && (y<=32*fieldSize))
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
    if (x>=0 && y>=0 && x<fieldSize && y<fieldSize)
        return battlefield[x+y*fieldSize];
    return Empty;
}

ShotField Battlefield::shot(int x, int y)
{
    ShotField result;
    result.shot = false;
    result.hit = false;
    //qDebug() << "Ship" << x+50 << y+50;
    QPoint Coord = getCoordinates(x, y);
    //qDebug() << "Ship" << Coord.x() << Coord.y();
    int num = Coord.x()+Coord.y()*fieldSize;
    if (Coord.x() != -1)
    {
        switch(battlefield[num])
        {
            case Empty:
                result.shot = true;
                battlefield[num] = Shot;
                qDebug() <<"stat" << status(Coord).num << status(Coord).alive;
            break;
            case Ship:
                result.shot = true;
                result.hit = true;
                battlefield[num] = Hit;
                qDebug() <<"stat" << status(Coord).num << status(Coord).alive;
                if (status(Coord).alive == false)
                {
                    while (monoShip(Coord, false).x() != -1)
                    {
                        Coord = monoShip(Coord, false);
                    }
                    if (Coord.y()-1 >= 0)
                        battlefield[Coord.x()-fieldSize+Coord.y()*fieldSize] = Shot;
                    if (Coord.x()-1 >= 0)
                        battlefield[Coord.x()-1+Coord.y()*fieldSize] = Shot;
                    QPoint res;
                    do
                    {
                        if (Coord.x()+1 < fieldSize && Coord.y()+1 < fieldSize)
                            battlefield[Coord.x()+fieldSize+1+Coord.y()*fieldSize] = Shot;
                        if (Coord.x()+1 < fieldSize && Coord.y()-1 >= 0)
                            battlefield[Coord.x()-fieldSize+1+Coord.y()*fieldSize] = Shot;
                        if (Coord.x()-1 >= 0 && Coord.y()+1 < fieldSize)
                            battlefield[Coord.x()+fieldSize-1+Coord.y()*fieldSize] = Shot;
                        if (Coord.x()-1 >= 0 && Coord.y()-1 >= 0)
                            battlefield[Coord.x()-fieldSize-1+Coord.y()*fieldSize] = Shot;
                        res = Coord;
                        Coord = monoShip(Coord, true);
                    }while (Coord.x() != -1);
                    if (res.y()+1 < fieldSize)
                        battlefield[res.x()+fieldSize+res.y()*fieldSize] = Shot;
                    if (res.x()+1 < fieldSize)
                        battlefield[res.x()+1+res.y()*fieldSize] = Shot;
                }
            break;
            default:
                return result;
            break;
        }
        return result;
    }
    return result;
}

void Battlefield::fill(QVector<Cell> combattlefield)
{
        battlefield = combattlefield;
}

End Battlefield::checkEnd()
{
    for (int i=0; i<fieldSize*fieldSize;i++)
    {
        if (battlefield[i] == Ship)
            return Not;
    }
    return Win;
}

bool Battlefield::correct()
{
    for (int i=0; i<4;i++)
        ships[i] = 0;
    for (int j=0; j<fieldSize;j++)
    {
        for (int i=0; i<fieldSize;i++)
        {
            if (battlefield[i+j*fieldSize] == Ship)
            {
                QPoint pos;
                pos.setX(i);
                pos.setY(j);
                battlefield[i+j*fieldSize] = Hit;
                if (monoShip(pos, true).x() != -1)
                {
                    pos = monoShip(pos, true);
                    battlefield[pos.x()+pos.y()*fieldSize] = Hit;
                    if (monoShip(pos, true).x() != -1)
                    {
                        pos = monoShip(pos, true);
                        battlefield[pos.x()+pos.y()*fieldSize] = Hit;
                        if (monoShip(pos, true).x() != -1)
                        {
                            pos = monoShip(pos, true);
                            battlefield[pos.x()+pos.y()*fieldSize] = Hit;
                            if (monoShip(pos, true).x() != -1)
                            {
                                ships[0] = 3;
                            }
                            else
                                ships[0] = ships[0]+1;
                        }
                        else
                            ships[3] = ships[3]+1;
                    }
                    else
                        ships[2] = ships[2]+1;
                }
                else
                    ships[1] = ships[1]+1;
            }
        }
    }
    for (int i=0; i<fieldSize*fieldSize;i++)
    {
        if (battlefield[i] == Hit)
            battlefield[i] = Ship;
    }
    switch(fieldSize)
    {
        case 8:
            if (ships[1]==3 && ships[2]==2 && ships[3]==1 && ships[0]==0)
                return true;
        break;
        case 10:
            if (ships[1]==4 && ships[2]==3 && ships[3]==2 && ships[0]==1)
                return true;
        break;
        case 12:
            if (ships[1]==5 && ships[2]==4 && ships[3]==3 && ships[0]==1)
                return true;
        break;
    }
    return false;
}

QPoint Battlefield::monoShip(QPoint pos, bool direction)
{
    int x = pos.x();
    int y = pos.y();
    if (direction)
    {
        if (check(x+1,y) == Ship or check(x+1,y) == Hit)
        {
            pos.setX(x+1);
            return pos;
        }
        if (check(x,y+1) == Ship or check(x,y+1) == Hit)
        {
            pos.setY(y+1);
            return pos;
        }
    }
    else
    {
        if (check(x,y-1) == Ship or check(x,y-1) == Hit)
        {
            pos.setY(y-1);
            return pos;
        }
        if (check(x-1,y) == Ship or check(x-1,y) == Hit)
        {
            pos.setX(x-1);
            return pos;
        }
    }
    pos.setX(-1);
    pos.setY(-1);
    return pos;
}

statusShip Battlefield::status(QPoint pos)
{
    struct statusShip stat;
    stat.num = 0;
    stat.alive = false;
    if (check(pos.x(),pos.y()) == Ship or check(pos.x(),pos.y()) == Hit)
    {
        while (monoShip(pos, false).x() != -1)
        {
            pos = monoShip(pos, false);
        }
        while (pos.x() != -1)
        {
            if (battlefield[pos.x()+pos.y()*fieldSize] == Ship)
                stat.alive = true;
            stat.num = stat.num + 1;
            pos = monoShip(pos, true);
        }
    }
    return stat;
}

ShotField Battlefield::doshot(int x, int y)
{
    ShotField result;
    result.shot = false;
    result.hit = false;
    QPoint Coord;
    Coord.setX(x);
    Coord.setY(y);
    int num = Coord.x()+Coord.y()*fieldSize;
    if (x>=0 && y>=0 && x<fieldSize & y<fieldSize)
    {
        switch(battlefield[num])
        {
            case Empty:
                result.shot = true;
                qDebug() <<"stat" << status(Coord).num << status(Coord).alive;
            break;
            case Ship:
                result.shot = true;
                result.hit = true;
            break;
            case Hit:
                result.hit = true;
            default:
                return result;
            break;
        }
        return result;
    }
    return result;
}
