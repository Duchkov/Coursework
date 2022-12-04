#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Images.h"
#include <QImage>
#include <QPainter>
#include "battlefield.h"
#include <QPoint>
#include <QMouseEvent>
#include <QtWidgets>
#include "computer.h"

namespace Ui {
class MainWindow;
}

enum Status
{
    Placement,
    Battle
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    Images *images;
    Battlefield *battlefield, *Enemybattlefield;
    Status status;
    Computer *computer;
};

#endif // MAINWINDOW_H
