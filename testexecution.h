#ifndef TESTEXECUTION_H
#define TESTEXECUTION_H

//#include "testWindow.h"
#include <QDialog>
#include <QGridLayout>
#include "testchoicebutton.h"
#include <string>
#include "applicationhandler.h"
#include "closewindow.h"
#include "saveclosewindow.h"

namespace Ui {
class TestExecution;
}

class TestExecution : public QDialog
{
    Q_OBJECT

public:
    explicit TestExecution(applicationHandler *appHND, QWidget *parent = 0);
    ~TestExecution();
    void measureStopTime(int val);
    void goForward();
    applicationHandler * getAppHND(){return appHND;}
    int getSeqNumber(){return currentSeqNo;}

private slots:
    void on_okCMDB_clicked();
    void on_exitCMDB_clicked();
    void update();
    void on_playPauseCMDB_clicked();
    void on_stopCMDB_clicked();
    void on_backCMDB_clicked();
    void on_fwdCMDB_clicked();

signals:
    void recordsUpdated();

private:
    void updateCurrentSequence();
    Ui::TestExecution *ui;
    applicationHandler *appHND;
    int userGroup;
    int currentSeqNo;
    int currentSeqCnt;
    int currentWaitCnt;
    enum runState {stop=0, running, waiting } myRunState;
    std::string userDBCopyName;
    std::string userDBFileName;

    QTimer *timer;
    //testChoiceButton *buttons[10];
    //QLabel *labels[10];
protected:
    void keyPressEvent(QKeyEvent * event);
};

#endif // TESTEXECUTION_H
