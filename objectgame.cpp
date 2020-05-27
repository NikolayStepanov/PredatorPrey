#include "objectgame.h"

static size_t ID = 1;

ObjectGame::ObjectGame()
{
    m_id=ID++;
}

size_t ObjectGame::getId() const
{
    return m_id;
}

