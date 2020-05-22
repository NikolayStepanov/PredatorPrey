#ifndef MEDIATORFISHMOTOR_H
#define MEDIATORFISHMOTOR_H

#include <fish.h>
#include <QList>
#include <gamemodel.h>

class MediatorFishMotor
{
public:
    static MediatorFishMotor *getInstance();
    void initialization();
private:
    MediatorFishMotor();
    MediatorFishMotor( const MediatorFishMotor& );
    MediatorFishMotor& operator=( MediatorFishMotor& );

private:
    static MediatorFishMotor * p_instance;
};

MediatorFishMotor * MediatorFishMotor::p_instance = nullptr;

#endif // MEDIATORFISHMOTOR_H
