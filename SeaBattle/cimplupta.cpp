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
   QPainter desen(this);
    QPen creion; // pt conturul obiectelor
    creion.setColor(Qt::darkCyan);
    creion.setWidth(3);
    desen.setPen(creion);
    //desenam conturul cimpului
    desen.drawRect(CIMP_OFFSET,CIMP_OFFSET,mar_cimp-2*CIMP_OFFSET,mar_cimp-2*CIMP_OFFSET);//patratul principal
    //grid-ul
    for(int i=CIMP_OFFSET+CELULA; i <= (mar_cimp-CIMP_OFFSET-CELULA); i+=CELULA)
        desen.drawLine(CIMP_OFFSET,i,mar_cimp-CIMP_OFFSET,i); //liniile verticale
     for(int i=CIMP_OFFSET+CELULA; i <= (mar_cimp-CIMP_OFFSET-CELULA); i+=CELULA)
         desen.drawLine(i,CIMP_OFFSET,i,mar_cimp-CIMP_OFFSET); //liniile orizontale
     QFont font;
     font.setPixelSize(15);
     desen.setFont(font);
     creion.setColor(Qt::black);
     creion.setWidth(2);
     desen.setPen(creion);
     for(int i = 0; i<10;i++)
         desen.drawText(0,CIMP_OFFSET+i*CELULA+18,QString::number(i+1)); //desenam cifrele

     for(int i = 0; i<10;i++)
         desen.drawText(CIMP_OFFSET+i*CELULA+8,CIMP_OFFSET-5,QString(abc[i])); //desenam literele
     //mai intii desenam toate corabiile inafara de cel activ,pentru ca la deplasarea,
     //sau la conflict,corabia sa se deseneze deasupra la restu
     for(int i = 0; i < corabii.size(); i++)
         if(corabii.at(i) != corabieActiva)
             corabii.at(i)->desenam(&desen);
     //desenm corabia activa sau care conflict
     if(corabieConflict)
         corabieConflict->desenam(&desen);
     else
         if(corabieActiva)
             corabieActiva->desenam(&desen);
     //desenam statuturile celulelor deasupra la tot
     for(int i = 0; i < 10; i++)
     {
         for(int j = 0; j < 10; j++)
         {
             switch(cimp[i][j])
             {
             case EMPTY:
                 break;
             case KILLED:
             case DAMAGED:
                 deseneazaRanit(&desen,j,i);
                 break;
             case DOT:
                 deseneazaPunct(&desen,j,i);
                 break;
             }
         }
     }
}

void CimpLupta::deseneazaPunct(QPainter *desen, int x, int y)
{
    QPen creion;
    QBrush periuta;
    creion.setColor(Qt::black);
    desen->setPen(creion);
    periuta.setStyle(Qt::SolidPattern);
    periuta.setColor(Qt::black);
    desen->setBrush(periuta);
    desen->drawEllipse(QPoint(CIMP_OFFSET+x*CELULA+CELULA/2,CIMP_OFFSET+y*CELULA+CELULA/2),PUNCT,PUNCT); //desenam punctul
}

void CimpLupta::deseneazaRanit(QPainter *desen, int x, int y)
{
    QPen creion;
    creion.setColor(Qt::red);
    creion.setWidth(2);
    desen->setPen(creion);
    //desenam un X din 2 linii
    desen->drawLine(CIMP_OFFSET + x * CELULA, CIMP_OFFSET + y * CELULA, CIMP_OFFSET + (x + 1) * CELULA, CIMP_OFFSET + (y + 1) * CELULA);
    desen->drawLine(CIMP_OFFSET + x * CELULA, CIMP_OFFSET + (y + 1) * CELULA, CIMP_OFFSET + (x + 1) * CELULA, CIMP_OFFSET + y  * CELULA);
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
