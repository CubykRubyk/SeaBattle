#ifndef STATISTICA_H
#define STATISTICA_H

#include <QObject>
#include "comun.h"

//clasa statisticii corabiilor si pt determinarea invingatorului
class Statistica : public QObject
{
    Q_OBJECT
private:
    int myShips[4]; //statistica corabiilor mele, myShips[i]-numarului corabiilor intregi cu marimea i+1
    int enemyShips[4]; //statistica corabiilor dusmanului
public:
    explicit Statistica(QObject *parent = 0);

signals:
    void gameOver(PLAYERS pl);

public slots:
    void corabieDistrusa(PLAYERS pl,int size); //stergerea corabiei din statistica
    int  statisticaCorabii(PLAYERS pl, int size); //obtinerea statisticii despre corabii de marimea size
    void verificaStatus(); //verificam finisarea jocului
};

#endif // STATISTICA_H
