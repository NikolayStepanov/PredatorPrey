#ifndef GENERATOR_H
#define GENERATOR_H

#include <mediatorfishmotor.h>

#include <gameboard.h>

class Generator
{
public:
    static Generator *getInstance();
    ~Generator();

    bool generationBoard();
    void offspringGenerator(QList<size_t> indexEmptyList, ObjectType typeObject);
    size_t generatIndex(QList<size_t> indexesList);

private:
    Generator();
    Generator( const Generator& );
    Generator& operator=( Generator& );

private:
    static Generator * p_instance;
    GameBoard * p_board;
};

#endif // GENERATOR_H
