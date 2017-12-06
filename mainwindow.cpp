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
    field = new Field(10,10); // setup field size TODO not only square field
    QGraphicsScene *scene = new QGraphicsScene(0,0,512,512);
    ui->graphicsView->setScene(scene);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //debug field output
    {
        for(int i = 0; i < field->get_h(); i++){
            QString str = "";
            for(int j = 0; j < field->get_w(); j++){
                str.append(QString::number(field->get_cell(i,j)));
            }
            qDebug() << str;
        }
        qDebug() << '\n';
    }

    field->update();// moving snake, spreading food...
    ui->scores->display(field->get_score()); // displaying scores
    ui->graphicsView->scene()->clear();

    int scene_size = 384; // setting scene size
    int cell_size = scene_size / field->get_h(); // calculating cells size


    QPen mapPen(Qt::black);
    ui->graphicsView->scene()->addLine(0,0,field->get_w() * cell_size,0,mapPen);//top
    ui->graphicsView->scene()->addLine(0,field->get_h() * cell_size+2,field->get_w() * cell_size+2,field->get_h() * cell_size+2,mapPen); //bottom
    ui->graphicsView->scene()->addLine(field->get_w() * cell_size+2,0,field->get_w() * cell_size+2,field->get_h() * cell_size+2, mapPen); //right
    ui->graphicsView->scene()->addLine(0,0,0,field->get_h() * cell_size+2,mapPen);

    /*QPen mapPen(Qt::black);
    for(int i = 0; i <= scene->width(); i+= cell_size){
        scene->addLine(i,0,i,scene->height(),mapPen);
    }
    for(int i = 0; i <= scene->height(); i+= cell_size){
        scene->addLine(0,i,scene->width(),i,mapPen);
    }*/
    QPen cellsPen(Qt::white);
    for(int i = 0; i < field->get_h(); i++){
        for(int j = 0; j < field->get_w(); j++){
            int curr_cell = field->get_cell(i,j);
            QGraphicsRectItem *r1 = new QGraphicsRectItem();
            r1->setPen(cellsPen);
            r1->setRect(i * cell_size + 2,j * cell_size + 2,cell_size - 2, cell_size - 2);
            switch(curr_cell){
            /*case 0:
                r1->setBrush(Qt::gray);
                break;*/
            case 1:
                r1->setBrush(Qt::red);
                break;
            case 2:
                r1->setBrush(Qt::black);
                break;
            }

            ui->graphicsView->scene()->addItem(r1);
        }
    }

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()){
    case Qt::Key_Up:
        field->set_next_direction(0);
        break;
    case Qt::Key_Right:
        field->set_next_direction(1);
        break;
    case Qt::Key_Down:
        field->set_next_direction(2);
        break;
    case Qt::Key_Left:
        field->set_next_direction(3);
        break;
    default:
        qDebug() << "another key";
        MainWindow::keyPressEvent(event);
        break;
    }
}
