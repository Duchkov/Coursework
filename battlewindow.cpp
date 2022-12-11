#include "battlewindow.h"
#include "ui_battlewindow.h"

BattleWindow::BattleWindow(int field, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BattleWindow)
{
    ui->setupUi(this);
    fieldSize = field;
    images = new Images(fieldSize);
    battlefield = new Battlefield(images,422,422, fieldSize);
    Enemybattlefield = new Battlefield(images,422,422, fieldSize);

    battlefield->update(true);
    Enemybattlefield->update(false);

    controll = new Controller(battlefield, Enemybattlefield);
    connect( controll, SIGNAL(drawWin()), this, SLOT(drawWindow_Slot()));

    status = Placement;
    pause = false;
    turncom = false;
    tryStart = false;

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    computer = new Computer(fieldSize);
    timer->start(300);
    switch(fieldSize)
    {
        case 8:
            width = 64;
            height = 64;
        break;
        case 10:
            width = 32;
            height = 32;
        break;
        case 12:
            width = 0;
            height = 0;
        break;
    }
}

BattleWindow::~BattleWindow()
{
    delete images;
    delete ui;
}

void BattleWindow::paintEvent(QPaintEvent *event)
{
    pause = true;
    QPainter painter(this);
    painter.setFont(QFont("Segoe Script", 20));
    painter.drawImage(0,0,images->get("background"));
    painter.drawImage(50+width,50+height,battlefield->get());
    painter.drawImage(840-width,550-height,images->get("menu"));
    if (status == Placement)
    {
        if (tryStart)
        {
            QPen pen(QColor("red"));
            painter.setPen(pen);
            painter.drawText(190, 35+height, "ПРОВЕРЬТЕ РАССТАНОВКУ КОРАБЛЕЙ");
        }
        painter.drawImage(550+width,50+height,images->get("enemy"));
        painter.drawImage(440,550-height,images->get("start"));
    }
    else
    {
        if (turncom)
        {
            QPen pen(QColor("black"));
            painter.setPen(pen);
            painter.drawText(400, 35+height, "ход компьютера");
        }
        painter.drawImage(550+width,50+height,Enemybattlefield->get());
        if (Enemybattlefield->checkEnd() == Win)
        {
            Enemybattlefield->update(false);
            painter.drawImage(550+width,50+height,Enemybattlefield->get());
            painter.drawImage(390,140,images->get("win").scaled(300,300,Qt::KeepAspectRatio));
            return;
        }
        if (battlefield->checkEnd() == Win)
        {
            Enemybattlefield->update(false);
            painter.drawImage(550+width,50+height,Enemybattlefield->get());
            painter.drawImage(390,140,images->get("lose").scaled(300,300,Qt::KeepAspectRatio));
            return;
        }
    }
    pause = false;
}

void BattleWindow::mousePressEvent(QMouseEvent * event)
{

    if (pause == true)
    {
        QPoint position = event->pos();
        if (position.x()>840-width && position.y()>550-height && position.x()<1030-width && position.y()<610-height)
        {
            emit endBattle();
            this->close();
        }
        return;
    }
    else
    {
        pause = true;
        QPoint position = event->pos();
        if (position.x()>840-width && position.y()>550-height && position.x()<1030-width && position.y()<610-height)
        {
            emit endBattle();
            this->close();
        }
        if(status == Placement)
        {
            tryStart = false;
            if (position.x()>440 && position.y()>550-height && position.x()<630 && position.y()<610-height)
            {
                if (battlefield->correct())
                {
                    status = Battle;
                    Enemybattlefield->fill(computer->create());
                    Enemybattlefield->update(true);
                    this->update();
                    pause = false;
                    return;
                }
                else
                {
                    tryStart = true;
                    this->update();
                    return;
                }
            }
            battlefield->set(position.x()-50-width,position.y()-50-height,Ship);
            battlefield->update(false);
            this->update();
        }
        else
        {
            //controll->doTurn(position.x()-550,position.y()-50);
            if (!(turncom))
            {
                ShotField result;
                result = Enemybattlefield->shot(position.x()-550-width,position.y()-50-height);
                if (result.shot)
                {
                    Enemybattlefield->update(true);
                    turncom = true;
                    if (result.hit)
                        turncom = false;
                }
                this->update();
            }

        }
        pause = false;
    }
}

void BattleWindow::drawWindow_Slot()
{
    this->update();
}

void BattleWindow::slotTimerAlarm()
{
    if (turncom && !pause)
    {
        pause = true;
        QThread::msleep(700);
        QPoint pos = computer->attack(battlefield);
        qDebug()<<"a"<<pos.x()<<pos.y();
        if (!(battlefield->shot(pos.x()*32+50,pos.y()*32+52).hit))
            turncom = false;
        battlefield->update(false);
        if (battlefield->checkEnd() == Win)
            turncom = false;
        pause = false;
        this->update();
    }
}


