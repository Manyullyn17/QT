#include "netdataproducer.h"

#include <QDebug>
#include <QTcpSocket>

NetDataProducer::NetDataProducer()
    : m_socket{new QTcpSocket{}}
{

}

NetDataProducer::~NetDataProducer(){}

bool NetDataProducer::connect(const QString &host, int port)
{
    m_socket->abort();
    m_socket->connectToHost(host, port);
    return m_socket->waitForConnected(3000);
}

std::map<QTime, double> NetDataProducer::getData(int duration_msec) const
{
    if(m_socket->state() == QAbstractSocket::ConnectedState)
    {
        QByteArray request;
        request.append("READ_DATA ");
        request.append(QByteArray::number(duration_msec));

        m_socket->write(request);
        bool ok =  m_socket->waitForBytesWritten();

        std::map<QTime, double> data;

        if (ok)
        {
            while (m_socket->bytesAvailable())
            {
                QByteArray bytes_read = m_socket->readAll();
                if (bytes_read.size() == 0)
                {
                    return data;
                }

                auto data_list = bytes_read.split(' ');

                for(int idx = 0; idx < data_list.length(); )
                {
                    int time_stamp = data_list[idx].toInt(&ok);
                    idx++;
                    double value = data_list[idx].toDouble(&ok);
                    idx++;
                    data[QTime::fromMSecsSinceStartOfDay(time_stamp)] = value;
                }
            }
        }
        return data;
    }
    else
    {
        return {};
    }
}
