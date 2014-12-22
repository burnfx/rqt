#ifndef TESTEXECBUTTON_H
#define TESTEXECBUTTON_H

#include <QDialog>
#include <QMainWindow>
#include <QtWidgets/qwidget.h>
#include <QtWidgets>

class testExecButton : public QPushButton
{
    Q_OBJECT

public:
    testExecButton(int blockNum, QWidget *parent);

signals:
    void clicked(int digit);

private slots:
    void reemitClicked();

private:
    int bNum;
};

#endif // TESTEXECBUTTON_H
