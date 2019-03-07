#ifndef BFS_H
#define BFS_H
#include<QQueue>
#include<QDebug>

class square;
class bfs
{
public:
    bfs(square* start);
    void traverse();
private:
    QQueue<square*> q;
    QVector<square*> visited;
};

#endif // BFS_H
