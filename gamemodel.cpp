#include "gamemodel.h"

#include <common.h>

#include <QRect>
#include <QSet>
#include "qmath.h"
#include <QPoint>

GameModel::GameModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    mediator = MediatorFishMotor::getInstance();
    connect(mediator,SIGNAL(ubdatedData(size_t)),this,SLOT(slotCellUpdate(size_t)));
    mediator->generationGame();

}

int GameModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return mediator->getRowCountBoard();
}

int GameModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return mediator->getColumnCountBoard();
}

QVariant GameModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    ObjectInf objectInf = mediator->getObjectInf(index);

    switch (role)
    {
    case IdObject:
        return QVariant(objectInf.m_id);
        break;
    case TypeCell:
        return QVariant(objectInf.m_type);
        break;
    case IndexCell:
        return QVariant(objectInf.m_index);
        break;
    default:
        return QVariant();
    }
}

bool GameModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) == value)
        return false;

    emit dataChanged(index, index, {role});

    return true;
}

Qt::ItemFlags GameModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

void GameModel::nextStep()
{
    mediator->nextStep();
}

void GameModel::changeTypeCell(QVariant id, QVariant type, QVariant index)
{
    mediator->changeTypeObject(id.toInt(nullptr),type.toInt(nullptr),index.toULongLong(nullptr));
}

QVector<int> GameModel::getAllRolesIndex()
{

}

void GameModel::slotCellUpdate(size_t indexCell)
{
    QPoint pointUpdate = mediator->getPointForIndex(indexCell);
    QModelIndex indexUpdate = index(pointUpdate.y(),pointUpdate.x());
    //emit dataChanged(index(0,0),index(7,15));
    emit dataChanged(indexUpdate,indexUpdate);
}


