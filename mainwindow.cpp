#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    images = new Images;
    battlefield = new Battlefield(images,422,422);
    Enemybattlefield = new Battlefield(images,422,422);

    battlefield->update(true);
    Enemybattlefield->update(false);

    status = Placement;
}

MainWindow::~MainWindow()
{
    delete images;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0,0,images->get("background"));
    painter.drawImage(50,50,battlefield->get());
    painter.setPen(QColor(255, 0, 0, 255));
    painter.drawText(200,40,"Отсутствуют корабли");
    if (status == Placement)
    {
        painter.drawImage(550,50,images->get("enemy"));
        painter.drawImage(400,500,images->get("start"));
    }
    else
        painter.drawImage(550,50,Enemybattlefield->get());
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
    if(status == Placement)
    {
        QPoint position = event->pos();
        if (position.x()>400 && position.y()>500 && position.x()<700 && position.y()<570)
        {
            status = Battle;
            computer = new Computer;
            Enemybattlefield->fill(computer->create());
            Enemybattlefield->update(true);
            this->update();
            return;
        }
        battlefield->set(position.x()-50,position.y()-50,Ship);
        battlefield->update(false);
        this->update();
    }
    else
    {
        QPoint position = event->pos();
        Enemybattlefield->shot(position.x()-550,position.y()-50);
        Enemybattlefield->update(true);
        this->update();
    }
}
