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
      if(modAmplasare)
    {
        if(event->button() == Qt::LeftButton) //daca este click sting
        {
            //daca click-ul sa efectuat in locul unde nu era nici o corabie
            //corabie curenta o setam ca neactiva
            if(corabieActiva)
                corabieActiva->yesActiv(false);
            corabieActiva = NULL;
            //anuntam meniul amplasarii despre faptul ca corabie
            //nu mai este activa (se deactiveaza butoanele delete si rotate)
            emit corabieActivata(false,-1);
            //parcurgem lista de corabii si verificam daca pozitia curenta
            //a cursorului unei corabii
            for(int i = 0; i<corabii.size(); i++)
                if(corabii.at(i)->peCorabie(event->pos())) //verificare
                { //conflict
                    if(corabieConflict)
                    {
                        if(corabieConflict == corabii.at(i)) //am facut click pe corabia care conflicteaza
                        {
                            //setam corabia ca activa
                            corabieActiva = corabii.at(i);
                            corabieActiva->yesActiv(true);
                            // anuntam ca corabia este activa
                            emit corabieActivata(true,corabieActiva->dimensiunea());
                            //deplasarea corabiei
                            miscCorabie = true;
                            //memoram pozitia cursorului
                            ultimPunct = event->pos();
                            //setam corabia care o deplasam, fara conflict
                            if(corabieConflict)
                                corabieConflict->yesConflict(false);
                            corabieConflict = NULL;
                            break;
                        }
                    }
                    else //daca nu este conflict
                    {
                        //activam corabia pe care am facut click
                        corabieActiva = corabii.at(i);
                        corabieActiva->yesActiv(true);
                        emit corabieActivata(true,corabieActiva->dimensiunea());
                        //deplasam corabia
                        miscCorabie = true;
                        //memoram pozitia cursorului
                        ultimPunct = event->pos();
                        break;
                    }
                }
        }
        if(event->button() == Qt::RightButton) //click drept
        {
                   //in caz ca am dat click unde nui corabie,setam corabia curenta neactiva
                   if(corabieActiva)
                       corabieActiva->yesActiv(false);
                   corabieActiva = NULL;
                   //deactivam butoanele delete si rotate
                   emit corabieActivata(false, -1);
                   //verificam daca nu este cursorul pe corabie
                   for(int i = 0 ; i < corabii.size() ; i++)
                       if(corabii.at(i)->peCorabie(event->pos())) // verificare
                       {
                          //corabie conflict
                           if(corabieConflict)
                           {
                               if(corabieConflict == corabii.at(i)) // click-conflict
                               {
                                   // activam corabie
                                  corabieActiva = corabii.at(i);
                                  corabieActiva->yesActiv(true);
                                   // corabie activata
                                   emit corabieActivata(true, corabieActiva->dimensiunea());
                                   corabieActiva->roteste(); // rotim corabia activa
                                   // verificam daca dupa rotire nu a aparut conflict
                                   if(corabieActiva->verifica_conflict())
                                   {
                                       // corabie click conflict
                                      corabieConflict = corabieActiva;
                                      corabieConflict->yesConflict(true);
                                       // anuntam despre conflict
                                       emit corabieConflicta(true);
                                   }
                                   else
                                   {
                                       if(corabieConflict)
                                          corabieConflict->yesConflict(false);
                                      corabieConflict = NULL;
                                       // anuntam despre lipsa conflictului
                                       emit corabieConflicta(false);
                                   }
                                   break; // iesire din ciclu
                               }
                           }
                           else // daca lipseste conflictul
                           {
                               // activam corabia
                               corabieActiva = corabii.at(i);
                               corabieActiva->yesActiv(true);
                               //corabie activata
                               emit corabieActivata(true, corabieActiva->dimensiunea());
                               corabieActiva->roteste(); // rotim
                               // verificam aparitia conflictului
                               if(corabieActiva->verifica_conflict())
                               {
                                  corabieConflict = corabieActiva;
                                  corabieConflict->yesConflict(true);
                                   emit corabieConflicta(true);
                               }
                               else
                               {
                                   if(corabieConflict)
                                      corabieConflict->yesConflict(false);
                                  corabieConflict = NULL;
                                   // lipsa conflict
                                   emit corabieConflicta(false);
                               }
                               break;
                           }
                       }
               }
           }

           //daca cimpul e in regimul de lupta si e miscarea mea
           //in corpul if,variabila clicked se seteaza ca true
           //ca pina la venirea raspunsului la miscare,clickul sa nu se mai execute
           //clicked va fi din nou false,cind va fi miscarea mea
           if(clicked == false && modLupta && *gstatus == YOUR_TURN)
           {
               int x, y;
               // convertim coordonatele in numerele celulelor
               x = (event->pos().x() - CIMP_OFFSET) / CELULA;
               y = (event->pos().y() - CIMP_OFFSET) / CELULA;
               if(cimp[y][x] == EMPTY) // verificam daca in celula data inca nu am mers
               {
                   clicked = true;
                   emit updateStatusLabel(); // update la statutul miscarii
                   //emitem un semnal ca jucatorul a mers in celula (x,y)
                   //semnalul dat va fi analizat de slotul MainWindow::sendTurn(x,y)
                   //care prin protocolul TCP, va transmite coordonatele la aplicatia oponentului
                   emit celulaClicked(x, y);
               }
           }
           update(); // redesenam cimpul
}


void CimpLupta::mouseMoveEvent(QMouseEvent *event)
       {
           if(modAmplasare)
           {
               int deltax; // decalajul cursorului pe orizontal
               int deltay; // decalaj pe vertical

               //corabia se  deplaseaza doar daca este apasat click
               //miscCorabie se seteaza true la apasarea click,si false cind nu este apasat
               if(miscCorabie)
               {
                   // daca cursorul este in afara cimpului,pe orizontala,corabia nu trebuie sa se deplaseze
                   if(event->pos().x() < CIMP_OFFSET || event->pos().x() > CIMP_OFFSET + 10 * CELULA)
                       deltax = 0;
                   else
                    //calculam decalajul cursorului dupa ultima chemare a mousePressEvent sau mouseMoveEvent
                       deltax = event->pos().x() - ultimPunct.x();
                   // daca cursorul este in afara cimpului,pe verticala,corabia nu trebuie sa se deplaseze
                   if(event->pos().y() <CIMP_OFFSET || event->pos().y() > CIMP_OFFSET + 10 * CELULA)
                       deltay = 0;
                   else
                       //calculam decalajul cursorului dupa ultima chemare a mousePressEvent sau mouseMoveEvent
                       deltay = event->pos().y() - ultimPunct.y();
                   corabieActiva->deplaseaza(deltax, deltay); // deplasam corabia
                   ultimPunct = event->pos(); // memoram pozita actuala a cursorului,pentru calculul decalajului urmator
               }
               update(); // redesenam cimpul
           }
       }


void CimpLupta::mouseReleaseEvent(QMouseEvent *event)
       {
            if(modAmplasare)
           {
               if(miscCorabie)
               {
                   int x, y;
                   //la deplasarea corabiei si eliberarea butonului mouse,pozitia curenta a corabiei poate sa nu coincida
                   //exact cu amplasarea celulelor,de aceea e necesar de calculat celulele cele mai apropiate in care poate
                   //fi amplasata corabie
                   int up,bottom, rigth, left;
                   left = CIMP_OFFSET + ((corabieActiva->pozitia().x() - CIMP_OFFSET) / CELULA) * CELULA;
                   rigth = CIMP_OFFSET + ((corabieActiva->pozitia().x() - CIMP_OFFSET) / CELULA) * CELULA + CELULA;
                   up = CIMP_OFFSET + ((corabieActiva->pozitia().y() - CIMP_OFFSET) / CELULA) * CELULA;
                   bottom = CIMP_OFFSET + ((corabieActiva->pozitia().y() - CIMP_OFFSET) / CELULA) * CELULA + CELULA;
                   if( corabieActiva->pozitia().x() - left <= CELULA / 2) // daca corabia e mai aproape de celula dreapta sau stinga
                       x = left;
                   else
                       x = rigth;
                   if(corabieActiva->pozitia().y() - up <= CELULA / 2) //mai aproape de celula de sus sau jos
                       y = up;
                   else
                       y = bottom;
                   corabieActiva->deplaseazaIn(x, y); // deplasam in celula gasita
                   // daca este conflict
                   if(corabieActiva->verifica_conflict())
                   {
                       // corabia pe care am facut click este activa
                      corabieConflict = corabieActiva;
                      corabieConflict->yesConflict(true);

                       emit corabieConflicta(true);
                   }
                   else
                   {
                       if(corabieConflict)
                          corabieConflict->yesConflict(false);
                      corabieConflict = NULL;
                       // lipsa conflictului
                       emit corabieConflicta(false);
                   }
               }
               miscCorabie = false; // deplasarea e finisata
               update(); // redesenam cimpul
           }
       }


void CimpLupta::rotatieCorabieActiva()
       {
         // daca este corabie activa,o rotim
           if(corabieActiva)
               corabieActiva->roteste();
           // verificam conflict
           if(corabieActiva->verifica_conflict())
           {

              corabieConflict = corabieActiva;
              corabieConflict->yesConflict(true);
              emit corabieConflicta(true);
           }
           else
           {
               if(corabieConflict)
                  corabieConflict->yesConflict(false);
              corabieConflict = NULL;
                  emit corabieConflicta(false);
           }
           update();
       }
           

void CimpLupta::adaugaCorabiePeCimp(int size)
       {
//corabia noua se amplaseaza vetical,incepind cu virful stinga-sus al cimpului
           Corabie* cur = new Corabie(QPoint(CIMP_OFFSET, CIMP_OFFSET), size, VERTICAL, &corabii);
           corabii.append(cur); // adaugam o corabie noua in lista
           // verificam conflict
           if(cur->verifica_conflict())
           {
              corabieConflict = cur;
              corabieConflict->yesConflict(true);
              emit corabieConflicta(true);
           }
           else
           {
               if(corabieConflict)
                  corabieConflict->yesConflict(false);
              corabieConflict = NULL;
                  emit corabieConflicta(false);
           }

           if(corabieActiva)
               corabieActiva->yesActiv(false);
           // setam ca activa corabia adaugata
           corabieActiva = cur;
           corabieActiva->yesActiv(true);
           emit corabieActivata(true, corabieActiva->dimensiunea());
           update();
    
       }


void CimpLupta::elimineCorabieCimp()
       {
         //parcurgem lista si gasim corabia activa
           for(int i = 0 ; i < corabii.size() ; i++)
               if(corabii.at(i) == corabieActiva) // verificare
               {
                   corabii.removeAt(i); // stergem din lista
                   if(corabieActiva == corabieConflict) // daca eliminam corabie conflict,anuntam d
                   {
                      corabieConflict = NULL;
                       emit corabieConflicta(false);
                   }
                   delete corabieActiva; // stergem
                   corabieActiva = NULL;
                   emit corabieActivata(false, -1);
                   break;
               }
           update();
       }
           


void CimpLupta::reset()
       {
         corabieActiva = NULL;
          corabieConflict = NULL;
           modAmplasare = false;
           miscCorabie = false;
           // curatim lista de corabii
           while(corabii.size() != 0)
           {
               Corabie* cur = corabii.first();
               corabii.pop_front();
               delete cur;
           }
       }


void CimpLupta::genereazaRandom()
       {
           reset();
           modAmplasare = true;
           srand(time(NULL)); // initializam generatorul
           direction dir; // orientarea
           Corabie* cur; // pointer la corabia pe care incercam sa o plasam pe cimp
           // pt coordonate2
           int xmod, ymod;
           int x, y;

           // plasam corabiile de o celula
           for( int i = 0 ; i < CORABIE1_AMOUNT ; i++)
           {
              //alegem pozitia pt corabie pina cind nu o sa apara conflict cu corabiile deja plasate
               do
               {
                   // orientarea
                   if(rand() % 2 == 0)
                       dir = VERTICAL;
                   else
                       dir = ORIZONTAL;
                   // alegem celula
                   switch(dir)
                   {
                   case VERTICAL:
                       xmod = 10;
                       ymod = 10 - CORABIE1 + 1;
                       break;
                   case ORIZONTAL:
                       ymod = 10;
                       xmod = 10 - CORABIE1 + 1;
                       break;
                   }
                   // recalculam numarul celulei in coordonate
                   x = (rand() % xmod) * CELULA;
                   y = (rand() % ymod) * CELULA;
                   cur = new Corabie(QPoint(CIMP_OFFSET + x, CIMP_OFFSET + y), CORABIE1, dir, &corabii);
               }
               while(cur->verifica_conflict());// verificarea amplasarii
               corabii.append(cur); // adaugare in lista
           }

           //de 2 celule

           for( int i = 0 ; i < CORABIE2_AMOUNT ; i++)
           {
              //alegem pozitia pt corabie pina cind nu o sa apara conflict cu corabiile deja plasate
               do
               {
                   // orientarea
                   if(rand() % 2 == 0)
                       dir = VERTICAL;
                   else
                       dir = ORIZONTAL;
                   // alegem celula
                   switch(dir)
                   {
                   case VERTICAL:
                       xmod = 10;
                       ymod = 10 - CORABIE2 + 1;
                       break;
                   case ORIZONTAL:
                       ymod = 10;
                       xmod = 10 - CORABIE2 + 1;
                       break;
                   }
                   // recalculam numarul celulei in coordonate
                   x = (rand() % xmod) * CELULA;
                   y = (rand() % ymod) * CELULA;
                   cur = new Corabie(QPoint(CIMP_OFFSET + x, CIMP_OFFSET + y), CORABIE2, dir, &corabii);
               }
               while(cur->verifica_conflict());// verificarea amplasarii
               corabii.append(cur); // adaugare in lista
           }

           // plasam corabiile de 3 celule
           for( int i = 0 ; i < CORABIE3_AMOUNT ; i++)
           {
              //alegem pozitia pt corabie pina cind nu o sa apara conflict cu corabiile deja plasate
               do
               {
                   // orientarea
                   if(rand() % 2 == 0)
                       dir = VERTICAL;
                   else
                       dir = ORIZONTAL;
                   // alegem celula
                   switch(dir)
                   {
                   case VERTICAL:
                       xmod = 10;
                       ymod = 10 - CORABIE3 + 1;
                       break;
                   case ORIZONTAL:
                       ymod = 10;
                       xmod = 10 - CORABIE3 + 1;
                       break;
                   }
                   // recalculam numarul celulei in coordonate
                   x = (rand() % xmod) * CELULA;
                   y = (rand() % ymod) * CELULA;
                   cur = new Corabie(QPoint(CIMP_OFFSET + x, CIMP_OFFSET + y), CORABIE3, dir, &corabii);
               }
               while(cur->verifica_conflict());// verificarea amplasarii
               corabii.append(cur); // adaugare in lista
           }

           // plasam corabiile de 4 celule
           for( int i = 0 ; i < CORABIE4_AMOUNT ; i++)
           {
              //alegem pozitia pt corabie pina cind nu o sa apara conflict cu corabiile deja plasate
               do
               {
                   // orientarea
                   if(rand() % 2 == 0)
                       dir = VERTICAL;
                   else
                       dir = ORIZONTAL;
                   // alegem celula
                   switch(dir)
                   {
                   case VERTICAL:
                       xmod = 10;
                       ymod = 10 - CORABIE4 + 1;
                       break;
                   case ORIZONTAL:
                       ymod = 10;
                       xmod = 10 - CORABIE4 + 1;
                       break;
                   }
                   // recalculam numarul celulei in coordonate
                   x = (rand() % xmod) * CELULA;
                   y = (rand() % ymod) * CELULA;
                   cur = new Corabie(QPoint(CIMP_OFFSET + x, CIMP_OFFSET + y), CORABIE4, dir, &corabii);
               }
               while(cur->verifica_conflict());// verificarea amplasarii
               corabii.append(cur); // adaugare in lista
           }

           update();
       }


void CimpLupta::setModAmplasare(bool mode)
       {
           modAmplasare = mode;
       }


void CimpLupta::setModLupta(bool mode)
       {
           modLupta = mode;
       }


void CimpLupta::verificaMiscare(int x, int y)
       {

       }
           


void CimpLupta::verificaMiscareRaspuns(int x, int y, CELL_STATUS st, QPoint pos, int size, direction dir)
       {
           
       }


void CimpLupta::puncteCorabieDistrusa(QPoint pos, int size, direction dir)
       {
           int x1, x2, y1, y2;
           // coordonatele celulelor care inconjoara corabiile
           int x = (pos.x() - CIMP_OFFSET) / CELULA;
           int y = (pos.y() - CIMP_OFFSET) / CELULA;
           switch(dir)
           {
               case ORIZONTAL:
               {
                   x1 = x - 1 >= 0 ? x - 1 : 0;
                   y1 = y - 1 >= 0 ? y - 1 : 0;
                   x2 = x + size <= 9 ? x + size : 9;
                   y2 = y + 1  <= 10 ? y + 1 : 9;
                   break;
               }
               case VERTICAL:
               {
                   x1 = x - 1 >= 0 ? x - 1 : 0;
                   y1 = y - 1 >= 0 ? y - 1 : 0;
                   x2 = x + 1  <= 9 ? x + 1 : 9;
                   y2 = y + size <= 9? y + size : 9;
                   break;
               }
           }

           // starea celulelor inconjuratoare
           for(int i = x1 ; i <= x2 ; i++)
               if(cimp[y1][i] == EMPTY)
                   cimp[y1][i] = DOT;
           for(int i = x1 ; i <= x2 ; i++)
               if(cimp[y2][i] == EMPTY)
                   cimp[y2][i] = DOT;
           for(int i = y1 ; i <= y2 ; i++)
               if(cimp[i][x1] == EMPTY)
                   cimp[i][x1] = DOT;
           for(int i = y1 ; i <= y2 ; i++)
               if(cimp[i][x2] == EMPTY)
                   cimp[i][x2] = DOT; 
       }


void CimpLupta::corabieNeactiva()
{
       if(corabieActiva)
               corabieActiva->yesActiv(false);
           corabieActiva = NULL;
           if(corabieConflict)
              corabieConflict->yesConflict(false);
          corabieConflict = NULL;
       }
