#ifndef GUISTARTUP_H
#define GUISTARTUP_H

#include <QDialog>
#include <QDebug>
#include "applicationhandler.h"
#include <unistd.h>

namespace Ui {
class guiStartup;
}

class guiStartup : public QDialog
{
    Q_OBJECT

public:
    explicit guiStartup(applicationHandler *appHND, QWidget *parent = 0);
    ~guiStartup();

private slots:

    void on_exitCMDB_clicked();

    void on_testCMDB_2_clicked();

    void on_playCMDB_clicked();

    void on_recordCMDB_clicked();

    void on_edvsCMDB_clicked();

    void on_setFileCMDB_clicked();

    void on_stopCMDB_clicked();

private:
    Ui::guiStartup *ui;
    applicationHandler *appHND;
};

#endif // GUISTARTUP_H
