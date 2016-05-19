#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QList>
#include <QHash>
#include <QTcpServer>

class QBuffer;
class QTcpSocket;

class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    ChatServer(QObject* parent = 0);
    ~ChatServer();

private slots:
    void addConnection();
    void removeConnection();
    void receiveMessage();

private:
    QList<QTcpSocket*> connections;
    QHash<QTcpSocket*, QBuffer*> buffers;
};

#endif // CHATSERVER_H
