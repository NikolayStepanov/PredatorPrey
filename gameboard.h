#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>

#include <common.h>
#include <cell.h>

class GameBoard: public QObject
{
    Q_OBJECT
public:
    GameBoard(QObject *parent = 0, size_t width =0 , size_t height = 0);
    ~GameBoard();

    bool moveObject(size_t objectId, size_t indexNext);
    void deleteObject(size_t objectId);
    ObjectGame *getObjectGame(size_t objectId);

    bool setCellNewObject(size_t index, ObjectGame * object);

    ObjectInf getCellObjectInf(size_t index);
    ObjectInf getObjectInf(size_t objectId);
    QList<ObjectInf> getObjectsInf();
    QList<ObjectInf> getNeighboringObjectInf(size_t index);
    QList<ObjectGame *> getObjectsGameForIndices(QList<size_t> objectIndices);
    QList<ObjectGame *> getObjectsGameForId(QList<size_t> objectsId);
    size_t getIndexCellForObjectId(const size_t id) const;

    Cell* getCell(size_t index);

    //index convector
    bool areCellCoordinatesValid(const QPoint &coordinates) const;
    bool areCellIndexValid(const size_t cellIndex);

    QPoint cellCoordinatesFromIndex(const size_t cellIndex) const;
    size_t cellIndex(const QModelIndex index) const;
    size_t cellIndex(const QPoint &coordinates) const;

    //get private
    size_t getHeight() const;
    size_t getWidth() const;
    size_t getSize() const;
    QVector<Cell *> getAllCells();
    
private:
    void deleteBoard();
    void createEmptyBoard();

private:
    QVector<Cell*> m_cellsContainer;

    size_t m_width;
    size_t m_height;

    size_t m_size;
};

#endif // GAMEBOARD_H
