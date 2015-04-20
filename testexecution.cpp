#include "testexecution.h"
#include "ui_testexecution.h"
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

    //make results file
    this->userID = userID;
    unsigned long timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    filename = "UID" + QString::number(userID) + " " + QString::number(timestamp) + ".txt";
    qDebug() << filename;
    // QString filename = "Data.txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
           // QTextStream qTS(&file);
            stream = new QTextStream(&file);
            *stream << "something" << endl;
    }

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
    std::vector<int> qualSteps = {20,10,5};
    std::vector<answer> seqAnswers = {left,left,right,right};
    AdaptiveStaircase *as = new AdaptiveStaircase(1, down, 15, 6,10, qualSteps, seqAnswers);


    // send initial file name
    appHND->selectVideoTrack(currentSeqNo);
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

            currentSeqNo++;
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

            // start next sequence
            appHND->selectVideoTrack(currentSeqNo);
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
            saveDecisionToFile();
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
    appHND->selectVideoTrack(currentSeqNo);
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
    *stream << currentSeqNo << currentQuality << currentDecision << ui->fdtimeVal->text().toInt() << ui->ldtimeVal->text().toInt() << endl;
    if (currentDecision) {

    }
    else {

    }
}
