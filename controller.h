#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include "battlefield.h"
#include "computer.h"
#include <QtWidgets>
#include <QWidget>

class Controller : public QWidget
{
    Q_OBJECT

public:
    Controller(Battlefield *field, Battlefield *Enemyfield);
    ~Controller();
    void doTurn(int x, int y);

signals:
    void drawWin();

private:
    Battlefield *battlefield, *Enemybattlefield;
    bool turncom;
    Computer *computer;
};

#endif // CONTROLLER_H
