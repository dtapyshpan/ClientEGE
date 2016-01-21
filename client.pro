#-------------------------------------------------
#
# Project created by QtCreator 2016-01-13T12:02:32
#
#-------------------------------------------------

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = client
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
           mainwindow.cpp \
    configreader.cpp \
    gradevalidator.cpp \
    namevalidator.cpp

HEADERS += mainwindow.h \
    schoolnameconsts.h \
    pupil.h \
    exams.h \
    configreader.h \
    gradevalidator.h \
    namevalidator.h

FORMS += mainwindow.ui
