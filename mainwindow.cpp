#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->close();
    ui->mainToolBar->close();
    ui->pushButton_eight->close();
    ui->pushButton_ten->close();
    ui->pushButton_twelve->close();
    fieldSize = 10;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPixmap bkgnd(":/Images/Images/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

void MainWindow::on_pushButton_clicked()
{
    window = new BattleWindow(fieldSize);
    window->show();
    connect(window, SIGNAL(endBattle()), this, SLOT(endBattle_Slot()));
    this->close();
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ui->pushButton_2->isCheckable())
    {
        ui->pushButton_2->setDown(0);
        ui->pushButton_2->setCheckable(0);
        ui->textBrowser->close();
    }
    else
    {
        ui->pushButton_2->setCheckable(1);
        ui->pushButton_2->setDown(1);
        ui->textBrowser->show();

        ui->pushButton_size->setDown(0);
        ui->pushButton_size->setCheckable(0);
        ui->pushButton_eight->close();
        ui->pushButton_ten->close();
        ui->pushButton_twelve->close();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    this-close();
}


void MainWindow::endBattle_Slot()
{
    this->show();
}

void MainWindow::on_pushButton_eight_clicked()
{
    if (!(ui->pushButton_eight->isCheckable()))
    {
        fieldSize = 8;
        ui->pushButton_eight->setCheckable(1);
        ui->pushButton_eight->setDown(1);
        ui->pushButton_ten->setCheckable(0);
        ui->pushButton_ten->setDown(0);
        ui->pushButton_twelve->setCheckable(0);
        ui->pushButton_twelve->setDown(0);
        ui->pushButton_eight->setEnabled(0);
        ui->pushButton_ten->setEnabled(1);
        ui->pushButton_twelve->setEnabled(1);
    }
}

void MainWindow::on_pushButton_ten_clicked()
{
    if (!(ui->pushButton_ten->isCheckable()))
    {
        fieldSize = 10;
        ui->pushButton_eight->setCheckable(0);
        ui->pushButton_eight->setDown(0);
        ui->pushButton_ten->setCheckable(1);
        ui->pushButton_ten->setDown(1);
        ui->pushButton_twelve->setCheckable(0);
        ui->pushButton_twelve->setDown(0);
        ui->pushButton_eight->setEnabled(1);
        ui->pushButton_ten->setEnabled(0);
        ui->pushButton_twelve->setEnabled(1);
    }
}

void MainWindow::on_pushButton_twelve_clicked()
{
    if (!(ui->pushButton_twelve->isCheckable()))
    {
        fieldSize = 12;
        ui->pushButton_eight->setCheckable(0);
        ui->pushButton_eight->setDown(0);
        ui->pushButton_ten->setCheckable(0);
        ui->pushButton_ten->setDown(0);
        ui->pushButton_twelve->setCheckable(1);
        ui->pushButton_twelve->setDown(1);
        ui->pushButton_eight->setEnabled(1);
        ui->pushButton_ten->setEnabled(1);
        ui->pushButton_twelve->setEnabled(0);
    }
}

void MainWindow::on_pushButton_size_clicked()
{
    if (ui->pushButton_size->isCheckable())
    {
        ui->pushButton_size->setDown(0);
        ui->pushButton_size->setCheckable(0);
        ui->pushButton_eight->close();
        ui->pushButton_ten->close();
        ui->pushButton_twelve->close();
    }
    else
    {
        ui->pushButton_size->setCheckable(1);
        ui->pushButton_size->setDown(1);
        ui->pushButton_eight->show();
        ui->pushButton_ten->show();
        ui->pushButton_twelve->show();

        ui->pushButton_2->setDown(0);
        ui->pushButton_2->setCheckable(0);
        ui->textBrowser->close();
    }
}
