#ifndef BATTLEWINDOW_H
#define BATTLEWINDOW_H

#include <QWidget>
#include "Images.h"
#include <QImage>
#include <QPainter>
#include "battlefield.h"
#include <QPoint>
#include <QMouseEvent>
#include <QtWidgets>
#include "computer.h"

namespace Ui {
class BattleWindow;
}

enum Status
{
    Placement,
    Battle,
};

class BattleWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BattleWindow(QWidget *parent = 0);
    ~BattleWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::BattleWindow *ui;
    Images *images;
    Battlefield *battlefield, *Enemybattlefield;
    Status status;
    Computer *computer;
    bool pause;
};

#endif // BATTLEWINDOW_H
