#include "chatclient.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QTcpSocket>
#include <QBuffer>
#include <QSpinBox>
#include <QErrorMessage>
#include <mainwindow.h>
#include <QPalette>

static const quint16 DEFAULT_PORT = 6667;

ChatClient::ChatClient(QWidget *parent, Qt::WindowFlags flags)
    : QWidget(parent,flags)
{   cor = new CorabieMenu(&ipAdress,&port1);
    QVBoxLayout *main = new QVBoxLayout(this);
    QGridLayout *top  = new QGridLayout;
    QHBoxLayout *bottom = new QHBoxLayout;

    QLabel *label = new QLabel("Server",this);
    server = new QLineEdit(this);
    port = new QSpinBox(this);
    conn = new QPushButton("Connect:",this);
    port->setRange(1,32767);
    port->setValue(DEFAULT_PORT);
    server->setText(ipAdress);
    top->addWidget(label,0,0);
    top->addWidget(server,0,1);
    top->addWidget(port,0,2);

    label = new QLabel("Nick:",this);
    nick = new QLineEdit(this);
    nick->setText("Anonymus");
    top->addWidget(label,1,0);
    top->addWidget(nick,1,1);
    top->addWidget(conn,1,2);

    chat = new QTextEdit(this);
    chat->setReadOnly(true);

    label = new QLabel("Message:",this);
    message = new QLineEdit(this);
    send = new QPushButton("Send",this);
    send->setDefault(true);
    bottom->addWidget(label);
    bottom->addWidget(message);
    bottom->addWidget(send);

    main->addLayout(top);
    main->addWidget(chat);
    main->addLayout(bottom);
    setLayout(main);

    buffer = new QBuffer(this);
    socket = new QTcpSocket(this);
    buffer->open(QIODevice::ReadWrite);

    connect(message,SIGNAL(returnPressed()),SLOT(sendMessage()));
    connect(send,SIGNAL(clicked()),SLOT(sendMessage()));
    connect(conn,SIGNAL(clicked()),SLOT(toggleConnection()));
    connect(socket,SIGNAL(connected()),SLOT(setConnected()));
    connect(socket,SIGNAL(disconnected()),SLOT(setDisconnected()));
    connect(socket,SIGNAL(readyRead()),SLOT(receiveMessage()));

    toggleConnection();

   

}

ChatClient::~ChatClient()
{
    buffer->close();
    
}

void ChatClient::setConnected()
{
    port->setEnabled(false);
    server->setEnabled(false);
    nick->setEnabled(true);
    message->setEnabled(true);
    chat->setEnabled(true);
    chat->clear();
    send->setEnabled(true);
    conn->setText("Disconnect");
}

void ChatClient::setDisconnected()
{
    port->setEnabled(true);
    server->setEnabled(true);
    nick->setEnabled(false);
    message->setEnabled(false);
    chat->setEnabled(false);
    send->setEnabled(false);
    conn->setText("Connect");
}

void ChatClient::toggleConnection()
{
     if (socket->state() == QAbstractSocket::UnconnectedState)
    {
        socket->connectToHost(server->text(), port->value());
    }
    else
    {
        socket->disconnectFromHost();
    }
}

void ChatClient::sendMessage()
{
      // "<nick> message\n"
 if(ans = true)
      socket->write( "<font color=\"Red\">"+  nick->text().toLatin1() + ": "+"</font>" + message->text().toLatin1() + "\n");
   else
    if(ans = false)
       socket->write( "<font color=\"Aqua\">"+  nick->text().toLatin1() + ": "+"</font>" + message->text().toLatin1() + "\n");

    message->clear();
}

void ChatClient::receiveMessage()
{
    // missing some checks for returns values for the sake of simplicity
    qint64 bytes = buffer->write(socket->readAll());
    // go back as many bytes as we just wrote so that it can be read
    buffer->seek(buffer->pos() - bytes);
    // read only full lines, line by line
    while (buffer->canReadLine())
    {
        QString line = buffer->readLine();
        chat->append(line.simplified());
    }
}

