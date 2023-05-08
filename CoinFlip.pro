#-------------------------------------------------
#
# Project created by QtCreator 2023-05-05T17:01:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CoinFlip
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainscene.cpp \
    mypushbutton.cpp \
    chooselevelscene.cpp \
    playscene.cpp \
    mycoin.cpp \
    ../../../大三下/找工作/QT/QT从入门到实战完整版资料/day4资料/Doc/dataconfig.cpp

HEADERS += \
        mainscene.h \
    mypushbutton.h \
    chooselevelscene.h \
    playscene.h \
    mycoin.h \
    ../../../大三下/找工作/QT/QT从入门到实战完整版资料/day4资料/Doc/dataconfig.h

FORMS += \
        mainscene.ui

RESOURCES += \
    res.qrc
