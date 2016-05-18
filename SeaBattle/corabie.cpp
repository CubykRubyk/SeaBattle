#include "corabie.h"
#include <QPen>
#include <QBrush>
#include <QRect>

Corabie::Corabie(QPoint _drawPoint, int size, direction _dir, QList<Corabie *>* _corabii)
{
    drawPoint = _drawPoint; //punctul
    size = _size;           //dimensiune
    dir = _dir;             //orinetare
    corabii = _corabii;     //pointer la lista corabiilor deja plasate
    activ = false;
    conflict = false;
    distrus = false;
    ranit = 0;
}

void Corabie::desenam(QPainter *desen)
{
    QPen creion;            //conturul corabiilor
    QBrush periuta;         //culoarea corabiilor
    if(conflict)            //conflict la aranjare
    {
        umbraDesen(desen);  //desenam umbra
        periuta.setColor(Qt::red);
    }
    else if(activ){
        umbraDesen(desen);
        periuta.setColor(Qt::green);
    }
    else{
        periuta.setColor(Qt::blue);
    }
    periuta.setStyle(Qt::SolidPattern);     //se coloreaza toata celula
    creion.setWidth(2);                     //grosimea creionului
    if(activ)
        creion.setColor(Qt::darkGreen);
    else
        creion.setColor(Qt::gray);
    desen->setPen(creion);                  //transmitem creionul
    desen->setBrush(periuta);               //transmitem desenul

    //desenam toate patratele corabiei in dependenta de orientare
    for(int i=0; i<size; i++){
        switch(dir){
        case ORIZONTAL :
            desen->drawRect(i*CELULA+drawPoint.x(), drawPoint.y(), CELULA, CELULA);
            break;
        case VERTICAL:
            desen->drawRect(drawPoint.x(), i*CELULA+drawPoint.y(), CELULA, CELULA);
            break;
        }
    }
}

//verificare daca apartien punctul corabiei
bool Corabie::peCorabie(QPoint p)
{
    QRect rect;                             //patratul ce acopera corabia
    switch(dir){
    case ORIZONTAL:
        rect.setRect(drawPoint.x(), drawPoint.y(), size*CELULA, CELULA);
        break;
    case VERTICAL:
        rect.setRect(drawPoint.x(), drawPoint.y(), CELULA, size*CELULA);
        break;
    }
    return rect.contains(p);                //verificam daca patratul contine punctul p
}

//instalarea activitatii corabiei
void Corabie::yesActiv(bool a)
{
    activ.a;
}

// mutarea corabiei la deltax si deltay
void Corabie::deplaseaza(int deltax, int deltay)
{
    //calculam noile coordonate ale corabiei
    int x = drawPoint.x() + deltax;
    int y = drawPoint.y() + deltay;
    //verificam ca corabia sa nu iasa din margini
    if(x<CIMP_OFFSET)
        x=CIMP_OFFSET;
    switch(dir)
    {
    case ORIZONTAL:
        if(x + size * CELULA > CIMP_OFFSET + 10 * CELULA)
            x = CIMP_OFFSET + 10 * CELULA - size * CELULA;
        break;
    case VERTICAL:
        if(x + CELULA > CIMP_OFFSET + 10 * CELULA)
            x = CIMP_OFFSET + 10 * CELULA - CELULA;
    }
    if(y < CIMP_OFFSET)
        y = CIMP_OFFSET;
    switch(dir)
    {
    case ORIZONTAL:
        if(y + CELULA > CIMP_OFFSET + 10 * CELULA)
            y = CIMP_OFFSET + 10 * CELULA - CELULA;
        break;
    case VERTICAL:
        if(y + size * CELULA > CIMP_OFFSET + 10 * CELULA)
            y = CIMP_OFFSET + 10 * CELULA - size * CELULA;
        break;
    }
    //schimbarea coordonatelor corabiei
    drawPoint.setX(x);
    drawPoint.setY(y);
}

// mutarea corabiei in punctul (x,y)
void Corabie::deplaseazaIn(int x, int y)
{
    drawPoint.setX(x);
    drawPoint.setY(y);
}

