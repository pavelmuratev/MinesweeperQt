#ifndef SQUARE_H
#define SQUARE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
//#include <game.h>
#include <QString>
#include <QVector>
#include <bfs.h>
class game;
class square : public QPushButton
{
    Q_OBJECT
public:
    square();
    square(QWidget* parent, game* g,int x,int y);
    ~square();
    void setStatus(QString status);
    void bombIt();
    bool isBomb();
    void snab(); //set neighbours and bomb counts;
    void revBombLose();
    bool flagged();

public slots:
    void mousePressEvent(QMouseEvent *event);
signals:

private:
   int x;
   int y;
   int bombsNear;
   QString status;
   bool bomb;
   game* g;
   QVector<square*> neighbours;
   //QVector<square*> zneighbours;
   void handleStatus(QString status);
   friend class bfs;
};

#endif // SQUARE_H
