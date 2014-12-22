#include "testexecbutton.h"

testExecButton::testExecButton(int blockNum, QWidget *parent) : QPushButton(parent)
{
    this->bNum = blockNum;
    this->setText("Test #" + QString::number(bNum));

    this->setMaximumHeight(60);
    this->setMaximumWidth(70);
    this->setMinimumHeight(60);
    this->setMinimumWidth(70);

    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}

void testExecButton::reemitClicked()
{
        emit clicked(bNum);
}
