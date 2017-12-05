#ifndef FIELD_H
#define FIELD_H

#include <QObject>
#include <QVector>
#include <QPair>

class Field
{
public:
    Field(int w = 10, int h = 10);
    int get_item(int x, int y);
    void set_item(int x, int y, int v);
    int get_w();
    int get_h();
    void set_direction(int dir);
    bool move();
private:
    QVector<QVector<int>> *field;
    int direction = 0;// 0 for up, 1 for right, 2 for down, 3 for left
    int score = 0;
    QVector<QPair<int,int>> *snake;
};

#endif // FIELD_H
