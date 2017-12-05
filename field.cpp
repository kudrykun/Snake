#include "field.h"
#include <QDebug>
Field::Field(int w, int h)
{
    // 0 for empty space, 1 for food, 2 for snake cells
    field = new QVector<QVector<int>>(h, QVector<int>(w));



    //populating field with empty space
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++){
            (*field)[i][j] = 0;
        }

    //place first food cell randomly
    int food_x = qrand() % w;
    int food_y = qrand() % h;
    (*field)[food_y][food_x] = 1;

    //place snake
    snake = new QVector<QPair<int,int>>();
    snake->push_back(qMakePair(5,5));
    snake->push_back(qMakePair(5,6));
    snake->push_back(qMakePair(5,7));
    qDebug() << (*snake)[0];
    (*field)[(*snake)[0].second][(*snake)[0].first] = 2;
    (*field)[(*snake)[1].second][(*snake)[1].first] = 2;
    (*field)[(*snake)[2].second][(*snake)[2].first] = 2;
}

int Field::get_item(int x, int y)
{
    return (*field)[y][x];
}

/*void Field::set_item(int x, int y, int v)
{
    (*field)
}*/

int Field::get_w()
{
    return (*field)[0].size();
}

int Field::get_h()
{
    return (*field).size();
}

void Field::set_direction(int dir)
{
    direction = dir;
}

bool Field::move()
{

    // next head coordinates
    int next_x = (*snake)[0].first;
    int next_y = (*snake)[0].second;

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

    // checking for crossing borders
    if(next_x >= this->get_w() || next_y >= this->get_h() || next_x < 0 || next_y < 0){
        qDebug() << "BORDERS" << " x = " << next_x << " y = " << next_y;
        return false;
    }

    int next_value = this->get_item(next_x,next_y);

    //if next cell is snake's cell - game over
    if(next_value == 2){
        qDebug() << "CEll TWO" << " x = " << next_x << " y = " << next_y;;
        return false;
    }

    //if next cell is food - ok
    if(next_value == 1)
        score++;

    //updating field
    for(int i = snake->length()-1; i >= 0; i--){
        (*field)[(*snake)[i].second][(*snake)[i].first] = 0;
    }

    //moving snake
    for(int i = snake->length()-1; i >= 1; i--){
        (*snake)[i].first = (*snake)[i-1].first;
        (*snake)[i].second = (*snake)[i-1].second;
    }
    (*snake)[0].first = next_x;
    (*snake)[0].second = next_y;

    //updating field
    for(int i = snake->length()-1; i >= 0; i--){
        (*field)[(*snake)[i].second][(*snake)[i].first] = 2;
    }
    return true;
}
