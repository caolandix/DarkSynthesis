#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>

class GraphWidget;

namespace Ui {
    class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

    void setGraphWidget(GraphWidget *pObj) { graph_widget = pObj; };

private:
    Ui::CMainWindow *ui;

    GraphWidget *graph_widget;
};

#endif // CMAINWINDOW_H
