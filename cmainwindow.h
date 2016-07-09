#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QtWidgets>

#include "graphwidget.h"
#include "physcommon.h"
#include "xes1/physelectrostaticview.h"

class PhysObjectNavigator;
class PhysObjectPropsNavigator;
class PhysModuleNavigator;
class PhysOutputNavigator;
class PhysEqSolverTable;

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
    void setupMenu();
    void setupToolBars();
    void createActions();
    void setupStatusBar();
    void createDockWindows();
    void ReadXMLFile(QXmlStreamReader &, QFile &);
    void WriteXMLFile(QXmlStreamWriter &, QFile &);

    // properties
    QLabel *m_infoLabel;

    PhysObjectNavigator *m_pPhysObjNavigator;
    PhysObjectPropsNavigator *m_pPhysObjPropsNavigator;
    PhysModuleNavigator *m_pPhysModNavigator;
    PhysOutputNavigator *m_pPhysOutputNavigator;
    PhysEqSolverTable *m_pPhysEqSolver;
    PhysElectroStaticView *m_pPhysElectroStaticView;
    Ui::CMainWindow *m_pUI;
    GraphWidget *m_pGraphWidget;
    QGraphicsView *m_pView;

    QAction *m_pDeleteAction;
    QAction *m_pAboutAction;
    QAction *m_pExitAction;
    QToolBar *m_pEditToolBar;
    QToolBar *m_pPointerToolbar;

    QToolBox *m_pToolBox;
    QButtonGroup *m_pButtonGroup;
    QButtonGroup *m_pPointerTypeGroup;
};

#endif // CMAINWINDOW_H
