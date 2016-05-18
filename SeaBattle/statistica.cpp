#include "statistica.h"

Statistica::Statistica(QObject *parent) : QObject(parent)
{
    //initializam numarul de corabii pt mine si pentru dusman
    myShips[0] = CORABIE1_AMOUNT;
    myShips[1] = CORABIE2_AMOUNT;
    myShips[2] = CORABIE3_AMOUNT;
    myShips[3] = CORABIE4_AMOUNT;

    enemyShips[0] = CORABIE1_AMOUNT;
    enemyShips[1] = CORABIE2_AMOUNT;
    enemyShips[2] = CORABIE3_AMOUNT;
    enemyShips[3] = CORABIE4_AMOUNT;
}

void Statistica::corabieDistrusa(PLAYERS pl, int size)
{
    switch (pl) {
    case ME: //corabiile mele
        myShips[size-1]--;
        break;
    case ENEMY: //corabiile oponent
        enemyShips[size-1]--;
        break;
    }
}

int Statistica::statisticaCorabii(PLAYERS pl, int size)
{
   switch(pl)
   {
   case ME:
       return myShips[size-1];
   case ENEMY:
       return enemyShips[size-1];
   }
}

void Statistica::verificaStatus()
{
   //daca toate corabiile mele sau ale oponentului sunt distruse
   //emitem semnal despre finisarea jocului
    if(myShips[0]==0 && myShips[1]==0 && myShips[2]==0 && myShips[3]==0)
            emit gameOver(ENEMY);
    if(enemyShips[0]==0 && enemyShips[1]==0 && enemyShips[2]==0 && enemyShips[3]==0)
            emit gameOver(ME);

}

