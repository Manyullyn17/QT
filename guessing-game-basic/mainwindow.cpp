#include "mainwindow.h"
#include <iostream>
#include <QRandomGenerator>
#include <QIntValidator>
#include <QTimer>

#define TIME 15

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    generateRandomNumber();
    input->setValidator(new QIntValidator(0, 100, this));   // only allow numbers to be input
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::on_timer_timeout);
    on_reset_clicked();
}

MainWindow::~MainWindow()
{
}

void MainWindow::generateRandomNumber()
{
    m_randnum = QRandomGenerator::global()->bounded(0, 100);
    std::cout << m_randnum << std::endl;  // output random number to console for testing purposes
}

void MainWindow::on_guessButton_clicked()
{
    if (m_timer_state == 0)
    {
        m_timer->start(1000);
        m_timer_state = 1;
    }
    if (m_timer_state == 1)
    {
        int num = input->text().toInt();
        input->clear();
        if (num == m_randnum) {
            output->setText("Correct!");
            outputList->addItem("The correct answer was " + QString::number(num));
            m_timer->stop();
            m_timer_state = -1;
        } else if (num < m_randnum) {
            output->setText("Try higher");
            outputList->addItem("Answer is higher than " + QString::number(num));
        } else {
            output->setText("Try lower");
            outputList->addItem("Answer is lower than " + QString::number(num));
        }
    }
}

void MainWindow::on_input_returnPressed()
{
    on_guessButton_clicked();
}

void MainWindow::on_reset_clicked()
{
    generateRandomNumber();
    output->setText("Guess the number from 0-100!");
    input->setText("");
    outputList->clear();
    m_timer_state = 0;
    m_time = TIME;
    remTime->setText("Time: " + QString::number(TIME));
}

void MainWindow::on_timer_timeout()
{
    m_time--;
    remTime->setText("Time: " + QString::number(m_time));
    if (m_time == 0)
    {
        m_timer->stop();
        m_timer_state = -1;
        outputList->addItem("Time Over");
        output->setText("Time Over, try again!");
    }
}
