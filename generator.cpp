#include "generator.h"
#include <QTime>
#include <QSet>
#include <mediatorfishmotor.h>

const size_t g_SHARK_COUNT = 10;
const size_t g_AMPHIPRION_COUNT = 35;
const size_t g_LET_COUNT = 10;

const size_t g_FISH_COUNT = g_SHARK_COUNT + g_AMPHIPRION_COUNT;

Generator * Generator::p_instance = nullptr;

Generator *Generator::getInstance()
{
    if(!p_instance)
        p_instance = new Generator();
    return p_instance;
}

bool Generator::generationBoard()
{
    QSet<size_t> randPositions;
    MediatorFishMotor* mediator = MediatorFishMotor::getInstance();
    while (static_cast<size_t>(randPositions.size())<= (g_FISH_COUNT+g_LET_COUNT))
    {
        randPositions.insert(qrand()%p_board->getSize());
    }

    for(size_t i =0; i<g_SHARK_COUNT;i++)
    {
        auto indexCellRand = randPositions.begin() + qrand()%randPositions.size();
        ObjectType type = qrand()%2?ObjectType::SHARK_MALE:ObjectType::SHARK_FEMALE;
        p_board->setCellNewObject(*indexCellRand,mediator->createObjectGame(type));
        randPositions.erase(indexCellRand);
    }

    for(size_t i =0; i<g_AMPHIPRION_COUNT;i++)
    {
        auto indexCellRand = randPositions.begin() + qrand()%randPositions.size();
        ObjectType type = qrand()%2?ObjectType::AMPHIPRION_MALE:ObjectType::AMPHIPRION_FEMALE;
        p_board->setCellNewObject(*indexCellRand,mediator->createObjectGame(type));
        randPositions.erase(indexCellRand);
    }

    for(size_t i =0; i<g_LET_COUNT;i++)
    {
        auto indexCellRand = randPositions.begin() + qrand()%randPositions.size();
        p_board->setCellNewObject(*indexCellRand, new Rock());
        randPositions.erase(indexCellRand);
    }

    return true;
}

void Generator::offspringGenerator(QList<size_t> indexEmptyList, ObjectType typeObject)
{
    size_t numberOffspring = qrand()%indexEmptyList.size();
    MediatorFishMotor* mediator = MediatorFishMotor::getInstance();
    switch (typeObject)
    {
    case ObjectType::SHARK_FEMALE:
    {
        for(auto i=0;i<static_cast<int>(numberOffspring);i++)
        {
            auto indexCellRand = indexEmptyList.begin() + qrand()%indexEmptyList.size();
            ObjectType type = qrand()%2?ObjectType::SHARK_MALE:ObjectType::SHARK_FEMALE;
            p_board->setCellNewObject(*indexCellRand,mediator->createObjectGame(type));
            indexEmptyList.erase(indexCellRand);
        }
        break;
    }
    case ObjectType::AMPHIPRION_FEMALE:
    {
        for(auto i=0;i<static_cast<int>(numberOffspring);i++)
        {
            auto indexCellRand = indexEmptyList.begin() + qrand()%indexEmptyList.size();
            ObjectType type = qrand()%2?ObjectType::AMPHIPRION_MALE:ObjectType::AMPHIPRION_FEMALE;
            p_board->setCellNewObject(*indexCellRand,mediator->createObjectGame(type));
            indexEmptyList.erase(indexCellRand);
        }
        break;
    }
    default:
        break;
    }
}

size_t Generator::generatIndex(QList<size_t> indexesList)
{
    if(!indexesList.isEmpty())
    {
        return indexesList.at(qrand()%indexesList.size());
    }
    return UINT64_MAX;
}

Generator::Generator()
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    p_board =MediatorFishMotor::getInstance()->getGameBoard();
}
