#include "controller.h"

Controller::Controller(Battlefield *field, Battlefield *Enemyfield)
{
    battlefield = field;
    Enemybattlefield = Enemyfield;
    turncom = false;
}

Controller::~Controller()
{
    delete battlefield;
}

void Controller::doTurn(int x, int y)
{
    ShotField result;
    result = Enemybattlefield->shot(x,y);
    emit drawWin();
    if (result.shot)
    {
        computer = new Computer(10);
        Enemybattlefield->update(true);
        turncom = true;
        if (result.hit)
            turncom = false;
        while (turncom)
        {
            QPoint pos = computer->attack(battlefield);
            if (!(battlefield->shot(pos.x()*32+50,pos.y()*32+52).hit))
                turncom = false;
            battlefield->update(false);
        }
        emit drawWin();
}
}
