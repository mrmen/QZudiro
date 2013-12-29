#-------------------------------------------------
#
# Project created by QtCreator 2013-10-24T23:37:38
#
#-------------------------------------------------

QT       += core gui
LIBS     += -ltinyxml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QZudiro
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    zudirogrid.cpp

HEADERS  += mainwindow.h \
    zudirogrid.h

FORMS    += mainwindow.ui
