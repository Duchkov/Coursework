#include "battlefield.h"

Battlefield::Battlefield(Images *images):images(images)
{
    battlefield.fill(Empty,100);
    image = new QImage(500,500,QImage::Format_ARGB32);
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
}

const QImage& Battlefield::get() const
{
    return *image;
}
