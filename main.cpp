#include <QtWidgets>

#include "cmainwindow.h"
#include "graphwidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CMainWindow mainWindow;
    GraphWidget *pGraph = new GraphWidget();

    mainWindow.setGraphWidget(pGraph);
    mainWindow.setCentralWidget(pGraph);
    mainWindow.createSignalSlots();
    mainWindow.createBaseObjects();
    mainWindow.show();
    return app.exec();
}
