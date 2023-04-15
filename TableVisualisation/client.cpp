#include "client.h"

Client::Client(QObject *parent) :
    QObject(parent)
{
}

void Client::Connect(QString ip, int port)
{
    socket = new QTcpSocket(this);
    socket->connectToHost(ip, port);

    if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected";
        emit sendMsg("Connected", 1);
    }
    else
    {
        qDebug() << "Connection failed";
        emit sendMsg("Connection failed", -1);
    }
}

void Client::Disconnect(bool quiet)
{
    socket->close();
    if(!quiet)
    {
        qDebug() << "Disconnected";
        emit sendMsg("Disconnected", 1);
    }
}

void Client::sendMsgToServer(QString str)
{
    QByteArray txt = str.toUtf8();
    socket->write(txt);
    socket->waitForBytesWritten(1000);
    socket->waitForReadyRead(3000);
    QString msg = socket->readAll();
    emit sendMsg(msg, 0);
}
