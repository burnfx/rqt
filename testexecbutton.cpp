#include "testexecbutton.h"

testExecButton::testExecButton(QWidget *parent) : QPushButton(parent)
{
    //this->setText("Test");

    this->setMaximumHeight(60);
    this->setMaximumWidth(70);
    this->setMinimumHeight(60);
    this->setMinimumWidth(70);

    //connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}

void testExecButton::reemitClicked()
{
        emit clicked();
}

