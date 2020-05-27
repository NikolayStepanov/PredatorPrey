#ifndef CELL_H
#define CELL_H

#include <objectgame.h>
#include <common.h>

#include <QObject>

class Cell: public QObject
{
    Q_OBJECT
public:
    Cell(QObject *parent = nullptr, size_t index = 0);
    ~Cell();

signals:
    void updatedCell(size_t index);
public:
    bool createObject(ObjectType type);
    //bool setObject(ObjectGame objectGame);
    bool setObject(ObjectGame * objectGame);
    void deleteObject();
    ObjectInf getObjectInf();

    size_t getIndex() const;
    ObjectType getType() const;
    size_t getIdObject() const;
    ObjectGame *getObject() const;

private:
    size_t m_index;
    ObjectGame* p_object;
};

#endif // CELL_H
