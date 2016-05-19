#include "corabie.h"
#include <QPen>
#include <QBrush>
#include <QRect>

Corabie::Corabie(QPoint _drawPoint, int _size, direction _dir, QList<Corabie *>* _corabii)
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
    activ=a;
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

//functia returneaza coordonatele coltului sus-stinga
QPoint Corabie::pozitia()
{
    return drawPoint;
}

//functia de desenarea a umbrei corabiei in caz de miscare
void Corabie::umbraDesen(QPainter* desen)
{
    QPen creion;                                    // conturul figurilor
    QBrush periuta;                                 // umplerea figurilor
    bool intersectie = verifica_conflict();         // verificarea corabiei daca intra in conflict cu alta
    creion.setWidth(0);                             // definim latimea creionului
    if(intersectie)                                 // daca se intersecteaza
        periuta.setColor(QColor(255, 0, 0, 150));   // definim culoarea periutei
    else
        periuta.setColor(QColor(255, 255, 0, 150)); // definim culoarea periutei
    periuta.setStyle(Qt::SolidPattern);             // definim stilui colorari figurii (SolidPattern - model solid)
    desen->setPen(creion);                          // transmitem creionul spre desenare
    desen->setBrush(periuta);                       // transmitem periuta spre desenare
    // depistam umbrele asemenea
    int x, y;
    int up,bottom, rigth, left;
    left = CIMP_OFFSET + ((drawPoint.x() - CIMP_OFFSET) / CELULA) * CELULA;
    rigth = CIMP_OFFSET + ((drawPoint.x() - CIMP_OFFSET) / CELULA) * CELULA + CELULA;
    up = CIMP_OFFSET + ((drawPoint.y() - CIMP_OFFSET) / CELULA) * CELULA;
    bottom = CIMP_OFFSET + ((drawPoint.y() - CIMP_OFFSET) / CELULA) * CELULA + CELULA;
    if(drawPoint.x() - left <= CELULA / 2)
        x = left;
    else
        x = rigth;
    if(drawPoint.y() - up <= CELULA / 2)
        y = up;
    else
        y = bottom;
    // desenam umbrele
    switch(dir)
    {
        case ORIZONTAL:                             // corabiile orientate orizontal
        {
            desen->drawRect(x, y, CELULA * size, CELULA);
            creion.setWidth(2);
            if(intersectie)
                creion.setColor(QColor(255, 0, 0, 200));
            else
                creion.setColor(QColor(255, 255, 0, 200));
            periuta.setStyle(Qt::NoBrush);
            desen->setBrush(periuta);
            desen->setPen(creion);
            int x1 = x - CELULA >= CIMP_OFFSET ? x - CELULA : CIMP_OFFSET;
            int y1 = y - CELULA >= CIMP_OFFSET ? y - CELULA : CIMP_OFFSET;
            int x2 = x + (size + 1) * CELULA <= CIMP_OFFSET + 10 * CELULA ? x + (size + 1) * CELULA : CIMP_OFFSET + 10 * CELULA;
            int y2 = y + 2 * CELULA <= CIMP_OFFSET + 10 * CELULA ? y + 2 * CELULA : CIMP_OFFSET + 10 * CELULA;
            desen->drawLine(x1, y1, x1, y2);
            desen->drawLine(x2, y1, x2, y2);
            desen->drawLine(x1, y1, x2, y1);
            desen->drawLine(x1, y2, x2, y2);
            break;
        }
        case VERTICAL:                              // corabiile orientate vertical
        {
            desen->drawRect(x, y, CELULA, CELULA * size);
            creion.setWidth(2);
            if(intersectie)
                creion.setColor(QColor(255, 0, 0, 200));
            else
                creion.setColor(QColor(255, 255, 0, 200));
            periuta.setStyle(Qt::NoBrush);
            desen->setBrush(periuta);
            desen->setPen(creion);
            int x1 = x - CELULA >= CIMP_OFFSET ? x - CELULA : CIMP_OFFSET;
            int y1 = y - CELULA >= CIMP_OFFSET ? y - CELULA : CIMP_OFFSET;
            int x2 = x + 2 * CELULA <= CIMP_OFFSET + 10 * CELULA ? x + 2 * CELULA : CIMP_OFFSET + 10 * CELULA;
            int y2 = y + (size + 1) * CELULA <= CIMP_OFFSET + 10 * CELULA ? y + (size + 1) * CELULA : CIMP_OFFSET + 10 * CELULA;
            desen->drawLine(x1, y1, x1, y2);
            desen->drawLine(x2, y1, x2, y2);
            desen->drawLine(x1, y1, x2, y1);
            desen->drawLine(x1, y2, x2, y2);
            break;
        }
    }
}

//rotirea corabiei
void Corabie::roteste()
{
    // schimbam orientarea corabiei
    if(dir == ORIZONTAL)
        dir = VERTICAL;
    else
        dir = ORIZONTAL;
    // corectam pozitia corabiei ca sa nu iasa din cimp
    switch (dir)
    {
    case ORIZONTAL:
        if(drawPoint.x() + size * CELULA > CIMP_OFFSET + 10 * CELULA)
            drawPoint.setX(CIMP_OFFSET + 10 * CELULA - size * CELULA);
        if(drawPoint.y() + CELULA > CIMP_OFFSET + 10 * CELULA)
            drawPoint.setY(CIMP_OFFSET + 10 * CELULA -  CELULA);
        break;
    case VERTICAL:
        if(drawPoint.y() + size * CELULA > CIMP_OFFSET + 10 * CELULA)
            drawPoint.setY(CIMP_OFFSET + 10 * CELULA - size * CELULA);
        if(drawPoint.x() + CELULA > CIMP_OFFSET + 10 * CELULA)
            drawPoint.setX(CIMP_OFFSET + 10 * CELULA -  CELULA);
        break;
    }
}

//functia de verificare, daca corabia data nu interactioneaza cu alte corabii pe cimp
bool Corabie::verifica_conflict()
{
    bool res = false; // rezultatul, setam initial ca conflictul nu este
    QRect acestPatrat,candidatPatrat;
    int x, y;
    int up,bottom, rigth, left;
    left = CIMP_OFFSET + ((drawPoint.x() - CIMP_OFFSET) / CELULA) * CELULA;
    rigth = CIMP_OFFSET + ((drawPoint.x() - CIMP_OFFSET) / CELULA) * CELULA + CELULA;
    up = CIMP_OFFSET + ((drawPoint.y() - CIMP_OFFSET) / CELULA) * CELULA;
    bottom = CIMP_OFFSET + ((drawPoint.y() - CIMP_OFFSET) / CELULA) * CELULA + CELULA;
    if(drawPoint.x() - left <= CELULA / 2)
        x = left;
    else
        x = rigth;
    if(drawPoint.y() - up <= CELULA / 2)
        y = up;
    else
        y = bottom;
    switch(dir)
    {
        case ORIZONTAL:
        {
            int x1 = x - CELULA >= CIMP_OFFSET ? x - CELULA : CIMP_OFFSET;
            int y1 = y - CELULA >= CIMP_OFFSET ? y - CELULA : CIMP_OFFSET;
            int x2 = x + (size + 1) * CELULA <= CIMP_OFFSET + 10 * CELULA ? x + (size + 1) * CELULA : CIMP_OFFSET + 10 * CELULA;
            int y2 = y + 2 * CELULA <= CIMP_OFFSET + 10 * CELULA ? y + 2 * CELULA : CIMP_OFFSET + 10 * CELULA;
            acestPatrat.setRect(x1, y1, x2 - x1, y2 - y1);
            break;
        }
        case VERTICAL:
        {
            int x1 = x - CELULA >= CIMP_OFFSET ? x - CELULA : CIMP_OFFSET;
            int y1 = y - CELULA >= CIMP_OFFSET ? y - CELULA : CIMP_OFFSET;
            int x2 = x + 2 * CELULA <= CIMP_OFFSET + 10 * CELULA ? x + 2 * CELULA : CIMP_OFFSET + 10 * CELULA;
            int y2 = y + (size + 1) * CELULA <= CIMP_OFFSET + 10 * CELULA ? y + (size + 1) * CELULA : CIMP_OFFSET + 10 * CELULA;
            acestPatrat.setRect(x1, y1, x2 - x1, y2 - y1);
            break;
        }
    }
    for( int i = 0 ; i < corabii->size() ; i++)
    {
        Corabie* candidatNava = corabii->at(i);
        if(candidatNava != this)
        {
            switch(candidatNava->dir)
            {
                case ORIZONTAL:
                {
                    candidatPatrat.setRect(candidatNava->drawPoint.x(),
                                          candidatNava->drawPoint.y(),
                                          candidatNava->size * CELULA,
                                          CELULA);
                    break;
                }
                case VERTICAL:
                {
               candidatPatrat.setRect(candidatNava->drawPoint.x(),
                                      candidatNava->drawPoint.y(),
                                      CELULA,
                                      candidatNava->size * CELULA);
                    break;
                }
            }
            if(res = acestPatrat.intersects(candidatPatrat))
                return res;
        }
    }
    return res;
}

//setarea conflictului corabiei
void Corabie::yesConflict(bool c)
{
    conflict= c;
}

//functia returneaza dimensiunea corabiei
int Corabie::dimensiunea()
{
    return size;
}

//aplicarea dstrugerii corabiei
bool Corabie::damageCorabie()
{
    ranit++;
    if(ranit == size)
       distrus = true;
    return distrus;
}

//functia returneaza orientarea corabiei
direction Corabie::directie()
{
    return dir;
}
