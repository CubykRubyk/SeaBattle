#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QAbstractSocket>
#include <QtMultimedia/QSound>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    blockSize = 0;//initializam cu 0 pachetul transmis prin TCP

    gstatus = NONE;
    serverGata = false;
    clientGata = false;
    gameover = false;

        abc[0]= 'A';
        abc[1]='B';
        abc[2]='C';
        abc[3]='D';
        abc[4]='E';
        abc[5]='F';
        abc[6]='G';
        abc[7]='H';
        abc[8]='I';
        abc[9]='J';

        chatClient = new ChatClient();


    //aranjamentul fesrestrei principale
    centralWidgetLayout = new QHBoxLayout(ui->centralWidget);
    QVBoxLayout *cimpuriStrat  = new QVBoxLayout();
    myBF = new CimpLupta(&gstatus,&statLupta);
    enemyBF = new CimpLupta(&gstatus,&statLupta);
    enemyShips = new QLabel(tr("Enemy Field:"));
    cimpuriStrat->addWidget(enemyShips);
    cimpuriStrat->addWidget(enemyBF);
    myShips = new QLabel(tr("My Field:"));
    cimpuriStrat->addWidget(myShips);
    cimpuriStrat->addWidget(myBF);
    cimpuriStrat->addStretch();
    centralWidgetLayout->addLayout(cimpuriStrat);
    gMenu = new GameMenu();
    centralWidgetLayout->addWidget(gMenu);
    ssMenu = new CorabieMenu(&ipAdress,&port);
    centralWidgetLayout->addWidget(ssMenu);
    lMenu = new LogMenu(&gstatus,&statLupta);
    centralWidgetLayout->addWidget(lMenu);
    centralWidgetLayout->addWidget(chatClient);
    ssMenu->hide();
    lMenu->hide();
    enemyBF->hide();
    enemyShips->hide();
    myBF->hide();
    myShips->hide();
    chatClient->hide();
    this->adjustSize();


    //conectam semnalele si sloturile
    connect(gMenu, SIGNAL(createGameClicked()), this, SLOT(creazaJoc()));
    connect(gMenu, SIGNAL(connectToGameClicked()), this, SLOT(conectareLaJoc()));
    connect(ssMenu, SIGNAL(inapoiClicked()), this, SLOT(inapoiLaMenu()));
    connect(myBF, SIGNAL(corabieActivata(bool,int)), ssMenu, SLOT(corabieActivata(bool,int)));
    connect(ssMenu, SIGNAL(rotesteClicked()), myBF, SLOT(rotatieCorabieActiva()));
    connect(ssMenu, SIGNAL(adaugaCorabieClicked(int)), myBF, SLOT(adaugaCorabiePeCimp(int)));
    connect(myBF, SIGNAL(corabieConflicta(bool)), ssMenu, SLOT(corabieConflict(bool)));
    connect(ssMenu, SIGNAL(stergeCorabieCimp()), myBF, SLOT(elimineCorabieCimp()));
    connect(ssMenu,  SIGNAL(genereazaRandom()), myBF, SLOT(genereazaRandom()));
    connect(ssMenu, SIGNAL(playClicked()), this, SLOT(startJoc()));
    connect(enemyBF, SIGNAL(celulaClicked(int,int)), this, SLOT(transmiteRind(int,int)));
    connect(myBF, SIGNAL(miscareRaspuns(int,int,CELL_STATUS,Corabie*)), this, SLOT(transmiteRindRaspuns(int,int,CELL_STATUS,Corabie*)));
    connect(enemyBF, SIGNAL(updateStatusLabel()), lMenu, SLOT(updateStatusLabel()));
    connect(myBF, SIGNAL(updateStatusLabel()), lMenu, SLOT(updateStatusLabel()));
    connect(&statLupta, SIGNAL(gameOver(PLAYERS)), this, SLOT(gameOver(PLAYERS)));



}
//destructor
MainWindow::~MainWindow()
{
    delete ui;
}

//joc nou
void MainWindow::creazaJoc()
{
    isServer = true; //aplicatia e pornita in calitate de server

    myBF->show(); // afisam cimpul propriu
    myBF->setModAmplasare(true); //cimpul in calitate de regim amplasare
    //anuntam meniul amplasare despre faptul ca aplicatia este in calitate de server
    //dispar rindurile pt introducerea portului si IP
    ssMenu->setServer(true);
    ssMenu->show(); //meniul amplasarii
    gMenu->hide(); //ascundem meniul jocului
    startServer(); //TCP server
    QApplication::processEvents(); // tratam evenimentele existente
    this->adjustSize(); //ajustam marimea ferestrei
}

//ne conectam la jocul existent
void MainWindow::conectareLaJoc()
{
    isServer = false; //aplicatia ca client

    myBF->show(); //afisam cimpul propiu
    myBF->setModAmplasare(true); //regimul amplasare
    myShips->show(); //afisam labelul My Field
    //anuntam meniul amplasare despre faptul ca aplicatia este in calitate de client
    //se activeaza rindurile pt introducerea portului si IP
    ssMenu->setServer(false);
    ssMenu->show(); //meniul amplasare
    gMenu->hide(); //inchidem meniul jocului
    startClient(); //rulam TCP client
    QApplication::processEvents(); //evenmentele eixstente
    this->adjustSize();
}

//ne intoarce la meniul jocului
void MainWindow::inapoiLaMenu()
{
    myBF->hide();
    myShips->hide();
    ssMenu->hide();
    gMenu->show();
    myBF->reset(); // resetam amplasarea corabiilor
    ssMenu->reset();
    if(isServer)
        stopServer(); //stopam serverul
    QApplication::processEvents();
    this->adjustSize();
}

//trecem de la redactor la inceputul jocului
void MainWindow::startJoc()
{

    if(!isServer) //daca aplicatia - client
    {
        if(!conectareLaServer()) //incercam sa ne conectam la server
            return;
        //clientul e gata pt joc
        gstatus = READY;
        clientGata = true;
        transmiteGataServer(); //transmitem semnal
    }
    else
    {
        //severul e gata
        gstatus = READY;
        serverGata = true;
        incearcaStartJoc(); //serverul veifica daca jucatorii sunt gata

    }
    lMenu->updateStatusLabel(); //update la labelul cu starea jocului
    myBF->setModAmplasare(false); //stingem pt cimpul propiu modul amplasare
    myBF->corabieNeactiva(); //deactivam corabia activa,daca era
    enemyBF->setModLupta(true); //cimpul oponentului in regim de lupta
    lMenu->show(); //afisam meniul cu log
    ssMenu->hide(); //ascundem meniul amplasare
    enemyBF->show();//afisam cimpul oponentului
    enemyShips->show(); //afisam Labelul ""Enemy Ships
    chatClient->show();

    QApplication::processEvents();
    this->adjustSize();
    this->move(40,0); //miscam putin fereastra
}

//start TCP server
void MainWindow::startServer()
{
    tcpServer = new QTcpServer(this);
#ifdef PORT_DEFAULT
    if(!tcpServer->listen(QHostAddress::Any,PORT)) { //ascultam pe toate interfetele de retea
#else
    if(!tcpServer->listen()){// portul se alege automat
#endif
     QMessageBox::critical(this,tr("Sea Battle"),
                           tr("Unable to start the server:%1.")
                           .arg(tcpServer->errorString()));
     return;
    }
    ssMenu->setStatusLabelText(tr("The server is running\n\nport:%1\n").arg(tcpServer->serverPort()));
   //conectam semnalul care "spune" ca este o conexiune nou,cu slotul care primeste conexiunea
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(acceptaConexiune()));
}

void MainWindow::stopServer()
{
    tcpServer->close();
    delete tcpServer;
}

void MainWindow::startClient()
{
    tcpSocket = new QTcpSocket(this);
    //semnal ca in socket sunt date pentru citire + slot care primeste datele
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(citireDinSocket()));
    //semnal ca a aparut o eroare + slot care afiseaza eroarea
}

void MainWindow::stopClient()
{
    //stop TCP client
}

void MainWindow::displayEroare(QAbstractSocket::SocketError socketError){
    switch(socketError){
    case QAbstractSocket::HostNotFoundError:

        QMessageBox::information(this, tr("Sea Battle"),
                                      tr("Host Not Found."));
             break;
         case QAbstractSocket::ConnectionRefusedError:
             QMessageBox::information(this, tr("Sea Battle "),
                                      tr("The connection was rejected"));
             break;
         case QAbstractSocket::RemoteHostClosedError:
             if(!gameover)
             {
                 QMessageBox::information(this, tr("Sea Batlle"),
                                      tr("The remote host closed the connection."));
                 close();
             }
             break;
         default:
             QMessageBox::information(this, tr("Sea Battle"),
                                      tr("Error: %1.")
                                      .arg(tcpSocket->errorString()));
         }
}

//citeste date din socket
void MainWindow::citireDinSocket()
{
    QDataStream in(tcpSocket); //initializam fluxul de date
    in.setVersion(QDataStream::Qt_5_4);

    if(blockSize == 0) { //daca este pachet de date
        //daca in socket date sunt mai putine decit marimea variabila,atunci iesim(asteptam mai multe date)
        if(tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        //daca sunt date destule,citim marimea pachetului
        in >> blockSize;

    }
    //daca in socket nu este tot pachetul,iesim
    if(tcpSocket->bytesAvailable() < blockSize)
        return;

    //daca putem citi pachetul integral
    blockSize = 0; //initializam cu 0 pachetul curent,pentru a-l citi pe urmatoru
    POCKET_TYPE pt; //tipul pachetului
    int temp; //variabia temporara pentru citie din socket si convertire in tipul necesar
    //citim tipul pachetului
    in >> temp;
    pt = (POCKET_TYPE)temp;
    int x,y;
    switch(pt)
    {
       case READY_TO_GAME: //pachetul contine mesajul despre : Gata de joc
           {
            clientGata = true;
           incearcaStartJoc();
           break;
           }
       case SETUP_TURN: // pachetul de la server cu starea jocului
           {
           in >> temp;
           gstatus = (GAME_STATUS)temp;//starea rindului
           lMenu->updateStatusLabel(); //update menu
           break;
           }
       case TURN: //pachetul contine miscarea oponetului
        {
        //citim coordonatele celulei
        in >> x;
        in >> y;
        lMenu->adaugaLogString(tr("Enemy turn: (%1:%2)").arg(abc[x]).arg(y + 1)); //scriem miscarea in log
        myBF->verificaMiscare(x,y); //verificam miscarea
        break;
        }
       case TURN_RESPONSE: //pachet cu raspuns la miscare
        {
        CELL_STATUS st;
        QPoint pos; //desen pozitia corabiei (se transmite in pachet daca corabia a fost distrusa)
        int size = 0; //marimea corabiei
        direction dir = ORIZONTAL;
        //citim coordonatele celulei
        in >> x;
        in >> y;
        in >> temp;
        st = (CELL_STATUS)temp; //starea celulei
        if (st == KILLED)
        {
            //citim datele despre corabie
            in >> pos;
            in >> size;
            in >> temp;
            dir = (direction) temp;
        }
        //afisam in log starea miscarii
        QString text;
        switch(st)
        {
        case KILLED:
            text = tr("Killed");
            break;
        case DAMAGED:
            text = tr("Damaged");
            break;
        case DOT:
            text = tr("Dot");
            break;
        }
        lMenu->adaugaLogString(text);
        enemyBF->verificaMiscareRaspuns(x,y,st,pos,size,dir);
        break;
        }
    }
}

bool MainWindow::conectareLaServer()
{
    tcpSocket->connectToHost(ipAdress,port);
    return tcpSocket->waitForConnected();
}

//acceptare cinexiune la server
void MainWindow::acceptaConexiune()
{
    tcpSocket = tcpServer->nextPendingConnection();
    connect (tcpSocket,SIGNAL(disconnected()),tcpSocket,SLOT(deleteLater()));
    //semnal ca in socket sunt date +slotul care citeste datele
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(citireDinSocket()));
    //semnal despre eroare+ slot care afiseaza eroare
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayEroare(QAbstractSocket::SocketError)));

}

// transmitem misccarea oponetului pt verificare
void MainWindow::transmiteRind(int x, int y)
{
    QByteArray block; //matrice din byte
    QDataStream out(&block,QIODevice::WriteOnly); //initializam fluxul cu matricea de byte
    POCKET_TYPE pt = TURN; //tipul pacchetului
    out.setVersion(QDataStream::Qt_5_4);
    out << (quint16)0; //lasam loc pentru marimea  pachetului
    out << pt; //inscriem tipul pachetului
    //scriem coordonatele celulei
    out << x;
    out << y;
    out.device()->seek(0); //intoarcem la locul rezervat pt pachet
    out << (quint16)(block.size()-sizeof(quint16)); //scriem marimea pachetului
    tcpSocket->write(block); //scriem matricea in socket
    lMenu->adaugaLogString(tr("Your turn (%1:%2)").arg(abc[x]).arg(y + 1));
}

void MainWindow::transmiteRindRaspuns(int x, int y, CELL_STATUS st, Corabie *s)
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    POCKET_TYPE pt = TURN_RESPONSE; //tipul pachetului
    out.setVersion(QDataStream::Qt_5_4);
    out << (quint16)0; // loc pt pachet
    out << pt;
    //coordonate
    out <<x;
    out <<y;
    //starea celulei
    out << st;
    if(st == KILLED) //daca distrus scriem datele despre corabie
    {
        out << s->pozitia();
        out << s->dimensiunea();
        out << s->directie();
    }
    out.device()->seek(0); // intoarcem la locul rezervat pt pachet
    out << (quint16)(block.size()-sizeof(quint16));
    tcpSocket->write(block);
    //scrim in log
    QString text;
    switch(st)
    {
    case KILLED:
        text = tr("Killed");
        break;
    case DAMAGED:
        text = tr("Damaged");
        break;
    case DOT:
        text = tr("Dot");
        break;
    }
    lMenu->adaugaLogString(text);
}

void MainWindow::transmiteGataServer()
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    POCKET_TYPE pt = READY_TO_GAME;
    out.setVersion(QDataStream::Qt_5_4);
    out << (quint16)0;
    out << pt;
    out.device()->seek(0);
    out  << (quint16)(block.size()-sizeof(quint16));
    tcpSocket->write(block);
}

void MainWindow::transmiteStareJoc(GAME_STATUS st)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    POCKET_TYPE pt = SETUP_TURN;
    out.setVersion(QDataStream::Qt_5_4);
    out << (quint16)0;
    out << pt;
    out << st; // a cui este miscarea
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    tcpSocket->write(block);
}


void MainWindow::incearcaStartJoc()
{
    if(serverGata && clientGata)
    {
        if(rand() % 2 == 0) // cine merge primul
        {
            // miscarea mea
            gstatus = YOUR_TURN;
            transmiteStareJoc(ENEMY_TURN); //a cui este muscarea
            lMenu->updateStatusLabel();
        }
        else
        {
            // miscarea oponentului
            gstatus = ENEMY_TURN;
            transmiteStareJoc(YOUR_TURN); // a cui este miscarea
            lMenu->updateStatusLabel();
        }
    }
}

// Game Over
void MainWindow::gameOver(PLAYERS pl)
{
    gameover = true;
    QString text;
    QString sound;
    switch(pl)
    {
    case ME: // am invins eu
        text = tr("You Win =)");
        sound = ":/sounds/Sounds/sdwin.wav";
        break;
    case ENEMY: // a invins oponentul
        sound = ":/sounds/Sounds/nave.wav";
        text = tr("You Lose =(");
    }
    QSound::play(sound); // sunet
    QMessageBox::information(this, tr("Sea Battle"), text); //mesaj
    if(isServer)
    {
        tcpServer->close();
    }
    close();
}

