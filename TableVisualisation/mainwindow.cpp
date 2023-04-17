#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    m_update_timer.setInterval(1000/updateRate->value());

    connect(&m_client, &Client::sendMsg, this , &MainWindow::receiveMsg);
    connect(&m_update_timer, &QTimer::timeout, this, &MainWindow::getData);
}

MainWindow::~MainWindow()
{
}


void MainWindow::on_startButton_pressed()
{
    if(!m_started)  // start
    {
        m_update_timer.start();
        ipAddress->setDisabled(true);
        port->setDisabled(true);
        startButton->setText("Stop");
        m_started = true;
        m_client.Connect(ipAddress->text(), port->text().toInt());
    }
    else    // stop
    {
        m_client.Disconnect();
        m_update_timer.stop();
        ipAddress->setDisabled(false);
        port->setDisabled(false);
        startButton->setText("Start");
        m_started = false;
    }
}


void MainWindow::on_updateRate_valueChanged(int arg1)
{
    m_update_timer.setInterval(1000/arg1);
}

void MainWindow::getData()
{
    QString str = "READ_DATA " + QString::number(1000/updateRate->value());
    m_client.sendMsgToServer(str);
}

void MainWindow::receiveMsg(QString msg, int type)
{
    if(type == 0)   // received data
    {
        m_data = msg.split(' ');

        outputTable->clearContents();
        outputTable->setRowCount(m_data.count()/2);

        int timeIdx = 0;    // every 2nd starting from 0 => timestamp
        int valueIdx = 1;   // every 2nd starting from 1 => value

        for (int row = 0; row < m_data.count()/2; row++)
        {
            QTime timestamp = QTime::fromMSecsSinceStartOfDay(m_data[timeIdx].toInt());
            QTableWidgetItem *timeItem = new QTableWidgetItem(timestamp.toString("hh:mm:ss.zzz"));
            outputTable->setItem(row, 0, timeItem);

            QString value = m_data[valueIdx];
            QTableWidgetItem *valueItem = new QTableWidgetItem(value);
            outputTable->setItem(row, 1, valueItem);

            timeIdx += 2;
            valueIdx += 2;
        }
    }
    else if(type == 1)  // connection msg
    {
        conStatusLbl->setText(msg);
    }
    else if(type == -1) // connection failed
    {
        conStatusLbl->setText(msg);
        m_client.Disconnect(true);  // quiet = true
        m_update_timer.stop();
        startButton->setText("Start");
        m_started = false;
    }
}
