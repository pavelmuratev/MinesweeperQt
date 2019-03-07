#include "square.h"
#include <QDebug>
#include <game.h>
#include <QIcon>
#include <QQueue>
square::square(){}
square::square(QWidget* parent, game* g,int x, int y):QPushButton (parent)
{
    this->g = g;
    this->bomb = false;
    this->bombsNear = 0;
    this->x = x;
    this->y = y;
    this->setStatus("prestart");
}

square::~square()
{

}

bool square::isBomb()
{
    if(bomb)return true;
    else return false;
}

bool square::flagged()
{
    if(this->status=="flagged")return true;
    else return false;
}

void square::mousePressEvent(QMouseEvent *event)
{
    if(this->status=="revealed")return;
    if(this->status=="prestart"){
        g->plantBombs(this->x,this->y);
        this->setStatus("revealed");
    }
    if(event->button()==Qt::RightButton)
    {
        if(this->status=="flagged"){
            this->setStatus("hidden");
        }
        else {
            this->setStatus("flagged");
        }
    }
    else if(event->button()==Qt::LeftButton)
    {
        if(this->status == "flagged"){
            setStatus("hidden");
        }
        else {
            bfs bigreveal(this);
            this->setStatus("revealed");
        }
    }
}

void square::setStatus(QString status)
{
    this->status = status;
    handleStatus(status);
}

void square::handleStatus(QString status)
{
    if(status == "hidden"){
        setText("");
        setStyleSheet("background-color:#cccccc");
        setIcon(QIcon());
    }
    else if(status == "revealed"){
        setIcon(QIcon());
        if(bomb==true){
            qDebug()<<"boom";
            g->lose();
        }
        else {
            switch (bombsNear) {
            case 1:
                setText("1");
                setStyleSheet("font-weight:bold; "
                              "color: #0000ff;"
                              "background-color:#eeeeee;");
                break;
            case 2:
                setText("2");
                setStyleSheet("font-weight:bold; "
                              "color:  #558000;"
                              "background-color:#eeeeee;");
                break;
            case 3:
                setText("3");
                setStyleSheet("font-weight:bold; "
                              "color:  #ff0000;"
                              "background-color:#eeeeee;");
                break;
            case 4:
                setText("4");
                setStyleSheet("font-weight:bold; "
                              "color:  #0000b3;"
                              "background-color:#eeeeee;");
                break;
            case 5:
                setText("5");
                setStyleSheet("font-weight:bold; "
                              "color:  #990000;"
                              "background-color:#eeeeee;");
                break;
            case 6:
                setText("6");
                setStyleSheet("font-weight:bold; "
                              "color:  #66b3ff;"
                              "background-color:#eeeeee;");
                break;
            case 7:
                setText("7");
                setStyleSheet("font-weight:bold; "
                              "color:  #000000;"
                              "background-color:#eeeeee;");
                break;
            case 8:
                setText("8");
                setStyleSheet("font-weight:bold; "
                              "color:  #ff1ab3;"
                              "background-color:#eeeeee;");
                break;
             case 0:
                setText("");
                setStyleSheet("background-color:#eeeeee;");
                break;
            default:
                setText("");
                setStyleSheet("background-color:#eeeeee;");
                break;
            }
        }
    }
    else if(status == "flagged"){
        setText("");
        setStyleSheet("background-color:#cccccc;");
        QIcon c(":/new/prefix1/flag.png");
        setIcon(c);
        if(g->checkWin())g->win();
    }
}
void square::bombIt()
{
    this->bomb = true;
}

void square::snab()
{
    if(x-1>=0){
        if(g->gridAddress[x-1][y]->bomb==true)bombsNear++;
        else neighbours.append(g->gridAddress[x-1][y]);
    }
    if(y-1>=0){
        if(g->gridAddress[x][y-1]->bomb==true)bombsNear++;
        else neighbours.append(g->gridAddress[x][y-1]);
     }
    if(x-1>=0 && y-1>=0){
        if(g->gridAddress[x-1][y-1]->bomb==true)bombsNear++;
        else {
            neighbours.append(g->gridAddress[x-1][y-1]);
            //zneighbours.append(g->gridAddress[x-1][y-1]);
        }
     }
    if(x+1<=31){
        if(g->gridAddress[x+1][y]->bomb==true)bombsNear++;
        else neighbours.append(g->gridAddress[x+1][y]);
    }
    if(y+1<=31){
        if(g->gridAddress[x][y+1]->bomb==true)bombsNear++;
        else neighbours.append(g->gridAddress[x][y+1]);
    }
    if(x+1<=31&&y+1<=31){
        if(g->gridAddress[x+1][y+1]->bomb==true)bombsNear++;
        else {
            //zneighbours.append(g->gridAddress[x+1][y+1]);
            neighbours.append(g->gridAddress[x+1][y+1]);
        }
    }
    if(x+1<=31&&y-1>=0){
        if(g->gridAddress[x+1][y-1]->bomb==true)bombsNear++;
        else {
            //zneighbours.append(g->gridAddress[x+1][y-1]);
            neighbours.append(g->gridAddress[x+1][y-1]);
        }
    }
    if(x-1>=0&&y+1<=31){
        if(g->gridAddress[x-1][y+1]->bomb==true)bombsNear++;
        else {
            //zneighbours.append(g->gridAddress[x-1][y+1]);
            neighbours.append(g->gridAddress[x-1][y+1]);
        }
    }
   /* for(int i = 0;i<32;i++)
        for(int ii = 0;ii<32;ii++)
            for(int iii = 0;iii<g->gridAddress[i][ii]->neighbours.length();iii++)
            {
                if(g->gridAddress[i][ii]->neighbours[iii]->bombsNear==0){
                    g->gridAddress[i][ii]->zneighbours.append(
                                g->gridAddress[i][ii]->neighbours[iii]);
                    g->gridAddress[i][ii]->neighbours.removeAt(iii);
                }
            }*/
}

void square::revBombLose()
{
    this->status = "revealed";
    this->setIcon(QIcon(":/new/prefix1/bomb.jpg"));
}

