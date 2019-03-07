#include "game.h"
#include "square.h"
#include<mainwindow.h>
#include<ui_mainwindow.h>
#include <QFile>
game::game(MainWindow* mw)
{
    this->mw = mw;
}
game::game(){}
game::~game(){}

game::game(const game* gg)
{
   this->mw = gg->mw;
}

void game::setAddress(square* sq,int x, int y)
{
    this->gridAddress[x][y] = sq;
}

void game::plantBombs(int x, int y)
{
    for(int i=0;i<32;i++)
        for(int ii=0;ii<32;ii++)
            gridAddress[i][ii]->setStatus("hidden");
    srand(time(NULL));
    int bombNum = rand()%128+128;
    for(int i = 0;i<bombNum;i++)
    {
        int xc = rand()%32;
        int yc = rand()%32;
        if(xc==x&&yc==y)
        {
            i--;
            continue;
        }
        gridAddress[xc][yc]->bombIt();
        //gridAddress[xc][yc]->setStyleSheet("background-color:red"); //this was used for debugging purposes.
    }

    for(int i = 0;i<32;i++)
    {
        for(int ii = 0;ii<32;ii++)
        {
           gridAddress[i][ii]->snab();
        }
    }
    mw->timer.start(1000);
}

void game::lose()
{
    for(int i = 0;i<32;i++)
        for(int ii=0;ii<32;ii++){
           if(gridAddress[i][ii]->isBomb()==true)
               gridAddress[i][ii]->revBombLose();
           else gridAddress[i][ii]->setDisabled(true);
        }
    mw->timer.stop();
}

bool game::checkWin()
{
    for(int i = 0;i<32;i++)
        for(int ii=0;ii<32;ii++){
            if(gridAddress[i][ii]->isBomb()==true&&!gridAddress[i][ii]->flagged())

                return false;
        }
    return true;
}

void game::win()
{
    Highscore score;
    QString userName = mw->getUsername();
    for(int i = 0;i<32;i++)
        for(int ii=0;ii<32;ii++){
            gridAddress[i][ii]->setDisabled(true);
        }

    int nSeconds = mw->seconds;
    score.insertScore("D:\\project\\score.txt",nSeconds,userName);
    qDebug()<<"gg";

    mw->timer.stop();

}
