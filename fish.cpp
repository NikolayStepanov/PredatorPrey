#include "fish.h"



Fish::Fish(bool gender, size_t breedingTime, size_t timeToDeath)
    :m_gender(gender),m_pairing(false),m_breedingTime(breedingTime), m_timeToDeath(timeToDeath)
{

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
