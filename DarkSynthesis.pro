#-------------------------------------------------
#
# Project created by QtCreator 2015-07-25T23:21:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DarkSynthesis
TEMPLATE = app


SOURCES += main.cpp \
    cmainwindow.cpp \
    node.cpp \
    edge.cpp \
    graphwidget.cpp \
    cartesiangraph.cpp \
    physparticle.cpp \
    cartesianlabel.cpp \
    cartesiangraphsettingsdlg.cpp \
    physvector.cpp \
    cartesiangraphdataobj.cpp \
    physbaseitem.cpp \
    physobjectnavigator.cpp \
    comboboxdelegate.cpp \
    spinboxdelegate.cpp \
    physmodulenavigator.cpp \
    physoutputnavigator.cpp \
    physobjectpropsnavigator.cpp

HEADERS  += cmainwindow.h \
    node.h \
    edge.h \
    graphwidget.h \
    cartesiangraph.h \
    physparticle.h \
    cartesianlabel.h \
    cartesiangraphsettingsdlg.h \
    physvector.h \
    cartesiangraphdataobj.h \
    physbaseitem.h \
    physobjectnavigator.h \
    comboboxdelegate.h \
    spinboxdelegate.h \
    physmodulenavigator.h \
    physoutputnavigator.h \
    physobjectpropsnavigator.h

FORMS    += cmainwindow.ui \
    cartesiangraphsettingsdlg.ui
