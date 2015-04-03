/*!
    \brief  Модель хранения углов остановок мыши
    \authors Фищев Г.Ю.
    \date 03.04.2015
 */

#ifndef TLISTANGLE_H
#define TLISTANGLE_H

#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include <QModelIndex>
#include <QtDebug>

class TListAngle : public QAbstractListModel
{
    Q_OBJECT

public:
    TListAngle(QObject *parent);
    ~TListAngle();

    QVariant data(const QModelIndex &index, int role) const; ///< функция доступа к данным
    int rowCount(const QModelIndex &parent) const; ///< количество элементов в модели

public slots:
    void addAngle(double angle); ///< добавить контакт в модель
private:
    QList<double> angles; ///< список контактов
};

#endif // TLISTANGLE_H
