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
    void createToolBars();
    void createStatusBar();
    void createDockWindows();
    void ReadXMLFile(QXmlStreamReader &, QFile &);
    void WriteXMLFile(QXmlStreamWriter &, QFile &);

    // properties
    QLabel *m_infoLabel;

    PhysObjectNavigator *m_pPhysObjNavigator = nullptr;
    PhysObjectPropsNavigator *m_pPhysObjPropsNavigator = nullptr;
    PhysModuleNavigator *m_pPhysModNavigator = nullptr;
    PhysOutputNavigator *m_pPhysOutputNavigator = nullptr;
    PhysEqSolverTable *m_pPhysEqSolver = nullptr;
    PhysElectroStaticView *m_pPhysElectroStaticView = nullptr;
    Ui::CMainWindow *m_pUI = nullptr;
    GraphWidget *m_pGraphWidget = nullptr;
};

#endif // CMAINWINDOW_H
