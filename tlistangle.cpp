#include "tlistangle.h"

TListAngle::TListAngle(QObject *parent):
            QAbstractListModel(parent)
{
}

TListAngle::~TListAngle()
{

}

//!чтение поля
QVariant TListAngle::data(const QModelIndex &index, int role) const
{
    qDebug() << "index = " << index;
    if (!index.isValid())
        return QVariant();
    if (index.row() < 0 || index.row() > angles.count())
        return QVariant();
    if (role == Qt::DisplayRole)
    {
        qDebug() << "angles[index.row()] = " << angles[index.row()];
        return angles[index.row()];
    }
    else
        return QVariant();

}

/*!
Функция добавления угла
\param[in] angle Значение угла поворота
*/
void TListAngle::addAngle(double angle)
{
    qDebug() << "TListAngle::addAngle(double angle) " << angle;
    beginInsertRows(QModelIndex(), 0, angles.size() + 1);
    angles << angle;
    qSort(angles.begin(), angles.end());
    endInsertRows();
}

//!Функция возвращения количество строк данных в модели возвращает количество элементов списка:
int TListAngle::rowCount(const QModelIndex &parent) const
{
    qDebug() << "rowCount = " << angles.size();
    return angles.size();
}


