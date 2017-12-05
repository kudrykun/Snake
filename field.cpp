#include "field.h"
#include <QDebug>
Field::Field(int w, int h)
{
    // 0 for empty space, 1 for food, 2 for snake cells
    field = new QVector<QVector<int>>(h, QVector<int>(w));
    snake = new Snake(w/2,h/2);


    //populating field with empty space
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++){
            set_cell(i,j,0);
        }

    add_food();

    //place snake
    render_snake(snake);
}

bool Field::update()
{

    // next head coordinates
    int next_x = snake->get_head().first;
    int next_y = snake->get_head().second;

    //define this coordinates
    switch(next_direction){
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

    int next_value = this->get_cell(next_x,next_y);

    //if next cell is snake's cell - game over
    if(next_value == 2){
        qDebug() << "CEll TWO" << " x = " << next_x << " y = " << next_y;;
        return false;
    }



    //updating field
    snake->move(next_direction);

    //if next cell is food - ok
    if(next_value == 1){
        score++;
        snake->add_cell();
        add_food();
    }
    //moving snake
    render_snake(snake);
    return true;
}

void Field::render_snake(Snake *s)
{
    for(int i = 0; i < get_h(); i++)
        for(int j = 0; j < get_w(); j++)
            if(get_cell(i,j) == 2)
                set_cell(i,j,0);

    for(int i = 0; i < s->length(); i++)
        set_cell(s->get_cell(i).first,s->get_cell(i).second,2);
}

void Field::add_food(int count)
{

    for(int i = 0; i < count; i++){
        int x = qrand() % get_w();
        int y = qrand() % get_h();
        while(get_cell(x,y) == 2 || get_cell(x,y) == 1){
            x = qrand() % get_w();
            y = qrand() % get_h();
        }
        this->set_cell(x,y,1);
        qDebug() << "OK FOOD ADDED";
    }

}


int Field::get_cell(int x, int y)
{
    return (*field)[y][x];
}

void Field::set_cell(int x, int y, int v)
{
    (*field)[y][x] = v;
}

int Field::get_w()
{
    return (*field)[0].size();
}

int Field::get_h()
{
    return (*field).size();
}

void Field::set_next_direction(int dir)
{
    next_direction = dir;
}


