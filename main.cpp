#include "cmainwindow.h"
#include "graphwidget.h"
#include "darksynthwidget.h"

#include <QApplication>
#include <QTime>
#include <QMainWindow>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    CMainWindow mainWindow;
    GraphWidget *pgraph = new GraphWidget();
    DarkSynthWidget *pDSWidget = NULL;

    mainWindow.setGraphWidget(pgraph);
    mainWindow.setCentralWidget(pgraph);
    mainWindow.show();
    return app.exec();
}
