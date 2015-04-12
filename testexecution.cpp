#include "testexecution.h"
#include "ui_testexecution.h"
#include <QGridLayout>
#include <QTimer>
#include <QKeyEvent>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

#define MAX_TRACK_TIME 10;
#define WAIT_TIME_BLACK_BACKGROUND 3
#define WAIT_TIME_BLACK_BACKGROUND_EXPIRED 30
#define MAX_SEQUENCES 10

QString STOP = "stop";
QString PLAY = "play";
QString PAUSE = "pause";


TestExecution::TestExecution(applicationHandler *appHND, QWidget *parent) : QDialog(parent), ui(new Ui::TestExecution)
{
    ui->setupUi(this);
    this->appHND = appHND;
    //this->stUser = stUser;
    //this->userID = userID;
    //this->supervisor = sup.toUtf8().constData();
    this->myRunState = stop;
    this->currentSeqNo = 0;
    this->currentSeqCnt = MAX_TRACK_TIME;


    ui->titleLBL->setText(QString("Test"));

    //ui->gridLayoutCMDB->addWidget(ui->runningLBL, 0, 0);
    //ui->gridLayoutCMDB->addWidget(ui->remainLBL, 0, 2);
    //ui->gridLayoutCMDB->addWidget(ui->timeLBL, 0, 3);
    ui->timeLBL->setText("not started yet");

    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    int cnt = 0;
    /*
    for (int i = 0; i < 10; ++i)
    {
        labels[i] = new QLabel(this);
        labels[i]->setText(QString("Sequence %1").arg(i+1));
        ui->gridLayoutCMDB->addWidget(labels[i], i+1, 0);
        for (int j=1; j <= 1; j++)
        {
            buttons[cnt] = new testChoiceButton(i, j, this);
            ui->gridLayoutCMDB->addWidget(buttons[cnt], i+1, j);
            cnt++;
        }
    }
    */
    //updateCurrentSequence();

    // set file names
    userDBCopyName = "temp_DB_Copy.txt";
    //userDBFileName = userID.toUtf8().constData();
    userDBFileName = "testdata_userID_" + userDBFileName + ".txt";

    // send initial file name
    appHND->selectVideoTrack(currentSeqNo);
}

TestExecution::~TestExecution()
{
    //killTimer(timer);
    delete timer;
    emit recordsUpdated();
    delete ui;
}

void TestExecution::on_okCMDB_clicked()
{
    //get data off all buttons
    //if a datapoint is missing set "uncomplete_flag"
    int complete = 1;
    int *complete_flag = &complete;
    std::string seq[10];

    /*
    for (int i = 0; i < 30; i+=3)
    {
        std::stringstream ss[4];
        ss[0] << i/3;
        ss[1] << buttons[i]->getDepthData(complete_flag);
        ss[2] << buttons[i+1]->getDepthData(complete_flag);
        ss[3] << buttons[i+2]->getDepthData(complete_flag);
        seq[i/3] = "seq" + ss[0].str() + "," + ss[1].str() + ss[2].str() + ss[3].str();
    }
    if (*complete_flag == 0)
    {
        saveCloseWindow sWnd;
        sWnd.setModal(true);
        if (sWnd.exec()!=QDialog::Accepted)
        {
            return;
        }
    }
    */

    // make sure application also stops
    myRunState = stop;
    appHND->setControl(STOP);

    //read comments
    //std::string comments = ui->textEdit->toPlainText().toUtf8().constData();

    //open file with user id
    std::ofstream testDataFile;
    testDataFile.open(userDBFileName.c_str(), std::ofstream::out | std::ofstream::app);


    /*
    // date, time, supervisor
    QDateTime dateTime = QDateTime::currentDateTime();
    std::string sDateTime = dateTime.toString("dd.MM.yyyy'-'hh:mm:ss").toUtf8().constData();
    testDataFile << "time," + sDateTime + ",supervisor," + supervisor + "\n";

    // test results from buttons
    for (int i = 0; i < 9; i++)
    {
        testDataFile << seq[i] << ",";
    }
    testDataFile << seq[9] << "\n";

    // comment string - remove newlines "\n"
    char delC[] = "\n";
    //comments.erase (std::remove(comments.begin(), comments.end(), delC[0]), comments.end());
    //testDataFile << "comments," << comments << "\n";

    // close file
    testDataFile.close();
    */

    // update executed test information
    //emit recordsUpsdated();

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
    emit recordsUpdated();

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
    //updateCurrentSequence();
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
    //updateCurrentSequence();
}

void TestExecution::on_stopCMDB_clicked()
{
    myRunState = stop;
    currentSeqCnt = MAX_TRACK_TIME;
    ui->timeLBL->setText("stopped");
    appHND->setControl(STOP);
    //updateCurrentSequence();
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
    //updateCurrentSequence();
}

void TestExecution::on_fwdCMDB_clicked()
{
    goForward();
}

/*
void TestExecution::updateCurrentSequence()
{
    for (int i=0; i < 10; i++)
    {
        if (i!=currentSeqNo)
        {
            //make grey
            //labels[i]->setStyleSheet("QLabel { background-color : rgb(199,199,199) }");
        }
        else
        {
            if (myRunState == running)
            {
                // make green
                //labels[i]->setStyleSheet("QLabel { background-color : rgb(78,238,148) }");
            }
            else if (myRunState == stop)
            {
                // make red
                //labels[i]->setStyleSheet("QLabel { background-color : rgb(238,99,99) }");
            }
            else if (myRunState = waiting)
            {
                // make blue
                //labels[i]->setStyleSheet("QLabel { background-color : rgb(50,99,200) }");
            }
        }
    }
}
*/

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
    if (currentDecision) {
        qDebug() << currentSeqNo << currentQuality << currentDecision;
    }
    else {
        qDebug() << currentSeqNo << currentQuality << currentDecision << ui->fdtimeVal->text().toInt() << ui->ldtimeVal->text().toInt();
    }
}
