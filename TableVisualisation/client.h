#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

    void Connect(QString ip, int port);
    void Disconnect(bool quiet = false);
    void sendMsgToServer(QString str);

signals:
    void connection_failed(bool print, QString msg);
    void sendMsg(QString msg, int type);

private:
    QTcpSocket *socket;

};

#endif // CLIENT_H
