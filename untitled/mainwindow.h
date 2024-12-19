
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>



class MainWindow : public QMainWindow
    , private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_button_clicked();
    void on_input_returnPressed();
};

#endif // MAINWINDOW_H
