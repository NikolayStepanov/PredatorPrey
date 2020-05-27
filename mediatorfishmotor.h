#ifndef MEDIATORFISHMOTOR_H
#define MEDIATORFISHMOTOR_H


#include <bootstrapper.h>
#include <fish.h>
#include <shark.h>
#include <amphiprion.h>
#include <rock.h>

#include <generator.h>

#include <QList>

#include <gameboard.h>

class MediatorFishMotor: public QObject
{
    Q_OBJECT
public:
    static MediatorFishMotor *getInstance();
    ~MediatorFishMotor();

    //Board
    QList<Cell> getNeighboringCells();
    QList<ObjectInf> getNeighboringObjectInf(size_t id);
    QList<size_t> getEmptyNeighboringCell(size_t id);
    ObjectInf getObjectInfForId(size_t objectId);

    void moveObject(size_t objectId, size_t indexNext);
    void deleteObject(ObjectInf objectInf);

    //game
    ObjectGame *createObjectGame(ObjectType type);

    //gamemodel
    size_t getRowCountBoard() const;
    size_t getColumnCountBoard() const;
    ObjectInf getObjectInf(const QModelIndex index) const;
    void nextStep();
    QPoint getPointForIndex(size_t index);

    //generator
    GameBoard *getGameBoard();
    void generationGame();
    Generator *getGenerator();

    //fish
    QList<Fish *> getAllFish();

signals:
    void ubdatedData(size_t indexCell);

public slots:
    void slotUpdatedData(size_t index);
    void deleteObjectForId(size_t objectId);

private:
    MediatorFishMotor(QObject *parent = 0);
    MediatorFishMotor( const MediatorFishMotor& );
    MediatorFishMotor& operator=( MediatorFishMotor& );

private:
    static constexpr int width = 16;
    static constexpr int height = 8;

    static MediatorFishMotor * p_instance;

    Bootstrapper * p_bootstrap;

    GameBoard *p_gameBoard;
    Generator *p_generator;

    QList <ObjectGame*> m_objectsGameList;

    QList <Fish*> m_fishList;
    QList <Shark*> m_sharkList;
    QList <Amphiprion*> m_amphiprionList;
};

#endif // MEDIATORFISHMOTOR_H
