#-------------------------------------------------
#
# Project created by QtCreator 2016-02-05T23:28:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Graphytti
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    exptcycle.cpp \
    interactiveplot.cpp \
    exponeplotter.cpp \
    anisoplotter.cpp \
    exptcycle2.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    exptcycle.h \
    interactiveplot.h \
    graphplotter.h \
    exponeplotter.h \
    anisoplotter.h \
    exptcycle2.h

RESOURCES += \
    icons.qrc


