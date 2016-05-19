#ifndef CIMPLUPTA_H
#define CIMPLUPTA_H

#include <QWidget>
#include <QPainter>
#include <QList>

#include "corabie.h"
#include "comun.h"
#include "statistica.h"

//clasa cimpului de lupta

class CimpLupta : public QWidget
{
    Q_OBJECT
private:
    char abc[10]; //pt A-B-C-D-E-F
    int mar_cimp; //marimea cimpului
    CELL_STATUS cimp[10][10]; //matricea starilor celulei

    QList<Corabie*>corabii; //corabii pe cimp
    Corabie *corabieActiva; //pinter la corabia activa
    Corabie *corabieConflict; //pointer la corabia cu conflict

    QPoint ultimPunct; //punctul precedent de pe cimp,in care a fost chemat mouseMoveEvent
    bool miscCorabie; //true daca corabiile se amplaseaza pe cimp

    bool modAmplasare; //regimul amplasarii
    bool modLupta; //regim de joc

    GAME_STATUS *gstatus; //pointer la statutul curent al jocului (READY, YOUR_TURN, ENEMY_TURN)
    Statistica *statLupta; //pointer la statistica jocului
    bool clicked; //click pe cimp

public:
    explicit CimpLupta(GAME_STATUS *_gstatus,Statistica *_statLupta,QWidget *parent = 0);//constructorul
    void setModAmplasare(bool mod); //regimul amplasare
    void setModLupta(bool mod); //regim lupta

signals:
    void corabieActivata(bool val,int size); //semnal despre corabia de pe cimp aleasa de utilizator
    void corabieConflicta(bool val); //semnal despre aparitia/rezolvarea conflictului
    void celulaClicked(int x,int y); //semnal despre click in celula de pe cimp
    void miscareRaspuns(int x,int y,CELL_STATUS st,Corabie *s); //rs la miscarea oponentului
    void updateStatusLabel(); //semnal despre necesitatea unui update a statisticii

public slots:
    void rotatieCorabieActiva(); //rotatie corabie
    void adaugaCorabiePeCimp(int size); //adaugarea corabiei pe cimp
    void elimineCorabieCimp(); //stergerea corabiei
    void reset();
    void genereazaRandom();
    void deseneazaPunct(QPainter *desen,int x,int y); //desneaza punctul
    void deseneazaRanit(QPainter *desen,int x,int y); //deseneaza atunci cind -ranit
    void verificaMiscare(int x,int y); //verifica miscarea oponentului
    void verificaMiscareRaspuns(int x,int y,CELL_STATUS st, QPoint poz,int size,direction dir); //verifica raspunsul oponentului la miscare
    void puncteCorabieDistrusa(QPoint pos,int size,direction dir); //punctele imprejurul corabiei distruse
    void corabieNeactiva(); //deactivarea corabiei

protected:
    void paintEvent(QPaintEvent *event); //evenimentul desenarii cimpului
    void mousePressEvent(QMouseEvent *event);//evenimentul click pe cimp
    void mouseMoveEvent(QMouseEvent *event);//evenimentul deplasarii cursorului pe cimp
    void mouseReleaseEvent(QMouseEvent *event);//evenimentul eliberarii butonului mouse
};

#endif // CIMPLUPTA_H
