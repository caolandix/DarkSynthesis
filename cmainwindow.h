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
    void createToolBars();
    void createStatusBar();
    void createDockWindows();
    void ReadXMLFile(QXmlStreamReader &, QFile &);
    void WriteXMLFile(QXmlStreamWriter &, QFile &);

    // properties
    QMenu *m_pFileMenu;
    QMenu *m_pEditMenu;
    QMenu *m_pHelpMenu;
    QMenu *m_pSettingsMenu;
    QAction *m_pcartGraphSettings;
    QAction *m_pactNew;
    QAction *m_pactOpen;
    QAction *m_pactSave;
    QAction *m_pactPrint;
    QAction *m_pactExit;
    QAction *m_pactAbout;
    QAction *m_pactAboutQt;
    QLabel *m_infoLabel;
};

#endif // CMAINWINDOW_H
