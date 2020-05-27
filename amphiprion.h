#ifndef AMPHIPRION_H
#define AMPHIPRION_H

#include <QObject>
#include <QTimer>

#include <fish.h>
#include<climits>

class Amphiprion:public QObject, public Fish
{
    Q_OBJECT
public:
    Amphiprion(bool gender);

private slots:
    void slotGiveOffspring();

public:
    ObjectType getType() override;

    bool reproduction() override;
    bool eat() override;
    void move() override;
private:
    QTimer * m_timerGiveOffspring;
};

#endif // AMPHIPRION_H
