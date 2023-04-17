#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent)
    : QObject{parent}
{
    server = new QTcpServer(this);

    // when a user connect emits a signal
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(server->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Server started!";
    }
    else
    {
        qDebug() << "Server could not start";
    }
}

void MyTcpServer::newConnection()
{
    // grab socket
    QTcpSocket *socket = server->nextPendingConnection();

    socket->write("Hello client\r\n");
    socket->flush();

    socket->waitForBytesWritten(3000);

    socket->close();
}
