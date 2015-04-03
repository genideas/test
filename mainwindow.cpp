#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    flStopMouse(false),
    prevAngle(0),startAngle(0),
    prev_x1(0),prev_y1(0)
{
    ui->setupUi(this);

    scene1 = new QGraphicsScene;
    ui->graphicsView1->setScene(scene1);
    scene1->addSimpleText("В одну сторону");
    scene1->addEllipse(QRectF(-100.0, -40.0, 100.0, 40.0));

    scene2 = new QGraphicsScene;
    ui->graphicsView2->setScene(scene2);
    scene2->addSimpleText("Во вторую сторону");
    scene2->addRect(QRectF(-100.0, -40.0, 100.0, 40.0));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAngle()));
    timer->start(150);

    listAngle = new TListAngle(ui->listView);

    ui->listView->setModel(listAngle);
}

MainWindow::~MainWindow()
{
    delete scene1;
    delete scene2;
    delete timer;
    delete listAngle;
    delete ui;
}

/*!
Обновляет значение изменения угла поворота картинки в зависимости от скорости движения курсора
*/
void MainWindow::updateAngle()
{
    QPoint p = ui->groupBox->mapFromGlobal(QCursor::pos());
    double x2 = 0;
    double y2 = - ui->groupBox->height()/2.;
    double x1 = p.x() - ui->groupBox->width()/2.;
    double y1 = p.y() - ui->groupBox->height()/2.;

    double curAngle = 180.*acos((x1*x2+y1*y2)/(sqrt(x1*x1+y1*y1)*sqrt(x2*x2+y2*y2)))/M_PI;
    if(x1 < 0) curAngle*=-1;
//    qDebug() << "curAngle = " << curAngle << "prevAngle = " << prevAngle <<"\r\n";
    if(x1!=prev_x1||y1!=prev_y1)
    {
        dA = curAngle - prevAngle;
        if(dA > 180) dA-=360;
        if(dA < -180) dA+=360;
        prev_x1 = x1;
        prev_y1 = y1;
        //поворачиваем, потому что мышка двигается
        prevAngle = curAngle;
        ui->graphicsView1->rotate(dA);
        ui->graphicsView2->rotate(-dA);
        flStopMouse = false;
    }
    else
    {//мыша встала - продолжаем двигаться пока не достигнем стартового угла
        if(!flStopMouse)
        {//сохраняем последнее значение до остановки мыши в модели
            listAngle->addAngle(prevAngle);
            flStopMouse = true;
        }
//        qDebug() << "Stop mouse " << dA << "\r\n";
        if((prevAngle<startAngle&&dA>0&&(prevAngle+dA>startAngle)))
            dA = - prevAngle + startAngle;
        if(prevAngle>startAngle&&dA<0&&(prevAngle+dA<startAngle))
            dA =  startAngle - prevAngle;
//        qDebug() << "dA = " << dA << "\r\n";
        ui->graphicsView1->rotate(dA);
        ui->graphicsView2->rotate(-dA);

        prevAngle+=dA;
        if(prevAngle>180) prevAngle-=360;
        if(prevAngle<-180) prevAngle+=360;

        if(fabs(startAngle - prevAngle)<0.1)
            dA = 0;
    }
}



