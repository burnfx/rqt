#include "testchoicebutton.h"
#include "testexecution.h"

testChoiceButton::testChoiceButton(int rowNum, int typeNum,TestExecution *parent) : QPushButton(parent)
{
    myDigit = 10;
    mySeqNo = rowNum;
    myType = (types)typeNum;
    if (typeNum == 1)
    {
        setText("left");
    }
    else
    {
        setText("right");
    }
    myColor = grey;
    this->setStyleSheet("* { background-color: rgb(145,145,145) }");
    //setText(QString::number(myDigit));
    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
    this->parent = parent;
}

void testChoiceButton::reemitClicked()
{
    if (myColor == lightblue)
        {
            myColor = darkblue;
            this->setText("left");
            this->setStyleSheet("* { background-color: rgb(30,144,255); color: rgb(0, 0, 0) }");
        }
        else
        {
            myColor = lightblue;
            this->setText("right");
            this->setStyleSheet("* { background-color: rgb(135,206,250); color: rgb(0, 0, 0)}");
        }
        emit clicked(myDigit);
}

int testChoiceButton::getDepthData(int *value_set)
{
    if (myColor == 4) {*value_set = 0;}
    return myColor;
}

void testChoiceButton::decision(Qt::Key key){
    if(key == Qt::Key_Right)
    {
        myColor = lightblue;
        this->setText("right");
        this->setStyleSheet("* { background-color: rgb(135,206,250); color: rgb(0, 0, 0)}");
        //parent->appHnd->measureStopTime();
    }else if(key == Qt::Key_Left)
    {
        myColor = darkblue;
        this->setText("left");
        this->setStyleSheet("* { background-color: rgb(30,144,255); color: rgb(0, 0, 0) }");
        //parent->appHnd->measureStopTime();
    }else if(key == Qt::Key_Up)
    {
        //parent->appHnd->measureStopTime();
        parent->goForward();
    }
}

