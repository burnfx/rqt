#ifndef TESTEXECUTION_H
#define TESTEXECUTION_H

#include <QDialog>
#include <QGridLayout>
#include "testchoicebutton.h"
#include <string>
#include "applicationhandler.h"

namespace Ui {
class TestExecution;
}

class TestExecution : public QDialog
{
    Q_OBJECT

public:
    explicit TestExecution(int testNo,  QString stUser, QString userID, QString sup, applicationHandler *appHND, QWidget *parent = 0);
    ~TestExecution();

private slots:
    void on_okCMDB_clicked();
    void on_exitCMDB_clicked();
    void update();
    void setPosition(int testABC);
    void on_playPauseCMDB_clicked();
    void on_stopCMDB_clicked();
    void on_backCMDB_clicked();
    void on_fwdCMDB_clicked();

private:
    void updateCurrentSequence();
    Ui::TestExecution *ui;
    applicationHandler *appHND;
    int testNo;
    int currentSeqNo;
    int currentSeqCnt;
    int runState;
    std::string supervisor;
    QString stUser;
    QString userID;
    QTimer *timer;
    testChoiceButton *buttons[30];
    QLabel *labels[10];
};

#endif // TESTEXECUTION_H
