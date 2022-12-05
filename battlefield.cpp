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

void Battlefield::update(bool enemy)
{
    image->fill(0);
    QPainter painter(image);
    painter.drawImage(0,0,images->get("field"));
    for (int i=0; i<10; i++)
         for (int j=0; j<10; j++)
             if (enemy)
             {
                 switch(battlefield[i+10*j])
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
                 switch(battlefield[i+10*j])
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
    int x = xx-50;
    int y = yy-52;
    //qDebug() << "Ship" << x << y;
    if ((x>=0)&& (y>=0) && (x<=320) && (y<=320))
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

bool Battlefield::shot(int x, int y)
{
    //qDebug() << "Ship" << x+50 << y+50;
    QPoint Coord = getCoordinates(x, y);
    //qDebug() << "Ship" << Coord.x() << Coord.y();
    int num = Coord.x()+Coord.y()*10;
    if (Coord.x() != -1)
    {
        qDebug() <<"ff" << status(Coord).num << status(Coord).alive;
        switch(battlefield[num])
        {
            case Empty:
                battlefield[num] = Shot;
            break;
            case Ship:
                if (true)
                {
                    battlefield[num] = Hit;
                }
                else
                {
                    battlefield[num] = Hit;
                    x = Coord.x();
                    y = Coord.y();
                    if (x+1<10 && y+1<10)
                        battlefield[num+11] = Shot;
                    if (x-1>=0 && y-1>=0)
                        battlefield[num-11] = Shot;
                    if (y-1>=0 && x+1<10)
                        battlefield[num-9] = Shot;
                    if (x-1>=0 && y+1<10)
                        battlefield[num+9] = Shot;
                    if (y+1<10)
                        battlefield[num+10] = Shot;
                    if (y-1>=0)
                        battlefield[num-10] = Shot;
                    if (x-1>=0)
                        battlefield[num-1] = Shot;
                    if (x+1<10)
                        battlefield[num+1] = Shot;
                }
            break;
            default:
                return false;
            break;
        }
        return true;
    }
    return false;
}

void Battlefield::fill(QVector<Cell> combattlefield)
{
        battlefield = combattlefield;
}

End Battlefield::checkEnd()
{
    for (int i=0; i<100;i++)
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
    for (int j=0; j<10;j++)
    {
        for (int i=0; i<10;i++)
        {
            if (battlefield[i+j*10] == Ship)
            {
                QPoint pos;
                pos.setX(i);
                pos.setY(j);
                battlefield[i+j*10] = Hit;
                if (monoShip(pos).x() != -1)
                {
                    pos = monoShip(pos);
                    battlefield[pos.x()+pos.y()*10] = Hit;
                    if (monoShip(pos).x() != -1)
                    {
                        pos = monoShip(pos);
                        battlefield[pos.x()+pos.y()*10] = Hit;
                        if (monoShip(pos).x() != -1)
                        {
                            pos = monoShip(pos);
                            battlefield[pos.x()+pos.y()*10] = Hit;
                            if (monoShip(pos).x() != -1)
                            {
                                ships[0] = 2;
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
    for (int i=0; i<100;i++)
    {
        if (battlefield[i] == Hit)
            battlefield[i] = Ship;
    }
    if (ships[1]==4 && ships[2]==3 && ships[3]==2 && ships[0]==1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

QPoint Battlefield::monoShip(QPoint pos)
{
    int x = pos.x();
    int y = pos.y();
    if (check(x,y-1) == Ship)
    {
        pos.setY(y-1);
        return pos;
    }
    if (check(x+1,y) == Ship)
    {
        pos.setX(x+1);
        return pos;
    }
    if (check(x,y+1) == Ship)
    {
        pos.setY(y+1);
        return pos;
    }
    if (check(x-1,y) == Ship)
    {
        pos.setX(x-1);
        return pos;
    }
    pos.setX(-1);
    pos.setY(-1);
    return pos;
}

statusShip Battlefield::status(QPoint pos)
{
    int x = pos.x();
    int y = pos.y();
    struct statusShip stat;
    stat.num = 0;
    stat.alive = false;
    if (battlefield[x+y*10] == Ship or battlefield[x+y*10] == Hit)
    {
        if (battlefield[x+y*10] == Ship)
            stat.alive = true;
        if (monoShip(pos).x() != -1)
        {
            pos = monoShip(pos);
            if (monoShip(pos).x() != -1)
            {
                pos = monoShip(pos);
                if (monoShip(pos).x() != -1)
                {
                    pos = monoShip(pos);
                    if (monoShip(pos).x() != -1)
                    {
                        stat.num = 5;
                        return stat;
                    }
                    else
                        stat.num = 4;
                        return stat;
                }
                else
                    stat.num = 3;
                    return stat;
            }
            else
                stat.num = 2;
                return stat;
        }
        else
            stat.num = 1;
            return stat;
    }
    return stat;
}
