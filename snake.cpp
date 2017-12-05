#include "snake.h"

#include <QVector>
#include <QPair>
#include <QDebug>

Snake::Snake(int hx, int hy, int length, int direction)
{
    snake = new QVector<QPair<int,int>>();

    //push head of snake
    snake->push_back(qMakePair(hx,hy));

    //now determine how to build snake based on direction
    int dx = 0;
    int dy = 0;
    switch(direction){
    case 0:
        dy = 1;
        break;
    case 1:
        dx = 1;
        break;
    case 2:
        dy = -1;
        break;
    case 3:
        dx = -1;
        break;
    }

    //now build snake body
    for(int i = 0; i < length-1; i++){
        snake->push_back(qMakePair(hx+dx,hy+dy));
    }
}

void Snake::move(int direction)
{
    // next head coordinates
    int next_x = this->get_head().first;
    int next_y = this->get_head().second;

    //define this coordinates
    switch(direction){
    case 0:
        next_y--;
        break;
    case 1:
        next_x++;
        break;
    case 2:
        next_y++;
        break;
    case 3:
        next_x--;
        break;
    }

    for(int i = this->length()-1; i >= 1; i--)
        set_cell(get_cell(i-1),i);
    set_head(next_x,next_y);
}


QPair<int, int> Snake::get_cell(int n)
{
    return (*snake)[n];
}

QPair<int, int> Snake::get_head()
{
    return (*snake)[0];
}

void Snake::set_cell(int x, int y, int n)
{
    (*snake)[n].first = x;
    (*snake)[n].second = y;
}

void Snake::set_cell(QPair<int, int> c, int n)
{
    (*snake)[n].first = c.first;
    (*snake)[n].second = c.second;
}

void Snake::set_head(int x, int y)
{
    (*snake)[0].first = x;
    (*snake)[0].second = y;
}

int Snake::length()
{
    return (*snake).size();
}

void Snake::add_cell()
{
    QPair<int,int> t1 = get_cell(length()-1);
    QPair<int,int> t2 = get_cell(length()-2);

    // now lets define how we will add new cell to our snake
    if(t1.first - t2.first == 0){
        //direction - up
        if(t1.second - t2.second == 1)
            snake->push_back(qMakePair(t1.first, t1.second+1));
        //direction - down
        else
            snake->push_back(qMakePair(t1.first, t1.second-1));
    }
    else{
        //direction - right
        if(t1.first - t2.first == -1)
            snake->push_back(qMakePair(t1.first-1, t1.second));
        //direction - left
        else
            snake->push_back(qMakePair(t1.first+1, t1.second));
    }
    qDebug() << "OK CELL ADDED";
}
