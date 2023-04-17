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

    void Connect();

signals:

public slots:

private:
    QTcpSocket *socket;

};

#endif // CLIENT_H
