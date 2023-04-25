#pragma once

#include "ui_mainwindow.h"

#include <QMainWindow>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_upperButton_clicked();
    void on_lowerButton_clicked();
    void on_camelButton_clicked();
private:
    static char toLower(char c);
    static char toUpper(char c);
};
