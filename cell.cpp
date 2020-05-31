#include "cell.h"
#include <rock.h>
#include <shark.h>
#include <amphiprion.h>

Cell::Cell(QObject *parent, size_t index):
    QObject(parent),m_index(index), p_object(nullptr)
{

}

Cell::~Cell()
{
    delete p_object;
}

bool Cell::createObject(ObjectType type)
{
    if(!p_object)
    {
        return false;
    }
    else{
        switch (type)
        {
        case ObjectType::ROCK:
            p_object = new Rock();
            break;
        case ObjectType::SHARK_MALE:
            p_object = new Shark(true);
            break;
        case ObjectType::SHARK_FEMALE:
            p_object = new Shark(false);
            break;
        case ObjectType::AMPHIPRION_MALE:
            p_object = new Amphiprion(true);
            break;
        case ObjectType::AMPHIPRION_FEMALE:
            p_object = new Amphiprion(false);
            break;
        default:
            return false;
        }
    }
    //emit updatedCell(m_index);
    return true;
}

bool Cell::setObject(ObjectGame *objectGame)
{
    if(!p_object)
    {
        delete p_object;
        p_object = objectGame;
    }
    else
    {
        p_object = objectGame;
    }
    emit updatedCell(m_index);
    return true;
}

void Cell::deleteObject()
{
    if(p_object!=nullptr)
    {
        delete p_object;
    }
    p_object = nullptr;
    emit updatedCell(m_index);
}

ObjectInf Cell::getObjectInf()
{
    size_t id = getIdObject();
    ObjectType type = getType();
    size_t index = getIndex();
    ObjectInf inf(id,index,type);
    return inf;
}

size_t Cell::getIndex() const
{
    return m_index;
}

ObjectType Cell::getType() const
{
    if(p_object!=nullptr)
    {
        return p_object->getType();
    }
    else
    {
        return ObjectType::EMPTY;
    }
}

size_t Cell::getIdObject() const
{
    if(p_object!=nullptr)
    {
        return p_object->getId();
    }
    else
    {
        return 0;
    }
}

ObjectGame *Cell::getObject() const
{
    return p_object;
}
