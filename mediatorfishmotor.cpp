#include "mediatorfishmotor.h"

MediatorFishMotor *MediatorFishMotor::getInstance()
{
    if(!p_instance)
        p_instance = new MediatorFishMotor();
    return p_instance;
}

MediatorFishMotor::MediatorFishMotor()
{

}
