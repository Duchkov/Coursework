#include "mainwindow.h"
#include "battlewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    BattleWindow b;
    b.show();

    return a.exec();
}
