#include "amphiprion.h"

Amphiprion::Amphiprion(bool gender,size_t indexCell): Fish(gender,g_BREEDING_TIME,g_TIME_TO_DEATH)
{
    setIndexCell(indexCell);
}

bool Amphiprion::reproduction()
{

}

bool Amphiprion::eat()
{

}

void Amphiprion::move(size_t index)
{
    setIndexCell(index);
}
