#-------------------------------------------------
#
# Project created by QtCreator 2015-07-25T23:21:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DarkSynthesis
TEMPLATE = app


SOURCES += main.cpp\
        cmainwindow.cpp \
    node.cpp \
    edge.cpp \
    graphwidget.cpp \
    darksynthwidget.cpp \
    cartesiangraph.cpp \
    physparticle.cpp \
    cartesianlabel.cpp

HEADERS  += cmainwindow.h \
    node.h \
    edge.h \
    graphwidget.h \
    darksynthwidget.h \
    cartesiangraph.h \
    physparticle.h \
    cartesianlabel.h

FORMS    += cmainwindow.ui
