#ifndef GAME_H
#define GAME_H
#include <QString>
#include <QMainWindow>
#include <QGridLayout>
#include <time.h>
#include <stdlib.h>
#include <QDebug>
#include <square.h>

#include "highscore.h"

class MainWindow;
class game
{
public:
    game(MainWindow* mw);
    game();
    ~game();
    void setAddress(square* sq,int x, int y);
    game(const game* gg);

private:
    square* gridAddress[32][32];
    MainWindow* mw;
    void lose();
    bool checkWin();
    void plantBombs(int x, int y);
    void win();
    friend class square;
};

#endif // GAME_H
