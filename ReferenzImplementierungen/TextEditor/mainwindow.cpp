#include "mainwindow.h"


#include <QRegularExpression>

#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
}

MainWindow::~MainWindow()
{
}


char MainWindow::toUpper(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
    return c;
}

char MainWindow::toLower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    return c;
}

// Solution with full library support
void MainWindow::on_upperButton_clicked()
{
    QString text = textEdit->toPlainText();
    textEdit->setPlainText(text.toUpper());
}

// hand crafted solution
void MainWindow::on_lowerButton_clicked()
{
    auto text = textEdit->toPlainText().toStdString();
    for (char& c : text)
    {
        c = toLower(c);
    }
    textEdit->setPlainText(QString::fromStdString(text));
}

void MainWindow::on_camelButton_clicked()
{
    QString text = textEdit->toPlainText();

    const auto& words = text.split(" ");

    textEdit->clear();
    for(auto& word : words)
    {
        auto str = word.toStdString();

        bool first_letter = true;
        for (char& c : str)
        {
            if (first_letter)
            {
                c = toUpper(c);
                first_letter = false;
            }
            else
            {
                c = toLower(c);
            }
            textEdit->insertPlainText(QChar::fromLatin1(c));
        }

        textEdit->insertPlainText(" ");

// solution with iterators
//        std::string::iterator it = str.begin();
//        *it = toUpper(*it);
//        it++;
//        for( ; it != str.end(); it++)
//            *it = toLower(*it);
//        textEdit->insertPlainText(QString::fromStdString(str) + " ");
    }
}


