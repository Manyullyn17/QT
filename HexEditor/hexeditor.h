#ifndef HEXEDITOR_H
#define HEXEDITOR_H

#include "ui_hexeditor.h"

#include <QMainWindow>

class HexEditor : public QMainWindow, private Ui::HexEditor
{
    Q_OBJECT

public:
    HexEditor(QWidget *parent = nullptr);
    ~HexEditor();

private slots:
    void on_hexEdit_textChanged();
    void on_asciiEdit_textChanged();

private:
    QString text;
    QString hex;
};
#endif // HEXEDITOR_H
