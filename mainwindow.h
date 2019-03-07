#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <game.h>
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resizeEvent(QResizeEvent *evt);
    QString getUsername();

private slots:
    void on_startButton_released();

    void on_mainMenuButton_released();

    void updateTime();


    void on_textEdit_textChanged();
private:
    Ui::MainWindow *ui;
    game g;
    QTimer timer;
    int seconds;
    QString strUsername;

    friend class game;
};

#endif // MAINWINDOW_H
