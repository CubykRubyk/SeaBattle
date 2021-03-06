#include "chatserver.h"
#include <QBuffer>
#include <QTcpSocket>

ChatServer::ChatServer(QObject* parent) : QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(addConnection()));
}

ChatServer::~ChatServer()
{
}

void ChatServer::addConnection()
{
    QTcpSocket* connection = nextPendingConnection();
    connections.append(connection);
    QBuffer* buffer = new QBuffer(this);
    buffer->open(QIODevice::ReadWrite);
    buffers.insert(connection, buffer);
    connect(connection, SIGNAL(disconnected()), SLOT(removeConnection()));
    connect(connection, SIGNAL(readyRead()),	SLOT(receiveMessage()));
}

void ChatServer::removeConnection()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QBuffer* buffer = buffers.take(socket);
    buffer->close();
    buffer->deleteLater();
    connections.removeAll(socket);
    socket->deleteLater();
}

void ChatServer::receiveMessage()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QBuffer* buffer = buffers.value(socket);

    // missing some checks for returns values for the sake of simplicity
    qint64 bytes = buffer->write(socket->readAll());
    // go back as many bytes as we just wrote so that it can be read
    buffer->seek(buffer->pos() - bytes);
    // read only full lines, line by line
    while (buffer->canReadLine())
    {
        QByteArray line = buffer->readLine();
        foreach (QTcpSocket* connection, connections)
        {
            connection->write(line);

        }
    }
}
