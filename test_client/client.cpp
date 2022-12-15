#include "client.h"

client::client(QObject *parent)
    : QObject{parent}
{
    socket = new QTcpSocket(this);
}

bool client::connectToHost(QString host)
{
    socket->connectToHost(host, 9999);
    return socket->waitForConnected();
}

/*void client::socketReadyRead() // connected to QTcpSocket::readyRead() signal
 *
{
    array += socket->readAll();

    if(array.contains('\n')) {
        int bytes = array.indexOf('\n') + 1;     // Find the end of message
        QByteArray message = array.left(bytes);  // Cut the message
        array = array.mid(bytes);                // Keep the data read too early

        processMessage(message);

        socketReadyRead();                       // re-call myself to process more
    }
}*/
QByteArray array;

while(!array.contains('\n')) {
    socket->waitForReadyRead();
    array += socket->readAll();
}

int bytes = array.indexOf('\n') + 1;     // Find the end of message
QByteArray message = array.left(bytes);  // Cut the message
array = array.mid(bytes);                // Keep the data read too early

processMessage(message);
