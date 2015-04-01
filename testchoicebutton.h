#ifndef TESTCHOICEBUTTON_H
#define TESTCHOICEBUTTON_H

#include <QDialog>
#include <QMainWindow>
#include <QtWidgets/qwidget.h>
#include <QtWidgets>

class TestExecution;

class testChoiceButton : public QPushButton
{
    Q_OBJECT

public:
    testChoiceButton(int rowNum, int typeNum, TestExecution *parent);
    int getDepthData(int *value_set);
    void decision(Qt::Key key);
signals:
    void clicked(int digit);

private slots:
    void reemitClicked();

private:
    int myDigit;
    int mySeqNo;
    enum colors { lightblue=1, blue, darkblue, grey } myColor;
    enum types { left=1, right } myType;
    TestExecution *parent;

};


#endif // TESTCHOICEBUTTON_H
