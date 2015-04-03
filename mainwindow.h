/*!
    \brief  Тестовая форма выполненная по заданию


    Поле с двумя картинками НЕ по центру поля. Когда пользователь водит мышью/пальцем по полю, картинки поворачиваются относительно центра поля одна по часовой стрелке, другая против часовой на соответствующий угол (так, чтобы, если пользователь опишет мышью/пальцем окружность, обе картинки оказались в первоначальном положении).
    Если пользователь перестал двигать мышью/пальцем, когда картинки не находятся в первоначальном положении, они должны продолжить путь до первоначального положения с некоторой захардкоженной скоростью.
    Справа поля - список всех углов, на которых пользователь заканчивал двигать мышью/пальцем. Список заполняется из модели - потомка QAbstractListModel. В модели углы всегда отсортированы по возрастанию величины угла. QSortFilterProxyModel не используется.
    Бонус:
    Если пользователь перестал двигать мышью/пальцем, когда картинки не находятся в первоначальном положении, они должны продолжить путь до первоначального положения с той же угловой скоростью, с которой пользователь заканчивал двигать мышью/пальцем.

    \authors Фищев Г.Ю.
    \date 03.04.2015
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <math.h>
#include <QTimer>
#include <QtDebug>
#include "tlistangle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateAngle();
private:
    Ui::MainWindow *ui;
    QTimer * timer ;
    QGraphicsScene * scene1, *scene2;
    double prevAngle;
    double dA;
    double startAngle;
    double prev_x1, prev_y1;
    bool flStopMouse;

    TListAngle * listAngle;
};

#endif // MAINWINDOW_H
