
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
}

MainWindow::~MainWindow()
{
}

int value;

void MainWindow::on_button_clicked()
{
    value = input->text().toInt();

    if(value < 50)
        output->setText("Less than 50");
    else if(value == 50)
        output->setText("Exactly 50");
    else
        output->setText("More than 50");

    QString in = "your input string";
    QString out;
    for(int i = 0; i < in.size(); ++i)
    {
        QChar c = in[i];
        if(i % 2 == 0)
            out.append(c.toLower());
        else
            out.append(c.toUpper());
    }
    output->setText(out);
}

void MainWindow::on_input_returnPressed()
{
    on_button_clicked();
}

