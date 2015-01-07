#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <QDialog>
#include "applicationhandler.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>

namespace Ui {
class userManagement;
}

class userManagement : public QDialog
{
    Q_OBJECT

public:
    explicit userManagement(const char *dbFile, QStringList userList, applicationHandler *appHND, QWidget *parent = 0);
    ~userManagement();
    int extractUserId(std::string line);

private slots:
    void on_closeCMDB_clicked();
    void on_okCMDB_clicked();
    void on_delCMDB_clicked();
    void on_userCBX_currentTextChanged(const QString &arg1);
    void on_userNewCB_clicked();
    void on_eyeDistSlider_sliderPressed();
    void on_eyeDistSlider_sliderReleased();
    void on_eyeDistSlider_valueChanged(int value);
    void update();

private:
    Ui::userManagement *ui;
    applicationHandler *appHND;
    QTimer *timer;
    const char *userDBFileName;
    const char *userDBCopyName;
    int sliderIsPressed;
    int sliderValChanged;
    int runState;
    int vidCnt;
};

#endif // USERMANAGEMENT_H
