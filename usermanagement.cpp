#include "usermanagement.h"
#include "ui_usermanagement.h"
#include <QDebug>
#include <QString>
#include "testWindow.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <sstream>

// Constructor
userManagement::userManagement(const char *dbFile, QStringList userList, applicationHandler *appHND, QWidget *parent) : QDialog(parent), ui(new Ui::userManagement)
{
    ui->setupUi(this);

    this->sliderIsPressed = 0;
    this->sliderValChanged = 0;
    this->appHND = appHND;
    this->ui->userCBX->addItems(userList);

    userDBFileName = dbFile;
    userDBCopyName = "temp_DB_Copy.txt";

    runState = 1;
    vidCnt = 10;

    // start timer
    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    // send file name
    this->appHND->selectVideoTrack();
    this->appHND->setControl("play");
}


// Destructor
userManagement::~userManagement()
{
    runState = 0;
    delete ui;
}


// Extract userID as integer from whole user-data string in db
int userManagement::extractUserId(std::string line)
{
    std::string idString;
    for(unsigned int i = 0; i < line.size(); i++)
    {
        if(line[i] != ',') {idString.append(1, line[i]);}
        else {break;}
    }
    // get new user id integer from line user id string
    int lineID;
    std::stringstream convert(idString); // stringstream used for the conversion initialized with the contents of Text
    if ( !(convert >> lineID) ) {lineID = 0;} //give the value to Result using the characters in the string, if that fails set Result to 0
    return lineID;
}


// Closes the window, discarding changes
void userManagement::on_closeCMDB_clicked()
{
    runState = 0;
    this->close();
}


// Closes the window after calling Update Userlist in testWindow
void userManagement::on_okCMDB_clicked()
{
    // Check if Parent Connection is well established
    if (qobject_cast<testWindow*>(parent()) == 0)
    {
        qDebug() << "Parent of Parent is not MainWindow !";
        return;
    }

    // write GUI specified parameters into strings for easy adressing
    std::string userName = ui->userNameTXT->text().toUtf8().constData();
    std::string eyeDist = ui->eyeDistTXT->text().toUtf8().constData();
    std::string birthday = ui->birthdayTXT->text().toUtf8().constData();
    std::string userGroup = ui->groupTXT->text().toUtf8().constData();

    // If nothing was entered --> exit
    if (userName == "")
    {
        runState = 0;
        this->close();
    }
    // If New User is beeing created
    else if (ui->userNewCB->isChecked())
    {
        // get highest userID
        std::ifstream userReadIdFile(userDBFileName);
        std::string line;
        while (userReadIdFile >> std::ws && std::getline(userReadIdFile, line)); // skip empty lines
        userReadIdFile.close();
        // extract user id from line
        int highestID = extractUserId(line);
        if (highestID == 0) {highestID = 99;}
        int userID = highestID+1;

        // add to user list DB
        std::ofstream userWriteIdFile;
        userWriteIdFile.open(userDBFileName, std::ofstream::out | std::ofstream::app);
        userWriteIdFile << userID << "," << userName << "," << eyeDist << "," << birthday << "," << userGroup << "\n";
        userWriteIdFile.close();

        // add to dropdown user lists of parent window
        qobject_cast<testWindow*>(parent())->updateUserList(ui->userNameTXT->text(), 1);
    }
    else // just update user details
    {
        // make a copy of the DB
        std::ifstream origFile(userDBFileName); //File to read from
        std::ofstream copyFile(userDBCopyName); //Temporary file
        if(!origFile || !copyFile) {qDebug() << "Error opening files!";}
        copyFile << origFile.rdbuf();
        origFile.close();
        copyFile.close();

        std::string strReplace =  qobject_cast<testWindow*>(parent())->getDBentry(ui->userNameTXT->text());
        // user ID stays unmodified
        int userID = extractUserId(strReplace);
        if (userID < 100) {qDebug() << "Error with old userID!";}
        std::stringstream sstrNew;
        sstrNew << userID << "," << userName << "," << eyeDist << "," << birthday << "," << userGroup;
        std::string strNew = sstrNew.str();

        std::ifstream userReadIdFile(userDBCopyName);
        std::ofstream userWriteIdFile(userDBFileName);
        if(!userReadIdFile || !userWriteIdFile) {qDebug() << "Error opening files!";}

        std::string strTemp;                //bool found = false;
        while(getline(userReadIdFile, strTemp))
        {
            if(strTemp == strReplace)
            {
                strTemp = strNew;           //found = true;
            }
            strTemp += "\n";
            userWriteIdFile << strTemp;     //if(found) break;
        }
        userReadIdFile.close();
        userWriteIdFile.close();
    }

    // make current entry in parent window dropdown list
    qobject_cast<testWindow*>(parent())->setCurrentUser(ui->userNameTXT->text());

    runState = 0;
    this->close();
}


// Deletes current
void userManagement::on_delCMDB_clicked()
{
    // make a copy of the DB
    std::ifstream origFile(userDBFileName); //File to read from
    std::ofstream copyFile(userDBCopyName); //Temporary file
    if(!origFile || !copyFile) {qDebug() << "Error opening files!";}
    copyFile << origFile.rdbuf();
    origFile.close();
    copyFile.close();

    std::string strReplace =  qobject_cast<testWindow*>(parent())->getDBentry(ui->userNameTXT->text());
    std::ifstream userReadIdFile(userDBCopyName);
    std::ofstream userWriteIdFile(userDBFileName);
    if(!userReadIdFile || !userWriteIdFile) {qDebug() << "Error opening files!";}

    std::string strTemp;                //bool found = false;
    while(getline(userReadIdFile, strTemp))
    {
        if(strTemp == strReplace)
        {
            strTemp = "";               //found = true;
        }
        else
        {
            strTemp += "\n";
        }
        userWriteIdFile << strTemp;     //if(found) break;
    }
    userReadIdFile.close();
    userWriteIdFile.close();

    // remove from both CBXs
    qobject_cast<testWindow*>(parent())->updateUserList(ui->userNameTXT->text(),-1);
    ui->userCBX->clear();
    ui->userCBX->addItems(qobject_cast<testWindow*>(parent())->getUserList());
}

void userManagement::on_userCBX_currentTextChanged(const QString &arg1)
{
    // get details from db
    std::string userDetails =  qobject_cast<testWindow*>(parent())->getDBentry(arg1);

    std::string userData[5];
    int dataIndex = 0;
    for(unsigned int i = 0; i < userDetails.size(); i++)
    {
        if(userDetails[i] != ',') {userData[dataIndex].append(1, userDetails[i]);}
        else {dataIndex++;}
    }

    ui->userNewCB->setChecked(false);
    ui->userNameTXT->setText(QString::fromUtf8( userData[1].data(), userData[1].size() ));
    ui->eyeDistTXT->setText(QString::fromUtf8( userData[2].data(), userData[2].size() ));
    ui->birthdayTXT->setText(QString::fromUtf8( userData[3].data(), userData[3].size() ));
    ui->groupTXT->setText(QString::fromUtf8( userData[4].data(), userData[4].size() ));
    ui->idLBL->setText(QString::fromUtf8( userData[0].data(), userData[0].size() ));
}


// hides user id of currently selected user, when entering data for new user
void userManagement::on_userNewCB_clicked()
{
    ui->idLBL->setText("set after confirmation");
}

void userManagement::on_eyeDistSlider_sliderPressed()
{
    sliderIsPressed = 0;
    if (sliderValChanged)
    {
        sliderValChanged = 0;
        int eyeDistMax = 400;
        int value = ceil(eyeDistMax * ui->eyeDistSlider->value() / 99) -200;
        QString str = QString::number(value);
        appHND->setViewport_Offset(str);
    }
}

void userManagement::on_eyeDistSlider_sliderReleased()
{
    sliderIsPressed = 1;
}

void userManagement::on_eyeDistSlider_valueChanged(int value)
{
    int eyeDistMax = 400;
    value = ceil(eyeDistMax * value / 99) -200;
    ui->eyeDistTXT->setText(QString::number(value));
    // ensure not to send 100 signals a second
    if (!sliderIsPressed)
    {
        QString str = QString::number(value);
        appHND->setViewport_Offset(str);
    }
    else
    {
        sliderValChanged = 1;
    }
}


void userManagement::update()
{
    // if timer should actually be stopped, but is just running out
    if (!runState) { return; }

    // if sequence is over
    if (!vidCnt--)
    {
        qDebug() << "usermanagement timer elapsed 10 times -> restart video";
        appHND->setControl("stop");
        appHND->setControl("play");
        vidCnt = 10;
    }

    // if runState is still active restart timer
    if (runState) { timer->start(1000); }
}
