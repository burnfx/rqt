#include "closewindow.h"
#include "ui_closewindow.h"

closeWindow::closeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::closeWindow)
{
    ui->setupUi(this);
}

closeWindow::~closeWindow()
{
    delete ui;
}

void closeWindow::on_pushButton_clicked()
{
    this->accept();
    this->close();
}

void closeWindow::on_pushButton_2_clicked()
{
    this->reject();
    this->close();
}
