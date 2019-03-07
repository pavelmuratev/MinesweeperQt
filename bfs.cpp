#include "bfs.h"
#include<square.h>
#include <QVector>
bfs::bfs(square* start)
{
    this->q.enqueue(start);
    this->visited.append(start);
    traverse();
}

void bfs::traverse()
{
    while(!q.isEmpty())
    {
        square* curr = q.dequeue();
        for(int i = 0; i<curr->neighbours.length();i++){
            if(visited.indexOf(curr->neighbours[i])==-1){
                if(curr->neighbours[i]->bombsNear==0){
                    q.enqueue(curr->neighbours[i]);
                    visited.append(curr->neighbours[i]);
                    if(curr->neighbours[i]->flagged())continue;
                    curr->neighbours[i]->setStatus("revealed");

                }
            }
        }
        if(curr->bombsNear==0){
            for(int i =0;i<curr->neighbours.length();i++){
                if(curr->neighbours[i]->bombsNear>0){
                        if(curr->neighbours[i]->flagged())continue;
                        curr->neighbours[i]->setStatus("revealed");
                }
            }
        }
    }
}
