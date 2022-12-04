#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    images = new Images;
    battlefield = new Battlefield(images,422,422);

    battlefield->update();
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
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
    QPoint position = event->pos();
    battlefield->set(position.x(),position.y(),Ship);
    battlefield->update();
    this->update();
}
