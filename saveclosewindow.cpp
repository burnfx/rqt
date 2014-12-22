#include "saveclosewindow.h"
#include "ui_saveclosewindow.h"

saveCloseWindow::saveCloseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveCloseWindow)
{
    ui->setupUi(this);
}

saveCloseWindow::~saveCloseWindow()
{
    delete ui;
}

void saveCloseWindow::on_pushButton_clicked()
{
    this->accept();
    this->close();
}

void saveCloseWindow::on_pushButton_2_clicked()
{
    this->reject();
    this->close();
}
