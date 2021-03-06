#-------------------------------------------------
#
# Project created by QtCreator 2014-11-17T01:07:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test5
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
    usermanagement.cpp \
    testWindow.cpp \
    testexecution.cpp \
    applicationhandler.cpp \
    client.cpp \
    recordNames.cpp \
    guistartup.cpp \
    closewindow.cpp \
    saveclosewindow.cpp \
    alreadyrecordedwindow.cpp \
    AdaptiveStaircase.cpp

HEADERS  += \
    usermanagement.h \
    testWindow.h \
    testexecution.h \
    applicationhandler.h \
    client.h \
    recordNames.h \
    guistartup.h \
    closewindow.h \
    saveclosewindow.h \
    alreadyrecordedwindow.h \
    AdaptiveStaircase.h

FORMS    += \
    usermanagement.ui \
    testWindow.ui \
    testexecution.ui \
    guistartup.ui \
    closewindow.ui \
    saveclosewindow.ui \
    alreadyrecordedwindow.ui
