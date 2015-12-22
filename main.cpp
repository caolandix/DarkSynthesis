#include <QtWidgets>

#include "cmainwindow.h"
#include "graphwidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CMainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
