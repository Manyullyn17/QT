#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
}

MainWindow::~MainWindow()
{
}


void MainWindow::on_text_edit_textChanged()
{
    if (!text_edit->hasFocus())
        return;
    hex_edit->clear();
    const auto& text = text_edit->toPlainText();

    //QString hex = text.toLocal8Bit().toHex(' ');
    //hex_edit->setPlainText(hex);
    for(const QChar& c : text)
    {
        char code = c.toLatin1();
        hex_edit->insertPlainText(QString::number(code, 16) + " ");
    }
}


void MainWindow::on_hex_edit_textChanged()
{
    if (!hex_edit->hasFocus())
        return;
    text_edit->clear();
    const auto& text = hex_edit->toPlainText();

//    QString plain = QByteArray::fromHex(text.toLatin1().data());
//    text_edit->setPlainText(plain);

    const auto& codes = text.split(" ");
    for (const auto& code_str : codes)
    {
        bool ok = false;
        char code = code_str.toInt(&ok, 16);
        if(ok)
        {
            text_edit->insertPlainText(QChar::fromLatin1(code));
        }
    }
}

