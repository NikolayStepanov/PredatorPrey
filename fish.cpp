#include "fish.h"

static size_t ID = 0;

Fish::Fish(bool gender, size_t breedingTime, size_t timeToDeath)
    :m_gender(gender), m_breedingTime(breedingTime), m_timeToDeath(timeToDeath)
{
    m_pairing = false;
    m_indexCell = 0;
    id=ID++;
}

size_t Fish::getId()
{
    return id;
}

bool Fish::isMale()
{
    return m_gender;
}

bool Fish::isFemale()
{
    return !m_gender;
}

bool Fish::isPairing()
{
    return m_pairing;
}

bool Fish::setIndexCell(size_t indexCell)
{
    if(m_indexCell!=indexCell)
    {
        m_indexCell = indexCell;
        return true;
    }
    return false;
}
