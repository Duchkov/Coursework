#include "battlefield.h"

Battlefield::Battlefield(Images *images,int width, int height):
    images(images), width(width), height(height)
{
    battlefield.fill(Empty,100);
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
    int i = (x-50-50)/32;
    int j = (y-50-52)/32;
    int num = i+j*10;
    if (num>=0 && num<battlefield.size())
    {
        if (battlefield[num] == Empty)
        {
            battlefield[num] = cell;
        }else
        {
            battlefield[num] = Empty;
        }
    }
}
