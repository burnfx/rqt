#include "testWindow.h"
#include "ui_testWindow.h"
#include "main.cpp"
#include <QDebug>
#include <QString>
#include "usermanagement.h"
#include "testexecution.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>

// Constructor: Init with database values
testWindow::testWindow(applicationHandler *appHND, QWidget *parent) : QMainWindow(parent), ui(new Ui::testWindow)
{
    ui->setupUi(this);
    userDBFileName = "user_db.txt";
    this->appHND = appHND;
    //int value = 5;
    //this->appHND->setViewport_Offset(value);
    char* mode = "2";
    //appHND->setMode(mode);

    // set up test block buttons

    //start_test_button = new testExecButton(this);
    //connect(start_test_button, SIGNAL(clicked(int)), this, SLOT(openTestRecordingWindow(int)));


    // get user list from DB
    std::ifstream testFile(userDBFileName);
    if(!testFile)
    {
        qDebug() << "Error opening DB!";
        std::ofstream testDataFile;
        testDataFile.open(userDBFileName, std::ofstream::out | std::ofstream::app);
        testDataFile.close();
    }
    else
    {
        testFile.close();
    }

    std::ifstream userFile(userDBFileName);
    std::string strTemp;
    while(getline(userFile, strTemp))
    {
        std::string userNameEntry;
        int dataIndex = 0;
        for(unsigned int i = 0; i < strTemp.size(); i++)
        {
            if((strTemp[i] != ',') && (dataIndex != 0))  {userNameEntry.append(1, strTemp[i]);}
            else if (strTemp[i] == ',') {dataIndex++;}
            if (dataIndex>1){break;}
        }
        userList << QString::fromUtf8( userNameEntry.data(), userNameEntry.size() );
    }
    userFile.close();

    ui->userCBX->clear();
    ui->userCBX->addItems(userList);
}


// Destructor
testWindow::~testWindow()
{
    appHND->closeGUI();
    delete ui;
}


// Get Function
QStringList testWindow::getUserList()
{
    return userList;
}


// Set current entry in user dropdown list
void testWindow::setCurrentUser(QString userName)
{
    int index = userList.indexOf(userName, 0);

    if ( index != -1 )
    {
        ui->userCBX->setCurrentIndex(index);
        on_userCBX_currentTextChanged(ui->userCBX->currentText());
    }
    else
    {
        qDebug() << "Error: Didn't find entry in Dropdown List";
    }
}


// get data of userName - db entry
std::string testWindow::getDBentry(QString userName)
{
    std::ifstream readFile(userDBFileName);
    std::string line;
    std::string errorString = "error,error,error,error";

    if (readFile.is_open())
      {
        while ( getline (readFile,line) )
        {
            //compare second entry
            std::string lineName;
            int userIdFlag = 1;
            for(unsigned int i = 0; i < line.size(); i++)
            {
                if((line[i] != ',') && (userIdFlag != 1))
                {
                    lineName.append(1, line[i]);
                }
                else if ((line[i] == ','))
                {
                    userIdFlag--;
                }

                if (userIdFlag < 0)
                {
                    if (lineName == userName.toStdString())
                    {
                        readFile.close();
                        return line;
                    }
                    else {break;}
                }
            }
        }
        qDebug() << "User not found in DB, may be corrupted";
        readFile.close();
        return errorString;
      }
    else
    {
        qDebug() << "Couldn't find or open DB";
        return errorString;
    }
}


// Updates the user list in dropdown menu and adjusts parameters
void testWindow::updateUserList(QString userName, int addNewIfOne)
{
    // if new user is added
    if (addNewIfOne == 1)
    {
        userList << userName;
    }
    // if user to be deleted
    else if (addNewIfOne == -1)
    {
        int index = userList.indexOf(userName, 0);
        userList.removeAt(index);
    }
    else
    {
        qDebug() << "Error, calling updateUserList function.";
        return;
    }
    ui->userCBX->clear();
    ui->userCBX->addItems(userList);
}


void testWindow::updateExecutedTests()
{
    // set all buttons grey first

    std::string tempStr = ui->userParamValLBL_3->text().toUtf8().constData();
    std::string userDBFile = "testdata_userID_" + tempStr + ".txt";

    std::ifstream readFile(userDBFile.c_str());
    std::string line;

    /*
    // now check for test already executed
    if (readFile.is_open())
    {
        // for each line
        while ( getline (readFile,line) )
        {
            //compare second entry
            std::string lineName[3];
            int csvCNT = 0;
            for(unsigned int i = 0; i < line.size(); i++)
            {
                if (line[i] != ',')
                {
                    lineName[csvCNT].append(1, line[i]);
                }
                else if (line[i] == ',')
                {
                    csvCNT++;
                }

                if (csvCNT == 3)
                {
                    if (lineName[0] == "testBlock")
                    {
                        // check for all blocks
                        if (lineName[2]=="complete=false")
                        {
                            buttons[atoi(lineName[1].c_str())-1]->setStyleSheet("* { background-color: rgb(160,0,0) }");
                        }
                        else if (lineName[2]=="complete=true")
                        {
                            buttons[atoi(lineName[1].c_str())-1]->setStyleSheet("* { background-color: rgb(0,100,0) }");
                        }
                        else
                        {
                            qDebug() << "DB file seems to be corrupt.";
                        }
                    }
                    break;
                }
            }
        }
        readFile.close();
    }
    */
}


// Close Window
void testWindow::on_closeCMDB_clicked()
{
    this->close();
}


// Open User Management
void testWindow::on_userCMDB_clicked()
{
    um = new userManagement(userDBFileName, userList, appHND, this);
    um->show();
}


// On User Switch adjust parameters and labels
void testWindow::on_userCBX_currentTextChanged(const QString &arg1)
{
    if (arg1 == ""){return;}
    std::string userDetails =  getDBentry(arg1);

    std::string userData[5];
    int dataIndex = 0;
    for(unsigned int i = 0; i < userDetails.size(); i++)
    {
        if(userDetails[i] != ',') {userData[dataIndex].append(1, userDetails[i]);}
        else {dataIndex++;}
    }

    ui->userParamValLBL_1->setText(QString::fromUtf8( userData[2].data(), userData[2].size() ));
    ui->userParamValLBL_2->setText(QString::fromUtf8( userData[3].data(), userData[3].size() ));
    ui->userParamValLBL_3->setText(QString::fromUtf8( userData[0].data(), userData[0].size() ));
    ui->userParamValLBL_4->setText(QString::fromUtf8( userData[4].data(), userData[4].size() ));
    updateExecutedTests();
}


// Start test No X, Open new window accordingly to save results
void testWindow::openTestRecordingWindow(int bNum)
{
    /*
    // set file names
    std::string userDBCopyName = "temp_DB_Copy.txt";
    std::string userDBFileNameLocal = ui->userParamValLBL_3->text().toUtf8().constData();
    userDBFileNameLocal = "testdata_userID_" + userDBFileNameLocal + ".txt";

    // check if test block was recorded before and act accordingly
    std::ifstream origFile(userDBFileNameLocal.c_str()); //File to read from
    if (origFile)
    {
        // make a copy of the DB
        std::ofstream copyFile(userDBCopyName.c_str()); //Temporary file
        if(!origFile || !copyFile) {qDebug() << "Error opening files!";}
        copyFile << origFile.rdbuf();
        origFile.close();
        copyFile.close();

        // check if block was already executed
        std::ifstream readFile(userDBFileNameLocal.c_str());
        std::string line;
        int alrExAtLine = 0;
        if (readFile.is_open())
        {
            // for each line
            int lineCnt = 0;
            while ( getline (readFile,line) )
            {
                lineCnt++;
                std::string lineName[3];
                int csvCNT = 0;
                for(unsigned int i = 0; i < line.size(); i++)
                {
                    if (line[i] != ',') {lineName[csvCNT].append(1, line[i]);}
                    else if (line[i] == ',') {csvCNT++;}

                    if (csvCNT == 3)
                    {
                        if (lineName[0] == "testBlock")
                        {
                            if (atoi(lineName[1].c_str()) == bNum)
                            {
                                alrExAtLine = lineCnt;
                            }
                        }
                        break;
                    }
                }
            }
            readFile.close();
        }

        // Window: would you like to overwrite?
        if (alrExAtLine)
        {
            alreadyRecordedWindow aWnd;
            aWnd.setModal(true);
            if (aWnd.exec()!=QDialog::Accepted) {return;}

            // Overwriting Procedure
            std::ifstream userReadDBFile(userDBCopyName.c_str());
            std::ofstream userWriteDBFile(userDBFileNameLocal.c_str());
            if(!userReadDBFile || !userWriteDBFile) {qDebug() << "Error opening files!";}

            std::string strTemp;
            int lineCnt = 0;
            while(getline(userReadDBFile, strTemp))
            {
                lineCnt++;
                if (!((lineCnt>=alrExAtLine) && (lineCnt<alrExAtLine+3)))
                {
                    strTemp += "\n";
                    userWriteDBFile << strTemp;
                }
            }
            userReadDBFile.close();
            userWriteDBFile.close();
        }
    }

    te = new TestExecution(ui->userCBX->currentText(), ui->userParamValLBL_3->text(), ui->supervisorEdit->text(), appHND, this);
    te->show();
    QObject::connect(te, SIGNAL(recordsUpdated()), this, SLOT(exRecordUpdate()));
    */
}


void testWindow::exRecordUpdate()
{
    updateExecutedTests();
}

void testWindow::on_check_1_stateChanged(int arg1)
{
    QString str = QString::number(arg1);
    appHND->setRedGreen(str);
}

void testWindow::on_recordCMDB_clicked()
{
    //char *recordName;
    //recordName = applicationHandler::qstringtoChar(ui->recordNameLineEdit->text());
    //std::string recordNameStr = ui->recordNameLineEdit->text().toUtf8().constData();
    //recordName = new char[recordNameStr.length() + 1];
    //strcpy(recordName,recordNameStr.c_str());
    //qDebug() << ui->recordNameLineEdit->text();
    //appHND->setFile(recordName);
    //appHND->setFile(ui->recordNameLineEdit->text());
    // char *recordTime = applicationHandler::qstringtoChar(ui->recordTimeLineEdit->text());
    //char *recordTime;
    //std::string recordTimeStr = ui->recordTimeLineEdit->text().toUtf8().constData();
    //recordTime = new char[recordTimeStr.length() + 1];
    //strcpy(recordTime,recordTimeStr.c_str());
    // appHND->setTime(recordTime);
    //appHND->setTime(ui->recordTimeLineEdit->text());
    // QString mode = "2";
    //appHND->setMode(mode);
    //appHND->setMode(mode);
    appHND->setFile(ui->recordNameLineEdit->text());
    usleep(100);
    QString play = "play";
    appHND->setControl(play);
}

void testWindow::on_stopCMDB_clicked()
{
    QString stop = "stop";
    appHND->setControl(stop);
}

void testWindow::on_setFileCMDB_clicked()
{
    appHND->setFile(ui->recordNameLineEdit->text());
}

void testWindow::on_setModeCMDB_clicked()
{
    appHND->setMode(ui->modeLineEdit->text());
}

void testWindow::on_start_test_button_clicked()
{
    //TestExecution w(appHND,this);
    te = new TestExecution(appHND, this);
    te->show();
    //w->show();
}
