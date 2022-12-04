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

namespace Ui {
class MainWindow;
}

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
    Battlefield *battlefield;
};

#endif // MAINWINDOW_H
