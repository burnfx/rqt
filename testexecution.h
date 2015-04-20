#ifndef TESTEXECUTION_H
#define TESTEXECUTION_H

//#include "testWindow.h"
#include <QDialog>
#include <QGridLayout>
#include <QFile>

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
    explicit TestExecution(applicationHandler *appHND, int userID, QWidget *parent = 0);
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
    void updateDecisionTime(unsigned long time);
    void saveDecisionToFile();
    Ui::TestExecution *ui;
    applicationHandler *appHND;
    int userGroup;
    int currentSeqNo;
    int currentQuality = 100;
    bool firstDecision = true;
    bool ffwd = false;
    bool expired = false;
    QString filename;
    QFile file;
    std::ofstream *ofs;
    int currentDecisionTime;
    int userID;
    QTextStream *stream;


    //std::array<std::vector<decision>, MAX_SEQUENCES> firstDecision;
    //std::array<std::vector<decision>, MAX_SEQUENCES> lastDecision;
    //std::array<std::vector<int>, MAX_SEQUENCES> fDTime;
    //std::array<std::vector<int>, MAX_SEQUENCES> lDTime;

    int decisionTime[10][2];




    int currentSeqCnt;
    int currentWaitCnt;
    enum runState { stop=0, running, waiting } myRunState;
    enum decision { LEFT=0, UNDECIDED, RIGHT} currentDecision = UNDECIDED;
    QString decisionMap[3] = {"LEFT", "UNDECIDED","RIGHT"};


    std::string userDBCopyName;
    std::string userDBFileName;

    QTimer *timer;
    //testChoiceButton *buttons[10];
    //QLabel *labels[10];
protected:
    void keyPressEvent(QKeyEvent * event);
};

#endif // TESTEXECUTION_H
