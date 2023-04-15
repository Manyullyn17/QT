#include "hexeditor.h"

HexEditor::HexEditor(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
}

HexEditor::~HexEditor()
{
}


void HexEditor::on_hexEdit_textChanged()
{
    if(hexEdit->hasFocus())
    {
        hex = hexEdit->toPlainText();
        QStringList hexList = hex.split(" ");
        QString asciiString;
        foreach(QString hexValue, hexList) {
            QByteArray byteArray = QByteArray::fromHex(hexValue.toLatin1());
            asciiString += QString(byteArray);
        }
        asciiEdit->setText(asciiString);
    }
}


void HexEditor::on_asciiEdit_textChanged()
{
    if(asciiEdit->hasFocus())
    {
        text = asciiEdit->toPlainText();
        QString hexString;
        for (int i = 0; i < text.length(); i++) {
            hexString += QString("%1 ").arg(text.at(i).unicode(), 2, 16, QChar('0'));
            //                          arg(char_to_convert, len, base, char_to_fill_empty_space)
        }
        hexEdit->setText(hexString);
    }
}

