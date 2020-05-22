#include "gamemodel.h"

#include <shark.h>
#include <amphiprion.h>

#include <QRect>
#include <QSet>
#include "qmath.h"

const size_t g_SHARK_COUNT = 10;
const size_t g_AMPHIPRION_COUNT = 20;
const size_t g_LET_COUNT = 10;

const size_t g_FISH_COUNT = g_SHARK_COUNT + g_AMPHIPRION_COUNT;



GameModel::GameModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    clear();

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    objectsMapGeneration();
}

int GameModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return height;
}

int GameModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return width;
}

QVariant GameModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    return QVariant(m_currentState[cellIndex({index.column(), index.row()})]);
}

bool GameModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) == value)
        return false;

    m_currentState[cellIndex({index.column(), index.row()})] = static_cast<Roles>(value.toInt());
    emit dataChanged(index, index, {role});

    return true;
}

Qt::ItemFlags GameModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

void GameModel::objectsMapGeneration()
{
    QSet<size_t> randPositions;

    while (static_cast<size_t>(randPositions.size())<= (g_FISH_COUNT+g_LET_COUNT))
    {
        randPositions.insert(qrand()%size);
    }

    for(size_t i =0; i<g_SHARK_COUNT;i++)
    {
        auto indexCellRand = randPositions.begin() + qrand()%randPositions.size();
        Shark* shark_fish = new Shark(qrand()%2,*indexCellRand);
        m_fishList.push_back(shark_fish);
        m_currentState[*indexCellRand] =
                shark_fish->isMale()? Roles::Male_Predator:Roles::Female_Predator;
        randPositions.erase(indexCellRand);
    }


    for(size_t i =0; i<g_AMPHIPRION_COUNT;i++)
    {
        auto indexCellRand = randPositions.begin() + qrand()%randPositions.size();
        Amphiprion* amphiprion_fish = new Amphiprion(qrand()%2,*indexCellRand);
        m_fishList.push_back(amphiprion_fish);
        m_currentState[*indexCellRand] =
                amphiprion_fish->isMale()? Roles::Male_Prey:Roles::Female_Prey;
        randPositions.erase(indexCellRand);
    }

    for(size_t i =0; i<g_LET_COUNT;i++)
    {
        auto indexCellRand = randPositions.begin() + qrand()%randPositions.size();
        m_currentState[*indexCellRand] = Roles::Let;
        randPositions.erase(indexCellRand);
    }
    emit dataChanged(index(0, 0), index(height - 1, width - 1));
}

void GameModel::nextStep()
{
    for(auto fish: m_fishList)
    {
        QList<int> indexList= searchNeighboringCells(fish->m_indexCell);
        if(!indexList.isEmpty())
        {
            int modeIdex = indexList[(qrand()%indexList.size())];
            m_currentState[modeIdex]=m_currentState[fish->m_indexCell];
            m_currentState[fish->m_indexCell]=Roles::Empty;
            fish->move(modeIdex);
        }
    }

    /*for(auto fish: m_fishList)
    {
        if(typeid (*fish)==typeid(Shark))
        {
            int indexFood= searchFoodForShark(fish->m_indexCell);
            if(indexFood!=-1)
            {
                for (auto i = m_fishList.begin(), e = m_fishList.end(); i !=e ;)
                {
                    if ((*i)->m_indexCell==static_cast<size_t>(indexFood))
                    {
                        delete *i;
                        i = m_fishList.erase(i);
                        e = m_fishList.end();
                    }
                    else
                        ++i;
                }
                m_currentState[indexFood]=m_currentState[fish->m_indexCell];
                m_currentState[fish->m_indexCell]=Roles::Empty;
                fish->move(indexFood);
            }
        }
    }*/


    emit dataChanged(index(0, 0), index(height - 1, width - 1));
}

void GameModel::clear()
{
    m_currentState.fill(Empty);
    emit dataChanged(index(0, 0), index(height - 1, width - 1), {Empty});
}

void GameModel::changeCellType()
{

}

QString GameModel::roleNames(int role) const
{
    switch (role) {
    case Empty:
        return "Empty";
    case Female_Prey:
        return "Female_Prey";
    case Male_Prey:
        return "Female_Prey";
    case Female_Predator:
        return "Female_Predator";
    case Male_Predator:
        return "Male_Predator";
    case Let:
        return "Let";
    default:
        return "no";
    }
}

QList<int> GameModel::searchNeighboringCells(size_t index)
{
    QList<int> cells;
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            if (x == 0 && y == 0)
                continue;

            QPoint neighborPosition = cellCoordinatesFromIndex(index);

            neighborPosition.setX(neighborPosition.x()+x);
            neighborPosition.setY(neighborPosition.y()+y);

            if (!areCellCoordinatesValid(neighborPosition))
                continue;

            if(m_currentState[cellIndex(neighborPosition)]==Roles::Empty)
            {
                cells.push_back(cellIndex(neighborPosition));
            }
        }
    }

    return cells;
}

int GameModel::searchFoodForShark(size_t index)
{
    QList<int> cellsFood;
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            if (x == 0 && y == 0)
                continue;

            QPoint neighborPosition = cellCoordinatesFromIndex(index);

            neighborPosition.setX(neighborPosition.x()+x);
            neighborPosition.setY(neighborPosition.y()+y);

            if (!areCellCoordinatesValid(neighborPosition))
                continue;

            if(m_currentState[cellIndex(neighborPosition)]==Roles::Male_Prey ||
                    m_currentState[cellIndex(neighborPosition)]==Roles::Female_Prey)
            {
                cellsFood.push_back(cellIndex(neighborPosition));
            }
        }
    }
    if(!cellsFood.isEmpty())
    {
        return cellsFood[qrand()%cellsFood.size()];
    }
    else{return -1;}
}

bool GameModel::areCellCoordinatesValid(const QPoint &coordinates)
{
    return QRect(0, 0, width, height).contains(coordinates);
}

bool GameModel::areCellIndexValid(const int cellIndex)
{
    QPoint coordinates = cellCoordinatesFromIndex(cellIndex);
    return areCellCoordinatesValid(coordinates);
}

QPoint GameModel::cellCoordinatesFromIndex(int cellIndex)
{
    return {cellIndex % width, cellIndex / width};
}

std::size_t GameModel::cellIndex(const QPoint &coordinates)
{
    return std::size_t(coordinates.y() * width + coordinates.x());
}

QModelIndex& GameModel::cellModelIndexFromIndex(const int cellIndex)
{
    QPoint point = cellCoordinatesFromIndex(cellIndex);

    //return index(point.x(),point.y(),QModelIndex());
}


