#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "field.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QKeyEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    field = new Field(20,20);




    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
//! [5] //! [6]
    timer->start(200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    field->move();
    int scene_size = 384;
    int cell_size = scene_size / field->get_h();
    ui->graphicsView->resize(512,512);

    QGraphicsScene *scene = new QGraphicsScene(0,0,scene_size,scene_size);

    QPen mapPen(Qt::black);
    for(int i = 0; i <= scene->width(); i+= cell_size){
        scene->addLine(i,0,i,scene->height(),mapPen);
    }
    for(int i = 0; i <= scene->height(); i+= cell_size){
        scene->addLine(0,i,scene->width(),i,mapPen);
    }
    for(int i = 0; i < field->get_h(); i++){
        QString str = "";
        for(int j = 0; j < field->get_w(); j++){
            int curr_cell = field->get_item(i,j);
            QGraphicsRectItem *r1 = new QGraphicsRectItem();
            r1->setRect(i * cell_size + 2,j * cell_size + 2,cell_size - 2, cell_size - 2);
            switch(curr_cell){
            case 0:
                r1->setBrush(Qt::gray);
                break;
            case 1:
                r1->setBrush(Qt::red);
                break;
            case 2:
                r1->setBrush(Qt::black);
                break;
            }

            scene->addItem(r1);
            str.append(QString::number(curr_cell));
        }
        qDebug() << str;
    }
    qDebug() << '\n';
    ui->graphicsView->setScene(scene);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()){
    case Qt::Key_Up:
        field->set_direction(0);
        break;
    case Qt::Key_Right:
        field->set_direction(1);
        break;
    case Qt::Key_Down:
        field->set_direction(2);
        break;
    case Qt::Key_Left:
        field->set_direction(3);
        break;
    default:
        qDebug() << "another key";
        MainWindow::keyPressEvent(event);
        break;
    }
}
