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
        qDebug() << "BORDER COLLISION at" << " x = " << next_x << " y = " << next_y;
        return false;
    }

    int next_value = this->get_cell(next_x,next_y);

    //if next cell is snake's cell - game over
    if(next_value == 2){
        qDebug() << "SELF COLLISION at" << " x = " << next_x << " y = " << next_y;;
        return false;
    }



    //updating field
    snake->move(next_direction);

    //if next cell is food - ok
    if(next_value == 1){
        score++;
        increase_snake();
        add_food();
    }
    //moving snake
    render_snake(snake);
    return true;
}

void Field::render_snake(Snake *s)
{
    qDebug() << "... START SNAKE RENDERING";
    QString str = "";
    for(int i = 0; i < s->length(); i++)
        str.append("[" + QString::number(s->get_cell(i).first) + ", " + QString::number(s->get_cell(i).second) + "] ");
    qDebug() << "... SNAKE COORDS " << str;
    for(int i = 0; i < get_h(); i++)
        for(int j = 0; j < get_w(); j++)
            if(get_cell(i,j) == 2)
                set_cell(i,j,0);

    for(int i = 0; i < s->length(); i++)
        set_cell(s->get_cell(i).first,s->get_cell(i).second,2);
    qDebug() << "OK SNAKE RENDERED";
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

int Field::get_score()
{
    return score;
}

void Field::increase_snake()
{
    QPair<int,int> t1 = snake->get_cell(snake->length()-1);
    QPair<int,int> t2 = snake->get_cell(snake->length()-2);
    int nx = t1.first;
    int ny = t1.second;

    // now lets coords of added cell if cell behind current tail if empty
    if(t1.first - t2.first == 0){
        //direction - up
        if(t1.second - t2.second == 1)
            ny++;
        //direction - down
        else
            ny--;
    }
    else{
        //direction - right
        if(t1.first - t2.first == -1)
            nx--;
        //direction - left
        else
            nx++;
    }

    // NOT WORKING PROPERLY
    if(!is_valid(nx,ny)){
        if(is_valid(t1.first-1,t1.second)){
            nx = t1.first-1;
            ny = t1.second;
        }
        if(is_valid(t1.first,t1.second-1)){
            nx = t1.first;
            ny = t1.second-1;
        }
        if(is_valid(t1.first+1,t1.second)) {
            nx = t1.first+1;
            ny = t1.second;
        }
        if(is_valid(t1.first,t1.second+1)){
            nx = t1.first;
            ny = t1.second+1;
        }
    }


    snake->add_cell(nx,ny);
}

bool Field::is_valid(int x, int y)
{
    if(x < 0 || y < 0 || x >= get_w() || y >= get_h())
        return false;

    int v = get_cell(x,y);
    if(v == 2)
        return false;
    return true;
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
    if(qAbs(next_direction - dir) != 2)
        next_direction = dir;
}


