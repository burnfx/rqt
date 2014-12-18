#include "testWindow.h"
#include "ui_testWindow.h"
#include "main.cpp"
#include <QDebug>
#include "usermanagement.h"
#include "testexecution.h"
#include <iostream>
#include <fstream>
#include <string.h>

// Constructor: Init with database values
testWindow::testWindow(applicationHandler *appHND, QWidget *parent) : QMainWindow(parent), ui(new Ui::testWindow)
{
    ui->setupUi(this);
    userDBFileName = "user_id.txt";
    this->appHND = appHND;

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


// Close Window
void testWindow::on_closeCMDB_clicked()
{
    this->close();
}


// MISSING - Save and apply Parameter Values
void testWindow::on_applyCMDB_clicked()
{
    qDebug() << "Not implemented - apply something.";
}


// MISSING - Set all values as default
void testWindow::on_defaultCMDB_clicked()
{
    qDebug() << "Not implemented - restore default values.";
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

    std::string userData[4];
    int dataIndex = 0;
    for(unsigned int i = 0; i < userDetails.size(); i++)
    {
        if(userDetails[i] != ',') {userData[dataIndex].append(1, userDetails[i]);}
        else {dataIndex++;}
    }

    ui->userParamValLBL_1->setText(QString::fromUtf8( userData[2].data(), userData[2].size() ));
    ui->userParamValLBL_2->setText(QString::fromUtf8( userData[3].data(), userData[3].size() ));
    ui->userParamValLBL_3->setText(QString::fromUtf8( userData[0].data(), userData[0].size() ));
}


// For all the following
// Start test No X, Open new window accordingly to save results
void testWindow::on_testCMDB_1_clicked()
{
    te = new TestExecution(1, ui->userCBX->currentText(), ui->userParamValLBL_3->text(), ui->supervisorEdit->text(), appHND, this);
    te->show();
}

void testWindow::on_testCMDB_2_clicked()
{
    te = new TestExecution(2, ui->userCBX->currentText(), ui->userParamValLBL_3->text(), ui->supervisorEdit->text(), appHND, this);
    te->show();
}

void testWindow::on_testCMDB_3_clicked()
{
    te = new TestExecution(3, ui->userCBX->currentText(), ui->userParamValLBL_3->text(), ui->supervisorEdit->text(), appHND, this);
    te->show();
}

void testWindow::on_testCMDB_4_clicked()
{
    te = new TestExecution(4, ui->userCBX->currentText(), ui->userParamValLBL_3->text(), ui->supervisorEdit->text(), appHND, this);
    te->show();
}

void testWindow::on_testCMDB_5_clicked()
{
    te = new TestExecution(5, ui->userCBX->currentText(), ui->userParamValLBL_3->text(), ui->supervisorEdit->text(), appHND, this);
    te->show();
}

void testWindow::on_testCMDB_6_clicked()
{
    te = new TestExecution(6, ui->userCBX->currentText(), ui->userParamValLBL_3->text(), ui->supervisorEdit->text(), appHND, this);
    te->show();
}

void testWindow::on_testCMDB_7_clicked()
{
    te = new TestExecution(7, ui->userCBX->currentText(), ui->userParamValLBL_3->text(), ui->supervisorEdit->text(), appHND, this);
    te->show();
}

void testWindow::on_testCMDB_8_clicked()
{
    te = new TestExecution(8, ui->userCBX->currentText(), ui->userParamValLBL_3->text(), ui->supervisorEdit->text(), appHND, this);
    te->show();
}

void testWindow::on_testCMDB_9_clicked()
{
    te = new TestExecution(9, ui->userCBX->currentText(), ui->userParamValLBL_3->text(), ui->supervisorEdit->text(), appHND, this);
    te->show();
}

void testWindow::on_check_1_stateChanged(int arg1)
{
    appHND->setRedGreen(arg1);
}
