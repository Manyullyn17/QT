#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
}

MainWindow::~MainWindow()
{
}


void MainWindow::on_pushButton_pressed()
{
    test->setText(textEdit->toPlainText());

    if (add->isChecked())
    {
        int result = input1->value() + input2->value();
        output->setText(QString::number(result));
    }
    else if (substract->isChecked())
    {
        int result = input1->value() - input2->value();
        output->setText(QString::number(result));
    }
    else if (multiply->isChecked())
    {
        int result = input1->value() * input2->value();
        output->setText(QString::number(result));
    }
    else if (divide->isChecked())
    {
        if (input2->value() != 0)
            output->setText(QString::number((float)input1->value() / (float)input2->value()));
        else
            output->setText("Can't divide by Zero");
    }
}

