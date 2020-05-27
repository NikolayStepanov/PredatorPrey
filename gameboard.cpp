#include "gameboard.h"

#include <QRect>
#include <QModelIndex>
#include <cell.h>

#include <common.h>

GameBoard::GameBoard(QObject *parent, size_t width, size_t height): QObject(parent)
{
    m_height = height;
    m_width = width;
    m_size = width * height;

    m_cellsContainer.reserve(m_size*sizeof(Cell));

    createEmptyBoard();
}

GameBoard::~GameBoard()
{
    deleteBoard();
}

bool GameBoard::moveObject(size_t objectId, size_t indexNext)
{
    size_t indexObject = getIndexCellForObjectId(objectId);
    if(indexObject!=indexNext)
    {
        Cell *cellObject = getCell(indexObject);
        Cell *cellMove = getCell(indexNext);

        cellMove->setObject(cellObject->getObject());

        cellObject->setObject(nullptr);

        return true;
    }
    return false;
}

void GameBoard::deleteObject(size_t objectId)
{
    for(auto cell:m_cellsContainer)
    {
        if(cell->getObjectInf().m_id == objectId)
        {
            cell->deleteObject();
            break;
        }
    }
}

ObjectGame *GameBoard::getObjectGame(size_t objectId)
{
    ObjectGame* object=nullptr;
    for(auto cell: m_cellsContainer)
    {
        if(objectId==cell->getIdObject())
        {
            object = cell->getObject();
            break;
        }
    }
    return object;
}

bool GameBoard::setCellNewObject(size_t index, ObjectGame * object)
{
    if(areCellIndexValid(index))
    {
        m_cellsContainer[index]->setObject(object);
    }

    return true;
}

ObjectInf GameBoard::getCellObjectInf(size_t index)
{
    if(areCellIndexValid(index))
    {
        Cell* cell = m_cellsContainer.at(index);
        return ObjectInf(cell->getIdObject(),index,cell->getType());
    }
    return ObjectInf();
}

ObjectInf GameBoard::getObjectInf(size_t objectId)
{
    ObjectInf objectInf;
    for(auto cell: m_cellsContainer)
    {
        ObjectInf objectInfInCell = cell->getObjectInf();
        if(objectInfInCell.m_id == objectId)
        {
            return objectInfInCell;
        }
    }
    return objectInf;
}

QList<ObjectInf> GameBoard::getObjectsInf()
{
    QList<ObjectInf> listObjectsInf;
    for(auto cell: m_cellsContainer)
    {
        listObjectsInf.push_back(cell->getObjectInf());
    }

    return listObjectsInf;
}

QList<ObjectInf> GameBoard::getNeighboringObjectInf(size_t index)
{
    QList<ObjectInf> infObjectsList;

    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            if (x == 0 && y == 0)
                continue;

            QPoint neighborPosition = cellCoordinatesFromIndex(index);

            neighborPosition.setX(neighborPosition.x()+x);
            neighborPosition.setY(neighborPosition.y()+y);

            if (!areCellCoordinatesValid(neighborPosition))
                continue;

            size_t neighborIndex = cellIndex(neighborPosition);

            ObjectInf infNeighbord = getCellObjectInf(neighborIndex);

            infObjectsList.push_back(infNeighbord);
        }
    }

    return infObjectsList;
}

QList<ObjectGame *> GameBoard::getObjectsGameForIndices(QList<size_t> objectIndices)
{
    QList<ObjectGame*> listObjects;

    for(auto index:objectIndices)
    {
        listObjects.push_back(m_cellsContainer[index]->getObject());
    }

    return listObjects;
}

QList<ObjectGame *> GameBoard::getObjectsGameForId(QList<size_t> objectsId)
{
    QList<ObjectGame*> listObjects;

    for(auto objectId: objectsId)
    {
        for(auto cell: m_cellsContainer)
        {
            if(objectId==cell->getIdObject())
            {
                listObjects.push_back(cell->getObject());
                break;
            }
        }
    }

    return listObjects;
}

size_t GameBoard::getIndexCellForObjectId(const size_t id) const
{
    for(auto cell:m_cellsContainer)
    {
        if(cell->getIdObject()==id)
        {
            return cell->getIndex();
        }
    }
    return 0;
}

Cell *GameBoard::getCell(size_t index)
{
    if(areCellIndexValid(index))
    {
        return m_cellsContainer.at(index);
    }
    return nullptr;
}

QVector<Cell *> GameBoard::getAllCells()
{
    return m_cellsContainer;
}

bool GameBoard::areCellCoordinatesValid(const QPoint &coordinates) const
{
    return QRect(0, 0,m_width, m_height).contains(coordinates);
}

bool GameBoard::areCellIndexValid(const size_t cellIndex)
{
    QPoint coordinates = cellCoordinatesFromIndex(cellIndex);
    return areCellCoordinatesValid(coordinates);
}

QPoint GameBoard::cellCoordinatesFromIndex(const size_t cellIndex) const
{
    return {static_cast<int>(cellIndex % m_width),
                static_cast<int>(cellIndex / m_width)};
}

size_t GameBoard::cellIndex(const QModelIndex index) const
{
    return cellIndex(QPoint(index.column(),index.row()));
}

size_t GameBoard::cellIndex(const QPoint &coordinates) const
{
    if(areCellCoordinatesValid(coordinates))
    {
        return size_t(coordinates.y() * m_width + coordinates.x());
    }
    return UINT64_MAX;
}

void GameBoard::deleteBoard()
{
    m_cellsContainer.clear();
}

void GameBoard::createEmptyBoard()
{
    if(m_cellsContainer.isEmpty())
    {
        for(size_t i = 0; i< m_size;i++)
        {
            m_cellsContainer.push_back(new Cell(nullptr,i));
            connect(m_cellsContainer.at(i), SIGNAL(updatedCell(size_t)),parent(), SLOT(slotUpdatedData(size_t)));
        }
    }
}

size_t GameBoard::getHeight() const
{
    return m_height;
}

size_t GameBoard::getWidth() const
{
    return m_width;
}

size_t GameBoard::getSize() const
{
    return m_size;
}
