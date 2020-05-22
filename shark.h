#ifndef SHARK_H
#define SHARK_H

#include <fish.h>


const size_t g_BREEDINGTIME = 3000;
const size_t g_TIMETODEATH = 5000;


class Shark: public Fish
{
public:
    Shark(bool gender, size_t indexCell);

    bool reproduction() override;
    bool eat() override;
    void move(size_t index) override;
};

#endif // SHARK_H
