#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QtWidgets>

#include "graphwidget.h"
#include "physcommon.h"

class PhysObjectNavigator;
class PhysObjectPropsNavigator;
class PhysModuleNavigator;
class PhysOutputNavigator;
class PhysEqSolver;

namespace Ui {
    class CMainWindow;
}

class CMainWindow : public QMainWindow, public PhysCommon {
    Q_OBJECT
public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

    void setGraphWidget(GraphWidget *pObj) { m_pGraphWidget = pObj; }

    PhysObjectNavigator *getPhysObjNavigator() const { return m_pPhysObjNavigator; }
    PhysObjectPropsNavigator *getPhysObjPropsNavigator() const { return m_pPhysObjPropsNavigator; }
    PhysModuleNavigator *getPhysModuleNavigator() const { return m_pPhysModNavigator; }
    PhysOutputNavigator *getPhysOutputNavigator() const { return m_pPhysOutputNavigator; }
    GraphWidget *getGraphWidget() const { return m_pGraphWidget; }

    void createSignalSlots();
    void createBaseObjects();
private:
    Ui::CMainWindow *m_pUI;
    GraphWidget *m_pGraphWidget;
protected:
    void contextMenuEvent(QContextMenuEvent *) Q_DECL_OVERRIDE;
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
    void init();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();
    void ReadXMLFile(QXmlStreamReader &, QFile &);
    void WriteXMLFile(QXmlStreamWriter &, QFile &);
    void connectWindowsWithPhysObjects();

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

    PhysObjectNavigator *m_pPhysObjNavigator;
    PhysObjectPropsNavigator *m_pPhysObjPropsNavigator;
    PhysModuleNavigator *m_pPhysModNavigator;
    PhysOutputNavigator *m_pPhysOutputNavigator;
    PhysEqSolver *m_pPhysEqSolver;
};

#endif // CMAINWINDOW_H
