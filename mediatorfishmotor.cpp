#include "mediatorfishmotor.h"
#include <QModelIndex>
#include <QPoint>

#include <generator.h>

MediatorFishMotor * MediatorFishMotor::p_instance = nullptr;

MediatorFishMotor *MediatorFishMotor::getInstance()
{
    if(!p_instance)
        p_instance = new MediatorFishMotor();
    return p_instance;
}

MediatorFishMotor::~MediatorFishMotor()
{
    delete p_gameBoard;
    delete p_generator;

    m_objectsGameList.clear();
    m_fishList.clear();
    m_sharkList.clear();
    m_amphiprionList.clear();

}

QList<ObjectInf> MediatorFishMotor::getNeighboringObjectInf(size_t id)
{
    size_t index = p_gameBoard->getIndexCellForObjectId(id);
    QList<ObjectInf> neighboringObjectInf =
            p_gameBoard->getNeighboringObjectInf(index);

    return neighboringObjectInf;
}

QList<size_t> MediatorFishMotor::getEmptyNeighboringCell(size_t id)
{
    QList<ObjectInf> neighboringObjectInf = getNeighboringObjectInf(id);
    QList<size_t> emptyCellsIndex;

    for(auto objectInf:neighboringObjectInf)
    {
        if(objectInf.m_type==ObjectType::EMPTY)
        {
            emptyCellsIndex.push_back(objectInf.m_index);
        }
    }
    return emptyCellsIndex;
}

ObjectInf MediatorFishMotor::getObjectInfForId(size_t objectId)
{
    return p_gameBoard->getObjectInf(objectId);
}

void MediatorFishMotor::moveObject(size_t objectId, size_t indexNext)
{
    p_gameBoard->moveObject(objectId,indexNext);
}

void MediatorFishMotor::deleteObject(ObjectInf objectInf)
{
    ObjectGame * object = p_gameBoard->getObjectGame(objectInf.m_id);
    switch (objectInf.m_type)
    {
    case ObjectType::ROCK:
    {
        break;
    }
    case ObjectType::SHARK_MALE:
    {
        m_fishList.removeAll(dynamic_cast<Fish*>(object));
        m_sharkList.removeAll(dynamic_cast<Shark*>(object));
        break;
    }
    case ObjectType::SHARK_FEMALE:
    {
        m_fishList.removeAll(dynamic_cast<Fish*>(object));
        m_sharkList.removeAll(dynamic_cast<Shark*>(object));
        break;
    }
    case ObjectType::AMPHIPRION_MALE:
    {
        m_fishList.removeAll(dynamic_cast<Fish*>(object));
        m_amphiprionList.removeAll(dynamic_cast<Amphiprion*>(object));
        break;
    }
    case ObjectType::AMPHIPRION_FEMALE:
    {
        m_fishList.removeAll(dynamic_cast<Fish*>(object));
        m_amphiprionList.removeAll(dynamic_cast<Amphiprion*>(object));
        break;
    }
    default:
        break;
    }
    m_fishList.removeAll(nullptr);
    p_gameBoard->deleteObject(objectInf.m_id);
}

ObjectGame *MediatorFishMotor::createObjectGame(ObjectType type)
{
    ObjectGame * object = nullptr;

    switch (type)
    {
    case ObjectType::ROCK:
        object = new Rock();
        break;
    case ObjectType::SHARK_MALE:
    {
        Shark * shark = new Shark(true);
        object = shark;
        m_sharkList.push_back(shark);
        m_fishList.push_back(shark);
        break;
    }
    case ObjectType::SHARK_FEMALE:
    {
        Shark * shark = new Shark(false);
        object = shark;
        m_sharkList.push_back(shark);
        m_fishList.push_back(shark);
        break;
    }
    case ObjectType::AMPHIPRION_MALE:
    {
        Amphiprion * amphiprion = new Amphiprion(true);
        object = amphiprion;
        m_amphiprionList.push_back(amphiprion);
        m_fishList.push_back(amphiprion);
        break;
    }
    case ObjectType::AMPHIPRION_FEMALE:
    {
        Amphiprion * amphiprion = new Amphiprion(false);
        object = amphiprion;
        m_amphiprionList.push_back(amphiprion);
        m_fishList.push_back(amphiprion);
        break;
    }
    case ObjectType::EMPTY:
    {
        break;
    }
    default:
        assert( false);
    }

    m_objectsGameList.push_back(object);
    return object;
}

MediatorFishMotor::MediatorFishMotor(QObject *parent):
    QObject(parent),p_gameBoard(nullptr),p_generator(nullptr)
{
    p_gameBoard = new GameBoard(this,width,height);
}

size_t MediatorFishMotor::getRowCountBoard() const
{
    return p_gameBoard->getHeight();
}

size_t MediatorFishMotor::getColumnCountBoard() const
{
    return  p_gameBoard->getWidth();
}

ObjectInf MediatorFishMotor::getObjectInf(const QModelIndex index) const
{
    size_t indexObject = p_gameBoard->cellIndex(index);
    return p_gameBoard->getCellObjectInf(indexObject);
}

void MediatorFishMotor::nextStep()
{
    for(auto fish:m_fishList)
    {

        fish->reproduction();
    }

    for(auto shark:m_sharkList)
    {
        if(!shark->eat())
        {
            shark->move();
        };
    }
    for(auto amphiprion :m_amphiprionList)
    {
        amphiprion->move();
    }
}

QPoint MediatorFishMotor::getPointForIndex(size_t index)
{
    return p_gameBoard->cellCoordinatesFromIndex(index);
}

void MediatorFishMotor::changeTypeObject(size_t id, int type, size_t index)
{
    switch (type)
    {
    case ObjectType::ROCK:
    {
        deleteObjectForId(id);
        p_gameBoard->setCellNewObject(index,createObjectGame(ObjectType::SHARK_MALE));
        break;
    }
    case ObjectType::SHARK_MALE:
    {
        deleteObjectForId(id);
        p_gameBoard->setCellNewObject(index,createObjectGame(ObjectType::SHARK_FEMALE));
        break;
    }
    case ObjectType::SHARK_FEMALE:
    {
        deleteObjectForId(id);
        p_gameBoard->setCellNewObject(index,createObjectGame(ObjectType::AMPHIPRION_MALE));
        break;
    }
    case ObjectType::AMPHIPRION_MALE:
    {
        deleteObjectForId(id);
        p_gameBoard->setCellNewObject(index,createObjectGame(ObjectType::AMPHIPRION_FEMALE));
        break;
    }
    case ObjectType::AMPHIPRION_FEMALE:
    {
        deleteObjectForId(id);
        p_gameBoard->setCellNewObject(index,createObjectGame(ObjectType::EMPTY));
        break;
    }
    case ObjectType::EMPTY:
    {
        deleteObjectForId(id);
        p_gameBoard->setCellNewObject(index,createObjectGame(ObjectType::ROCK));
        break;
    }
    default:
        assert( false);
    }
}

GameBoard *MediatorFishMotor::getGameBoard()
{
    return p_gameBoard;
}

void MediatorFishMotor::generationGame()
{
    p_generator=Generator::getInstance();
    p_generator->generationBoard();
    m_fishList = getAllFish();
}

Generator *MediatorFishMotor::getGenerator()
{
    return p_generator->getInstance();
}

QList<Fish*> MediatorFishMotor::getAllFish()
{
    QList<ObjectInf> objectsInf = p_gameBoard->getObjectsInf();
    QList<size_t> objectsId;
    QList<ObjectGame *> objectsGameList;
    QList<Fish*> fish;

    for(ObjectInf infObject:objectsInf)
    {
        if(infObject.m_type!=ObjectType::ROCK &&
                infObject.m_type!=ObjectType::EMPTY)
        {
            objectsId.push_back(infObject.m_id);
        }
    }

    objectsGameList = p_gameBoard->getObjectsGameForId(objectsId);
    for(auto object:objectsGameList)
    {
        fish.push_back(dynamic_cast<Fish*>(object));
    }

    return fish;
}

void MediatorFishMotor::slotUpdatedData(size_t index)
{
    emit ubdatedData(index);
}

void MediatorFishMotor::deleteObjectForId(size_t objectId)
{
    ObjectInf objectInf = p_gameBoard->getObjectInf(objectId);
    deleteObject(objectInf);
}
