#ifndef BOOTSTRAPPER_H
#define BOOTSTRAPPER_H

class GameBoard;
class Generator;

class Bootstrapper
{
public:
    Bootstrapper();
    void Initialize();
    //get
private:
    GameBoard *p_gameBoard;
    Generator *p_generator;
};

#endif // BOOTSTRAPPER_H
