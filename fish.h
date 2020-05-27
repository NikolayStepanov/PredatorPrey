#ifndef FISH_H
#define FISH_H

#include <cstring>
#include <objectgame.h>

class Fish: virtual public  ObjectGame
{
public:
    bool isMale();
    bool isFemale();
    bool isPairing();

    virtual ObjectType getType() = 0;
    virtual bool reproduction() = 0;
    virtual bool eat() = 0;
    virtual void move() = 0;


//protected:
    Fish(bool gender, size_t breedingTime, size_t timeToDeath);
    bool m_gender;//1-male 0-female;
    bool m_pairing;

    size_t m_breedingTime;
    size_t m_timeToDeath;
};

#endif // FISH_H
