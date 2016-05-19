#ifndef CORABIE_H
#define CORABIE_H


#include "comun.h"
#include <QPoint>
#include <QPainter>
#include <QList>

class Corabie
{
private:
    QPoint drawPoint;           //punctul desenarii coltului sus-stinga al corabiei
    int size;                   //marimea
    direction dir;              //directia ORIZONTA?VERTICAL
    bool activ;                 //statutul corabiei activ/neactiv
    bool conflict;              //conflict in aranjarea corabiilor
    bool distrus;               //distrus / intreg
    int ranit;                  //numarul "ranilor"
    QList<Corabie*>*corabii;    //lista de pointeri la alte corabii (pentru determinarea conflicteor)
public:
    Corabie(QPoint _drawPoint, int _size, direction _dir, QList<Corabie*>* _corabii);
    void desenam(QPainter *desen);          //functia pentru desenarea corabiilor
    void umbraDesen(QPainter *desen);       //functia pentru desenarea umbrei la miscarea corabiei
    bool peCorabie(QPoint p);               //daca punctul apartine corabiei
    void yesActiv(bool a);                  //activam corabia
    void yesConflict(bool c);               //activam conflictul la aranjament
    void deplaseaza(int deltax, int deltay);//deplasarea corabiei
    void deplaseazaIn(int x, int y);        //deplasarea corabiei in punctul (x,y)
    QPoint pozitia();                       //functia intoarce coordonatele virfului stinga-sus
    int dimensiunea();                      //functia returneaza dimensiunea corabiei
    direction directie();                   //orientarea corabiei
    void roteste();                         //rotirea corabiei
    bool verifica_conflict();               //verificarea daca este conflict
    bool damageCorabie();                   //
};

#endif // CORABIE_H
