#include "shark.h"
#include "gamemodel.h"

Shark::Shark(bool gender, size_t indexCell):Fish(gender,g_BREEDINGTIME,g_TIMETODEATH)
{
    setIndexCell(indexCell);
}

bool Shark::reproduction()
{

}

bool Shark::eat()
{

}

void Shark::move(size_t index)
{
    if(index!=m_indexCell)
        setIndexCell(index);
}
