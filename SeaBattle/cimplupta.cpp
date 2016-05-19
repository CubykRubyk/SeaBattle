#include "cimplupta.h"
#include <QMouseEvent>
#include <math.h>
#include <time.h>
#include <iostream>
#include <QtMultimedia/QSound>

//constructor

CimpLupta::CimpLupta(GAME_STATUS *_gstatus, Statistica *_statLupta, QWidget *parent) : QWidget(parent)
{
   gstatus = _gstatus;
   statLupta = _statLupta;
   mar_cimp = CELULA*10+2*CIMP_OFFSET; //marimea widget-ului = 10 celule + 2 distante de la margine
   corabieActiva = NULL;
   corabieConflict = NULL;
   miscCorabie = false;
   modAmplasare = false;
   modLupta = false;
   clicked = false;

   for(int i = 0; i < 10; i++)
   {
       for(int j = 0; j < 10; j++)
       {
           cimp[i][j] = EMPTY;
       }
   }
   setFixedSize(mar_cimp,mar_cimp);
      abc[0]='A';
      abc[1]='B';
      abc[2]='C';
      abc[3]='D';
      abc[4]='E';
      abc[5]='F';
      abc[6]='G';
      abc[7]='H';
      abc[8]='I';
      abc[9]='J';
}

void CimpLupta::paintEvent(QPaintEvent *event)
{
  
}

void CimpLupta::deseneazaPunct(QPainter *desen, int x, int y)
{
   
}

void CimpLupta::deseneazaRanit(QPainter *desen, int x, int y)
{
 
}

void CimpLupta::mousePressEvent(QMouseEvent *event)
{
    
       }


void CimpLupta::mouseMoveEvent(QMouseEvent *event)
       {
          
       }


void CimpLupta::mouseReleaseEvent(QMouseEvent *event)
       {
           
       }


void CimpLupta::rotatieCorabieActiva()
       {
           

void CimpLupta::adaugaCorabiePeCimp(int size)
       {

    
       }


void CimpLupta::elimineCorabieCimp()
       {
           


void CimpLupta::reset()
       {
       }


void CimpLupta::genereazaRandom()
       {
           
       }


void CimpLupta::setModAmplasare(bool mode)
       {
         
       }


void CimpLupta::setModLupta(bool mode)
       {
           
       }


void CimpLupta::verificaMiscare(int x, int y)
       {
           


void CimpLupta::verificaMiscareRaspuns(int x, int y, CELL_STATUS st, QPoint pos, int size, direction dir)
       {
           /
       }


void CimpLupta::puncteCorabieDistrusa(QPoint pos, int size, direction dir)
       {
           
       }


void CimpLupta::corabieNeactiva()
      
       }
