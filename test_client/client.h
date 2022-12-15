#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class client : public QObject
{
    Q_OBJECT
public:
    explicit client(QObject *parent = nullptr);

public slots:
    bool connectToHost(QString host);
    void socketReadyRead();

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
