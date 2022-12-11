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
#include "controller.h"
#include <QTimer>
#include <QTime>

namespace Ui {
class BattleWindow;
}

enum Status
{
    Placement,
    Battle
};

class BattleWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BattleWindow(int field, QWidget *parent = 0);
    ~BattleWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void endBattle();

private slots:
    void drawWindow_Slot();
    void slotTimerAlarm();

private:
    Ui::BattleWindow *ui;
    Images *images;
    Battlefield *battlefield, *Enemybattlefield;
    Status status;
    Computer *computer;
    bool pause;
    bool turncom;
    bool tryStart;
    Controller *controll;
    QTimer *timer;
    int fieldSize, width, height;
};

#endif // BATTLEWINDOW_H
