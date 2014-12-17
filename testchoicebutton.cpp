#include "testchoicebutton.h"

testChoiceButton::testChoiceButton(int rowNum, int typeNum, QWidget *parent) : QPushButton(parent)
{
    myDigit = 10;
    mySeqNo = rowNum;
    myType = (types)typeNum;
    if (typeNum == 1)
    {
        setText("left");
    }
    else if (typeNum == 2)
    {
        setText("middle");
    }
    else
    {
        setText("right");
    }
    myColor = grey;
    this->setStyleSheet("* { background-color: rgb(145,145,145) }");
    //setText(QString::number(myDigit));
    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}

void testChoiceButton::reemitClicked()
{
    if (myColor == lightblue)
    {
        myColor = blue;
        this->setText("middle");
        this->setStyleSheet("* { background-color: rgb(30,144,255) }");
    }
    else if (myColor == blue)
    {
        myColor = darkblue;
        this->setText("back");
        this->setStyleSheet("* { background-color: rgb(0,0,205) }");
    }
    else
    {
        myColor = lightblue;
        this->setText("front");
        this->setStyleSheet("* { background-color: rgb(135,206,250) }");
    }
    emit clicked(myDigit);
}

int testChoiceButton::getDepthData(int *value_set)
{
    if (myColor == 4) {*value_set = 0;}
    return myColor;
}
