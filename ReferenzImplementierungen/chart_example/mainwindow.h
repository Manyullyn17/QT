#pragma once

#include "ui_mainwindow.h"

#include <QMainWindow>

class QChart;
class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_input_textChanged();

private:
    QChart* chart;
};
