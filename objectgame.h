#ifndef OBJECTGAME_H
#define OBJECTGAME_H

#include <common.h>

class ObjectGame
{
public:
    ObjectGame();
    virtual ~ObjectGame() = default;
    virtual ObjectType getType()= 0;
    size_t getId() const;
private:
    size_t m_id;
};

#endif // OBJECTGAME_H
