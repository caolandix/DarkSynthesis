#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QLabel>
#include <QFile>
#include <QXmlStreamReader>

#include "graphwidget.h"

namespace Ui {
    class CMainWindow;
}

class CMainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

    void setGraphWidget(GraphWidget *pObj) { graph_widget = pObj; }
private:
    Ui::CMainWindow *ui;
    GraphWidget *graph_widget;
protected:
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
private slots:
    void cartesianGraphOptions();
    void newFile();
    void open();
    void save();
    void print();
    void about();
    void aboutQt();

private:

    // methods
    void createActions();
    void createMenus();
    void ReadXMLFile(QXmlStreamReader &, QFile &);
    void WriteXMLFile(QXmlStreamWriter &, QFile &);

    // properties
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QMenu *m_pSettingsMenu;
    QAction *m_pcartGraphSettings;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QLabel *infoLabel;
};

#endif // CMAINWINDOW_H
