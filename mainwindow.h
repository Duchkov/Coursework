#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include "battlefield.h"
#include <QPoint>
#include <QMouseEvent>
#include <QtWidgets>
#include "computer.h"
#include "battlewindow.h"

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

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void endBattle_Slot();

    void on_pushButton_eight_clicked();

    void on_pushButton_ten_clicked();

    void on_pushButton_twelve_clicked();

    void on_pushButton_size_clicked();

private:
    Ui::MainWindow *ui;
    Battlefield *battlefield, *Enemybattlefield;
    Status status;
    Computer *computer;
    bool pause;
    BattleWindow *window;
    int fieldSize;
};

#endif // MAINWINDOW_H
