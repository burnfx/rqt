#include "guistartup.h"
#include "ui_guistartup.h"

guiStartup::guiStartup(applicationHandler *appHND, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::guiStartup)
{
    ui->setupUi(this);
    this->appHND = appHND;
}

guiStartup::~guiStartup()
{
    delete ui;
}

void guiStartup::on_exitCMDB_clicked()
{
    this->close();
}

void guiStartup::on_testCMDB_2_clicked()
{
    this->accept();
    this->close();
}

void guiStartup::on_playCMDB_clicked()
{
    appHND->setMode("2");
}

void guiStartup::on_recordCMDB_clicked()
{
    //char *recordName;
    //recordName = applicationHandler::qstringtoChar(ui->recordNameLineEdit->text());
    //std::string recordNameStr = ui->recordNameLineEdit->text().toUtf8().constData();
    //recordName = new char[recordNameStr.length() + 1];
    //strcpy(recordName,recordNameStr.c_str());
    //qDebug() << ui->recordNameLineEdit->text();
    //appHND->setFile(recordName);
    //appHND->setFile(ui->recordNameLineEdit->text());
    // char *recordTime = applicationHandler::qstringtoChar(ui->recordTimeLineEdit->text());
    //char *recordTime;
    //std::string recordTimeStr = ui->recordTimeLineEdit->text().toUtf8().constData();
    //recordTime = new char[recordTimeStr.length() + 1];
    //strcpy(recordTime,recordTimeStr.c_str());
    // appHND->setTime(recordTime);
    //appHND->setTime(ui->recordTimeLineEdit->text());
    // QString mode = "2";
    //appHND->setMode(mode);
    //appHND->setMode(mode);
    appHND->setFile(ui->recordNameLineEdit->text());
    usleep(100);
    QString play = "play";
    appHND->setControl(play);
}

void guiStartup::on_edvsCMDB_clicked()
{
    appHND->setMode("0");
}

void guiStartup::on_setFileCMDB_clicked()
{
    appHND->setFile(ui->recordNameLineEdit->text());
}

void guiStartup::on_stopCMDB_clicked()
{
    QString stop = "stop";
    appHND->setControl(stop);
}
