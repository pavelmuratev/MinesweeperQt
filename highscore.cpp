#include "highscore.h"

Highscore::Highscore()
{

}
bool Highscore::insertScore(QString filename,int nScore,QString strUser)
{
    QFile file(filename);

    QTextStream stream(&file);
    if( file.open(QIODevice::Append | QIODevice::Text))
    {
        stream << nScore << " " << strUser;
        stream << endl;
    }
    else
        return false;

    file.close();
    return true;
}
