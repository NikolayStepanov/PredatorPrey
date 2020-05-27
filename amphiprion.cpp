#include "amphiprion.h"
#include <mediatorfishmotor.h>

const size_t g_BREEDING_TIME = 2000;
const size_t g_TIME_TO_DEATH= INT_MAX;

Amphiprion::Amphiprion(bool gender): Fish(gender,g_BREEDING_TIME,g_TIME_TO_DEATH)
{
    m_timerGiveOffspring = new QTimer(this);
    m_timerGiveOffspring->setInterval(g_BREEDING_TIME);
}

void Amphiprion::slotGiveOffspring()
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

ObjectType Amphiprion::getType()
{
    return m_gender?ObjectType::AMPHIPRION_MALE:ObjectType::AMPHIPRION_FEMALE;
}

bool Amphiprion::reproduction()
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
                if(objectInf.m_type == ObjectType::AMPHIPRION_MALE)
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

bool Amphiprion::eat()
{

}

void Amphiprion::move()
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
