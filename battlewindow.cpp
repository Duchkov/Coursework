#include "battlewindow.h"
#include "ui_battlewindow.h"

BattleWindow::BattleWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BattleWindow)
{
    ui->setupUi(this);
    images = new Images;
    battlefield = new Battlefield(images,422,422);
    Enemybattlefield = new Battlefield(images,422,422);

    battlefield->update(true);
    Enemybattlefield->update(false);

    status = Placement;
    pause = false;
}

BattleWindow::~BattleWindow()
{
    delete images;
    delete ui;
}

void BattleWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0,0,images->get("background"));
    painter.drawImage(50,50,battlefield->get());
    if (status == Placement)
    {
        painter.drawImage(550,50,images->get("enemy"));
        painter.drawImage(400,500,images->get("start"));
    }
    else
    {
        painter.drawImage(550,50,Enemybattlefield->get());
        if (Enemybattlefield->checkEnd() == Win)
        {
            painter.drawImage(350,120,images->get("win").scaled(300,300,Qt::KeepAspectRatio));
            pause = true;
        }
        if (battlefield->checkEnd() == Win)
        {
            painter.drawImage(350,120,images->get("lose").scaled(300,300,Qt::KeepAspectRatio));
            pause = true;
        }
    }
}

void BattleWindow::mousePressEvent(QMouseEvent * event)
{
    if (pause == true)
    {
        return;
    }
    else
    {
        pause = true;
        QPoint position = event->pos();
        if(status == Placement)
        {
            if (position.x()>400 && position.y()>500 && position.x()<700 && position.y()<570)
            {
                if (battlefield->correct())
                {
                    status = Battle;
                    computer = new Computer;
                    Enemybattlefield->fill(computer->create());
                    Enemybattlefield->update(true);
                    this->update();
                    pause = false;
                    return;
                }
            }
            battlefield->set(position.x()-50,position.y()-50,Ship);
            battlefield->update(false);
            this->update();
        }
        else
        {
            if (Enemybattlefield->shot(position.x()-550,position.y()-50))
            {
                Enemybattlefield->update(true);
                this->update();
                //QThread::msleep(1000);
                QPoint pos = computer->attack(battlefield);
                battlefield->shot(pos.x()*32+50,pos.y()*32+52);
                battlefield->update(false);
                this->update();
            }
        }
        pause = false;
    }
}
