#ifndef FISH_H
#define FISH_H

#include <cstring>


class Fish
{
public:
    Fish(bool gender, size_t breedingTime, size_t timeToDeath);
    virtual ~Fish() = default;

    size_t getId();

    bool isMale();
    bool isFemale();
    bool isPairing();

    bool setIndexCell(size_t indexCell);

    virtual bool reproduction() = 0;
    virtual bool eat() = 0;
    virtual void move(size_t) = 0;

public:
    size_t id;

    bool m_gender;//1-male 0-female;
    bool m_pairing;

    size_t m_indexCell;
    size_t m_breedingTime;
    size_t m_timeToDeath;
};

#endif // FISH_H
