#include "shark.h"

const size_t g_BREEDINGTIME = 4000;
const size_t g_TIMETODEATH = 8000;

#include <mediatorfishmotor.h>

Shark::Shark(bool gender):QObject(),Fish(gender,g_BREEDINGTIME,g_TIMETODEATH)
{
    m_timerGiveOffspring = new QTimer(this);
    m_timerDeath = new QTimer(this);

    m_timerGiveOffspring->setInterval(g_BREEDINGTIME);
    m_timerDeath->setInterval(g_TIMETODEATH);
}

Shark::~Shark()
{
    delete m_timerGiveOffspring;
    delete m_timerDeath;
}

void Shark::slotGiveOffspring()
{
    m_timerGiveOffspring->stop();
    MediatorFishMotor* mediator = MediatorFishMotor::getInstance();
    size_t id = getId();
    QList<size_t> listIndexEmpty = mediator->getEmptyNeighboringCell(id);
    if(!listIndexEmpty.isEmpty())
    {
        mediator->getGenerator()->offspringGenerator(listIndexEmpty,getType());
    }
    m_pairing = false;
}

void Shark::slotDie()
{
    m_timerDeath->stop();
    emit die(getId());
}

ObjectType Shark::getType()
{
    return m_gender?ObjectType::SHARK_MALE:ObjectType::SHARK_FEMALE;
}

bool Shark:: reproduction()
{
    if(!m_gender && !m_pairing)
    {
        MediatorFishMotor* mediator = MediatorFishMotor::getInstance();
        size_t id = getId();
        QList<ObjectInf> listObjectsInf= mediator->getNeighboringObjectInf(id);
        QList<ObjectInf> listObjectsEatForId;

        if(!listObjectsInf.isEmpty())
        {
            for(auto objectInf:listObjectsInf)
            {
                if(objectInf.m_type == ObjectType::SHARK_MALE)
                {
                    m_pairing = true;
                    connect(m_timerGiveOffspring, SIGNAL(timeout()),SLOT(slotGiveOffspring()));
                    m_timerGiveOffspring->start();
                    return true;
                }
            }
        }
    }
    return false;
}

bool Shark::eat()
{
    MediatorFishMotor* mediator = MediatorFishMotor::getInstance();
    size_t id = getId();
    QList<ObjectInf> listObjectsInf= mediator->getNeighboringObjectInf(id);
    QList<ObjectInf> listObjectsEatForId;

    if(!listObjectsInf.isEmpty())
    {
        for(auto objectInf:listObjectsInf)
        {
            if(objectInf.m_type == ObjectType::AMPHIPRION_MALE ||
                    objectInf.m_type == ObjectType::AMPHIPRION_FEMALE)
            {
                //mediator->deleteObject(objectInf);
                listObjectsEatForId.push_back(objectInf);
            }
        }
    }
    if(!listObjectsEatForId.isEmpty())
    {
        size_t indexEat = qrand()%(listObjectsEatForId.size());
        ObjectInf object = listObjectsEatForId.at(indexEat);
        mediator->deleteObject(object);
        mediator->moveObject(id, object.m_index);
        if(!m_timerDeath->isActive())
        {
            connect(m_timerDeath, SIGNAL(timeout()),SLOT(slotDie()));
            connect(this, SIGNAL(die(size_t)),mediator,SLOT(deleteObjectForId(size_t)));
            m_timerDeath->start();
        }
        return true;
    }
    return false;
}

void Shark::move()
{
    MediatorFishMotor* mediator = MediatorFishMotor::getInstance();
    size_t id = getId();
    QList<size_t> listIndexEmpty = mediator->getEmptyNeighboringCell(id);
    if(!listIndexEmpty.isEmpty())
    {
        size_t indexNext = mediator->getGenerator()->generatIndex(listIndexEmpty);
        mediator->moveObject(id,indexNext);
    }
}
