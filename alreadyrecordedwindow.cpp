#include "alreadyrecordedwindow.h"
#include "ui_alreadyrecordedwindow.h"

alreadyRecordedWindow::alreadyRecordedWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alreadyRecordedWindow)
{
    ui->setupUi(this);
}

alreadyRecordedWindow::~alreadyRecordedWindow()
{
    delete ui;
}

void alreadyRecordedWindow::on_pushButton_clicked()
{
    this->accept();
    this->close();
}

void alreadyRecordedWindow::on_pushButton_2_clicked()
{
    this->reject();
    this->close();
}
