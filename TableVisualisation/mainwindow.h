#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include "client.h"
#include <QDebug>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_pressed();
    void on_updateRate_valueChanged(int arg1);
    void getData();
    void receiveMsg(QString msg, int type);

private:
    QTimer m_update_timer;
    bool m_started = false;
    Client m_client;
    QList<QString> m_data;

};
#endif // MAINWINDOW_H
