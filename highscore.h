#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <Qt>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QtDebug>
#include <iostream>

using namespace std;

class Highscore
{
public:
    Highscore();
    bool insertScore(QString filename,int nScore,QString strUser);
};

#endif // HIGHSCORE_H
