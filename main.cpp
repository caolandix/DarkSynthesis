#include <QApplication>
#include <QTime>
#include <QMainWindow>

#include "cmainwindow.h"
#include "graphwidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    CMainWindow mainWindow;
    GraphWidget *pgraph = new GraphWidget();

    mainWindow.setGraphWidget(pgraph);
    mainWindow.setCentralWidget(pgraph);
    mainWindow.createSignalSlots();
    mainWindow.createBaseObjects();
    mainWindow.show();
    return app.exec();
}
