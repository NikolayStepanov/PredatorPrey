#ifndef AMPHIPRION_H
#define AMPHIPRION_H

#include <fish.h>
#include<climits>

const size_t g_BREEDING_TIME = 2000;
const size_t g_TIME_TO_DEATH= INT_MAX;

class Amphiprion: public Fish
{
public:
    Amphiprion(bool gender,size_t indexCell);

    bool reproduction() override;
    bool eat() override;
    void move(size_t index) override;
};

#endif // AMPHIPRION_H
