#include "testexecution.h"
#include "ui_testexecution.h"
#include <QGridLayout>
#include "testchoicebutton.h"
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

#define maxTrackTime 10;

QString stop = "stop";
QString play = "play";
QString pause = "pause";


TestExecution::TestExecution(int testNo, QString stUser, QString userID, QString sup, applicationHandler *appHND, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestExecution)
{
    ui->setupUi(this);
    this->appHND = appHND;
    this->testNo = testNo;
    this->stUser = stUser;
    this->userID = userID;
    this->supervisor = sup.toUtf8().constData();
    this->runState = 0;
    this->currentSeqNo = 0;
    this->currentSeqCnt = maxTrackTime;
    ui->titleLBL->setText(QString("Test No. %1").arg(testNo));

    ui->gridLayoutCMDB->addWidget(ui->runningLBL, 0, 0);
    ui->gridLayoutCMDB->addWidget(ui->remainLBL, 0, 2);
    ui->gridLayoutCMDB->addWidget(ui->timeLBL, 0, 3);
    ui->timeLBL->setText("not started yet");

    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    int cnt = 0;
    for (int i = 0; i < 10; ++i)
    {
        labels[i] = new QLabel(this);
        labels[i]->setText(QString("Sequence %1").arg(i+1));
        ui->gridLayoutCMDB->addWidget(labels[i], i+1, 0);
        for (int j=1; j <= 3; j++)
        {
            buttons[cnt] = new testChoiceButton(i, j, this);
            ui->gridLayoutCMDB->addWidget(buttons[cnt], i+1, j);
            cnt++;
        }
    }
    updateCurrentSequence();

    // set file names
    userDBCopyName = "temp_DB_Copy.txt";
    userDBFileName = userID.toUtf8().constData();
    userDBFileName = "testdata_userID_" + userDBFileName + ".txt";
}

TestExecution::~TestExecution()
{
//    killTimer(timer);
    delete timer;
    int cnt = 0;
    for (int i = 0; i < 10; ++i)
    {
        delete labels[i];
        for (int j=1; j <= 3; j++)
        {
            delete buttons[cnt];
            cnt++;
        }
    }
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

    // make sure application also stops
    runState = 0;
    appHND->setControl(stop);

    //read comments
    std::string comments = ui->textEdit->toPlainText().toUtf8().constData();

    //open file with user id
    std::ofstream testDataFile;
    testDataFile.open(userDBFileName.c_str(), std::ofstream::out | std::ofstream::app);

    // sequence block number, complete_flag
    std::stringstream ss;
    ss << testNo;
    if (*complete_flag == 0)
    {
        testDataFile << "testBlock," << testNo  << ",complete=false,";
    }
    else
    {
        testDataFile << "testBlock," << testNo  << ",complete=true,";
    }

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
    comments.erase (std::remove(comments.begin(), comments.end(), delC[0]), comments.end());
    testDataFile << "comments," << comments << "\n";

    // close file
    testDataFile.close();

    // update executed test information
    emit recordsUpdated();

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
    runState = 0;
    appHND->setControl(stop);

    // update executed test information
    emit recordsUpdated();

    // close
    this->close();
}


void TestExecution::update()
{
    // if timer should actually be stopped, but is just running out
    if (!runState) { return; }
    // if sequence is over
    if (!currentSeqCnt--)
    {
        currentSeqCnt = maxTrackTime;
        if (currentSeqNo < 9)
        {
            currentSeqNo++;
            appHND->selectVideoTrack(testNo,currentSeqNo);
        }
        // if end of block reached
        else
        {
            runState = 0;
            ui->timeLBL->setText("--none--");
        }
    }
    ui->timeLBL->setText(QString::number(currentSeqCnt));
    updateCurrentSequence();
    //qDebug() << "Timer is over. SeqNo: " << currentSeqNo << ", SeqCnt: " << currentSeqCnt;

    // if runState is still active restart timer
    if (runState)
    {
        timer->start(1000);
    }
}

void TestExecution::on_playPauseCMDB_clicked()
{
    runState = runState ^ 1;
    // appHND->playPauseTrack(runState);
    if (runState)
    {
        ui->timeLBL->setText(QString::number(currentSeqCnt));
        timer->start(1000);
        appHND->setControl(play);
    }
    else
    {
        ui->timeLBL->setText("paused");
        appHND->setControl(pause);
    }
    updateCurrentSequence();
}

void TestExecution::on_stopCMDB_clicked()
{
    runState = 0;
    currentSeqCnt = maxTrackTime;
    ui->timeLBL->setText("stopped");
    appHND->setControl(stop);
    updateCurrentSequence();
}

void TestExecution::on_backCMDB_clicked()
{
    // if still running reset timer
    if (runState) { timer->start(1000); }
    // reset sequence counter
    currentSeqCnt = maxTrackTime;
    // go one track back
    if (currentSeqNo) {currentSeqNo--;}
    appHND->selectVideoTrack(testNo,currentSeqNo);
    updateCurrentSequence();
}

void TestExecution::on_fwdCMDB_clicked()
{
    // if still running reset timer
    if (runState) { timer->start(1000); }
    // reset sequence counter
    currentSeqCnt = maxTrackTime;
    // go one track forward, stop at the end
    if (currentSeqNo < 9) {currentSeqNo++;}
    else {runState = 0;}
    appHND->selectVideoTrack(testNo,currentSeqNo);
    updateCurrentSequence();
}

void TestExecution::updateCurrentSequence()
{
    for (int i=0; i < 10; i++)
    {
        if (i!=currentSeqNo)
        {
            //make grey
            labels[i]->setStyleSheet("QLabel { background-color : rgb(199,199,199) }");
        }
        else
        {
            if (runState)
            {
                // make green
                labels[i]->setStyleSheet("QLabel { background-color : rgb(78,238,148) }");
            }
            else
            {
                // make red
                labels[i]->setStyleSheet("QLabel { background-color : rgb(238,99,99) }");
            }
        }
    }
}
