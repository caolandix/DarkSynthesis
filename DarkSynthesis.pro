#-----------------------------------------------
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
    physobjectpropsnavigator.cpp \
    physmodule.cpp \
    physeqsolver.cpp \
    physprintview.cpp \
    physeqsolverdelegate.cpp \
    physeqsolveritem.cpp \
    physvectordataobj.cpp \
    physparticledataobj.cpp \
    xes1/es1.cpp \
    xes1/fft.cpp \
    xes1/fields.cpp \
    xes1/init.cpp \
    xes1/initwin.cpp \
    xes1/move.cpp \
    xes1/set.cpp \
    xes1/physelectrostatic.cpp \
    xes1/accel.cpp \
    physctrllineedit.cpp

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
    physobjectpropsnavigator.h \
    physmodule.h \
    physscience.h \
    physeqsolver.h \
    physprintview.h \
    physeqsolverdelegate.h \
    physeqsolveritem.h \
    physvectordataobj.h \
    physparticledataobj.h \
    xes1/es1.h \
    xes1/physelectrostatic.h \
    physctrllineedit.h

FORMS    += cmainwindow.ui \
    cartesiangraphsettingsdlg.ui
