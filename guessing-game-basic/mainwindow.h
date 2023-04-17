#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int m_randnum;
    void generateRandomNumber();
    int m_time;
    int m_timer_state;
    QTimer * m_timer;

private slots:
    void on_guessButton_clicked();
    void on_input_returnPressed();
    void on_reset_clicked();
    void on_timer_timeout();
};
#endif // MAINWINDOW_H
