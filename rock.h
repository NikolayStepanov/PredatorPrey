#ifndef ROCK_H
#define ROCK_H

#include <objectgame.h>

class Rock:public ObjectGame
{
public:
    Rock();
    ObjectType getType() override;
};

#endif // ROCK_H
