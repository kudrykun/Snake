#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QPair>

class Snake
{
public:
    Snake(int hx,  int hy, int length = 2, int direction = 0);
    void move();
    QPair<int, int> get_cell(int n);
    QPair<int, int> get_head();
    void set_cell(int x, int y, int n);
    void set_cell(QPair<int,int>, int n);
    void set_head(int x, int y);
    int length();
    void add_cell();
private:
    int direction; // 0 for up, 1 for right, 2 for down, 3 for left
    QVector<QPair<int,int>> *snake;
};

#endif // SNAKE_H
