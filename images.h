#ifndef IMAGES_H
#define IMAGES_H
#include <QImage>
#include <QMap>
#include <QString>

class Images
{
public:
    Images();
    QImage& get(const QString& name);

private:
    QMap<QString,QImage> images;
};

#endif // IMAGES_H
