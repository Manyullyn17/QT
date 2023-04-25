#pragma once

#include <map>
#include <QTime>
#include <QString>

class QTcpSocket;

class NetDataProducer
{
public:
    NetDataProducer();
    ~NetDataProducer();

    bool connect(const QString& host, int port);

    // DataProducer interface
public:
    std::map<QTime, double> getData(int duration_msec) const;

private:
    QTcpSocket* m_socket = nullptr;
};

