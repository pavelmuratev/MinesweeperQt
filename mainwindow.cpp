#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QResizeEvent>
#include <square.h>
#include <QObject>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->textEdit->setGeometry(1,1,100,50);

    seconds = 0;
    QObject::connect(&timer,&QTimer::timeout, this,&MainWindow::updateTime);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
    seconds++;
    ui->lcdNumber->display(QString::number(seconds));
}

void MainWindow::on_startButton_released()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->setGeometry(this->x(),this->y(),640,700);
    g = game(this);
    for(int i = 0;i<32;i++)
    {
        for(int ii = 0;ii<32;ii++)
        {
            square* fr = new square(ui->page_2, &g,i,ii);
            fr->setMinimumWidth(18);
            fr->setMinimumHeight(18);
            fr->setMaximumWidth(18);
            fr->setMaximumHeight(18);
            fr->setStyleSheet("background-color:#cccccc");
            ui->gridLayout->addWidget(fr,i,ii);
            g.setAddress(fr,i,ii);
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if(ui->stackedWidget->currentIndex()==1)
    {
        if(event->size().height()>event->size().width())
            this->resize(event->size().height(),event->size().height());
        else if(event->size().width()>event->size().height())
            this->resize(event->size().width(),event->size().width());
    }
}

void MainWindow::on_mainMenuButton_released()
{
    ui->stackedWidget->setCurrentIndex(0);
    seconds = 0;
    timer.stop();
    ui->lcdNumber->display(QString::number(seconds));
}

QString MainWindow::getUsername()
{
    return strUsername;
}
void MainWindow::on_textEdit_textChanged()
{
    strUsername = ui->textEdit->toPlainText();
    qDebug() << strUsername;

}
