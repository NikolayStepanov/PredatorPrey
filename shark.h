#ifndef SHARK_H
#define SHARK_H

#include <fish.h>
#include <QObject>

#include <QTimer>
#include <QTime>

class Shark:  public QObject,public Fish
{
    Q_OBJECT
public:
    Shark(bool gender);
    ~Shark();


private slots:
    void slotGiveOffspring();
    void slotDie();

signals:
    void die(size_t);

public:
    ObjectType getType() override;

    bool reproduction() override;
    bool eat() override;
    void move() override;
private:
    QTimer * m_timerGiveOffspring;
    QTimer * m_timerDeath;
};

#endif // SHARK_H
