#include "testexecution.h"
#include "ui_testexecution.h"
#include "AdaptiveStaircase.h"
#include <QGridLayout>
#include <QTimer>
#include <QKeyEvent>
#include <QTextStream>
#include <QFile>

#include <unistd.h>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>

#define MAX_TRACK_TIME 10;
#define WAIT_TIME_BLACK_BACKGROUND 3
#define WAIT_TIME_BLACK_BACKGROUND_EXPIRED 30
#define MAX_SEQUENCES 10

QString STOP = "stop";
QString PLAY = "play";
QString PAUSE = "pause";

TestExecution::TestExecution(applicationHandler *appHND, int userID, QWidget *parent) : QDialog(parent), ui(new Ui::TestExecution)
{
    ui->setupUi(this);
    this->appHND = appHND;
    this->userID = userID;
    this->myRunState = stop;
    this->currentSeqNo = 0;
    this->currentSeqCnt = MAX_TRACK_TIME;
    this->currentDecision = UNDECIDED;

    //make results file
    this->userID = userID;
    unsigned long timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    this->filename = "UID" + QString::number(userID) + " " + QString::number(timestamp) + ".txt";

    std::ofstream cstream(filename.toStdString().c_str());
    cstream.close();

    ui->titleLBL->setText(QString("Test"));
    ui->timeLBL->setText("not started yet");

    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    // set file names
    userDBCopyName = "temp_DB_Copy.txt";
    //userDBFileName = userID.toUtf8().constData();
    userDBFileName = "testdata_userID_" + userDBFileName + ".txt";

    // AdaptiveStaircase USAGE
    std::vector<int> qualSteps = {30,20,10,5};
    std::vector<decision> seqAnswers = {RIGHT,RIGHT,RIGHT,RIGHT,RIGHT,LEFT,LEFT,LEFT,LEFT,LEFT};
    as = new AdaptiveStaircase(1, down, 15, 6, 5, qualSteps, seqAnswers);
    currSQ = as->getCurrSQ();
    currentQuality = currSQ.quality;
    currentSeqNo = currSQ.sequence;

    //
    // std::vector<QString> seqNames = {"L0R5","L0R10","L0R20", "L0R40", "L0R80", "L0R5", "L0R10", "L0R20", "L0R40", "L0R80"};
//    for (int i = 0; i < seqNames.size(); i++) {
//        this->decodeSeq.insert(std::pair<int, QString>(i, seqNames.at(i)));
//    }
//    std::map<int, QString>::iterator iterator;
//    iterator = KeyMap.find(key);
//    if (iterator != KeyMap.end()) {
//        return iterator->second;
//    } else {
//        return -1;
//    }
    //currentSeqName = seqNames.at(currentSeqNo);

    ui->remainLBL->setText("Remaining: ");
    ui->timeLBL->setText(QString::number(currentSeqCnt));

    // resetting test information
    ui->seqVal->setText(QString::number(currentSeqNo));
    ui->qualVal->setText(QString::number(currentQuality));
    ui->decVal->setText("undecided");
    ui->fdtimeVal->setText("-1");
    ui->ldtimeVal->setText("-1");

    // send initial file name
    appHND->selectVideoTrack(currentSeqNo, currentQuality);
}

TestExecution::~TestExecution()
{
    delete timer;
    delete ui;
}

void TestExecution::on_okCMDB_clicked()
{
    //get data off all buttons
    //if a datapoint is missing set "uncomplete_flag"
    int complete = 1;
    int *complete_flag = &complete;
    std::string seq[10];

    // make sure application also stops
    myRunState = stop;
    appHND->setControl(STOP);

    //read comments
    //std::string comments = ui->textEdit->toPlainText().toUtf8().constData();

    //open file with user id
    std::ofstream testDataFile;
    testDataFile.open(userDBFileName.c_str(), std::ofstream::out | std::ofstream::app);

    // close window
    this->close();
}

void TestExecution::on_exitCMDB_clicked()
{
    closeWindow cWnd;
    cWnd.setModal(true);
    if (cWnd.exec()!=QDialog::Accepted)
    {
        return;
    }

    // make sure application also stops
    myRunState = stop;
    appHND->setControl(STOP);

    // update executed test information
    //emit recordsUpdated();

    // close
    this->close();
}


void TestExecution::update()
{
    if (myRunState == stop)
    {
        return;
    }
    else if(myRunState == waiting) {


        if (!currentWaitCnt--) {
            // save

            // reset sequence counter
            currentSeqCnt = MAX_TRACK_TIME;

            //
            //currentSeqNo++;
            //


            myRunState = running;
            ffwd = false;
            expired = false;
            firstDecision = true;

            // LABELS
            // timer
            ui->remainLBL->setText("Remaining: ");
            ui->timeLBL->setText(QString::number(currentSeqCnt));

            // resetting test information
            ui->seqVal->setText(QString::number(currentSeqNo));
            ui->qualVal->setText(QString::number(currentQuality));
            ui->decVal->setText("undecided");
            ui->fdtimeVal->setText("-1");
            ui->ldtimeVal->setText("-1");

            // decode sequence number


            // start next sequence
            appHND->selectVideoTrack(currentSeqNo, currentQuality);
            appHND->setControl(PLAY);
            timer->start(1000);

        }
        else {
            if (ffwd && expired) {
                currentWaitCnt = WAIT_TIME_BLACK_BACKGROUND;
                expired = false;
            }
            ui->timeLBL->setText(QString::number(currentWaitCnt));
            timer->start(1000);
        }


    } else if(myRunState == running) {
        if (!currentSeqCnt--) {
            myRunState = waiting;
            currSQ = as->nextSeqQual(currentDecision);
            currentQuality = currSQ.quality;
            currentSeqNo = currSQ.sequence;
            saveDecisionToFile();
            if(currentQuality == -1) {
                myRunState = stop;
                timer->start(1000);
                qDebug() << "Finished";
                return;
            }
            currentDecision = UNDECIDED;
            if (ffwd == true) {
                currentWaitCnt = WAIT_TIME_BLACK_BACKGROUND;
            }
            else {
                currentWaitCnt = WAIT_TIME_BLACK_BACKGROUND_EXPIRED;
                expired = true;
            }
            appHND->playBlackBackground();
            appHND->setControl(PLAY);
            ui->remainLBL->setText("Waiting: ");
            ui->timeLBL->setText(QString::number(currentWaitCnt));
            timer->start(1000);
        }
        else {
            ui->timeLBL->setText(QString::number(currentSeqCnt));
            timer->start(1000);
        }
    }
}

void TestExecution::on_playPauseCMDB_clicked()
{
    if(myRunState == stop){myRunState = running;}
    else if(myRunState == running){myRunState = stop;}
    // appHND->playPauseTrack(runState);
    if (myRunState == running)
    {
        ui->timeLBL->setText(QString::number(currentSeqCnt));
        timer->start(1000);
        appHND->setControl(PLAY);
    }
    else if (myRunState == stop)
    {
        ui->timeLBL->setText("paused");
        appHND->setControl(PAUSE);
    }
}

void TestExecution::on_stopCMDB_clicked()
{
    myRunState = stop;
    currentSeqCnt = MAX_TRACK_TIME;
    ui->timeLBL->setText("stopped");
    appHND->setControl(STOP);
}

void TestExecution::on_backCMDB_clicked()
{
    // if still running reset timer
    if (myRunState == running || myRunState == waiting) {
        myRunState = running;
        timer->start(1000);
    }
    // reset sequence counter
    currentSeqCnt = MAX_TRACK_TIME;
    ui->timeLBL->setText(QString::number(currentSeqCnt));
    // go one track back
    if (currentSeqNo) {currentSeqNo--;}
    appHND->selectVideoTrack(currentSeqNo, currentQuality);
    if (myRunState == running) {
        appHND->setControl(PLAY);
    }
}

void TestExecution::on_fwdCMDB_clicked()
{
    goForward();
}

void TestExecution::keyPressEvent( QKeyEvent * event )
{
    if (myRunState == running) {
        if (event->key() == Qt::Key_L) {
            currentDecisionTime = appHND->measureStopTime(currentSeqNo);
            updateDecisionTime(currentDecisionTime);
            currentDecision = RIGHT;
            ui->decVal->setText("RIGHT");
        }
        else if (event->key() == Qt::Key_J) {
            currentDecisionTime = appHND->measureStopTime(currentSeqNo);
            updateDecisionTime(currentDecisionTime);
            currentDecision = LEFT;
            ui->decVal->setText("LEFT");
        }
    }

    if (myRunState == running || (myRunState == waiting && ffwd==false)) {
        if (event->key() == Qt::Key_I) {
            goForward();
        }
    }

}

void TestExecution::updateDecisionTime(unsigned long time) {
    if (firstDecision) {
        firstDecision = false;
        ui->fdtimeVal->setText(QString::number(currentDecisionTime));
    } else {
        ui->ldtimeVal->setText(QString::number(currentDecisionTime));
    }
}

void TestExecution::goForward(){
    // reset
    ffwd = true;
    currentSeqCnt = 0;
    update();
}

void TestExecution::saveDecisionToFile() {
    std::ofstream outfile;
    outfile.open(this->filename.toStdString(), std::ios::app);
    outfile << currentSeqNo << " " << currentQuality << " " << currentDecision << " " << ui->fdtimeVal->text().toInt() << " " << ui->ldtimeVal->text().toInt() << std::endl;
    outfile.close();
}
