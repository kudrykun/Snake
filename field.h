#ifndef FIELD_H
#define FIELD_H

#include "snake.h"

#include <QObject>
#include <QVector>
#include <QPair>

class Field
{
public:
    Field(int w = 10, int h = 10);
    int get_cell(int x, int y);
    void set_cell(int x, int y, int v);
    int get_w();
    int get_h();
    void set_next_direction(int dir);
    bool update();
    void render_snake(Snake *s);
    void add_food(int count = 1);
private:
    QVector<QVector<int>> *field;
    int next_direction = 0;// 0 for up, 1 for right, 2 for down, 3 for left
    int score = 0;
    Snake *snake;
};

#endif // FIELD_H
