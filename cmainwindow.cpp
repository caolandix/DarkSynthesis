// C++ headers
#include <iostream>

// QT headers
#include <QtWidgets>

// DarkSynth headers
#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include "cartesiangraphsettingsdlg.h"
#include "cartesiangraphdataobj.h"
#include "physobjectnavigator.h"
#include "physmodulenavigator.h"
#include "physoutputnavigator.h"
#include "physobjectpropsnavigator.h"
#include "physeqsolvertable.h"
#include "physdockedwidget.h"
#include "xes1/physelectrostaticview.h"
#include "modulenavigator.h"
#include "objectnavigator.h"
#include "physobjectpropsnavigatordock.h"
#include "physequationsolverdock.h"
#include "physmodulenavigatormodel.h"
#include "physoutputnavigatordock.h"
#include "physcommon.h"

using namespace std;

CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent), m_pUI(new Ui::CMainWindow) , PhysCommon() {
    init();
    m_pUI -> setupUi(this);
    m_infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to invoke a context menu</i>"));
    m_infoLabel -> setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    m_infoLabel -> setAlignment(Qt::AlignCenter);
    setupMenu();
    createActions();
    setupToolBars();
    setupStatusBar();
    createDockWindows();

    GraphWidget *pGraph = new GraphWidget(this);

    setGraphWidget(pGraph);
    setCentralWidget(pGraph);
    createSignalSlots();
    createBaseObjects();
    setWindowTitle(tr("The Physicist's Workbench"));
}

CMainWindow::~CMainWindow() {
    delete m_pUI;
}

void CMainWindow::init() {
    m_pPhysObjNavigator = NULL;
    m_pPhysObjPropsNavigator = NULL;
    m_pPhysModNavigator = NULL;
    m_pPhysOutputNavigator = NULL;
    m_pPhysEqSolver = NULL;
}

void CMainWindow::contextMenuEvent(QContextMenuEvent *) {
    QMenu menu(this);
}

void CMainWindow::print() {
    m_infoLabel->setText(tr("Invoked <b>File|Print</b>"));
}

void CMainWindow::about() {
    m_infoLabel -> setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About Menu"), tr("The <b>Menu</b> example shows how to create menu-bar menus and context menus."));
}

void CMainWindow::aboutQt() {
    m_infoLabel -> setText(tr("Invoked <b>Help|About Qt</b>"));
}

void CMainWindow::cartesianGraphOptions() {
    CartesianGraphSettingsDlg dlg(m_pGraphWidget -> cartesianGraph() -> DataObj());
    if (dlg.exec() == QDialog::Accepted) {
    }
}

void CMainWindow::setupMenu() {
    m_pUI ->ui_mainMenuBar;
}

void CMainWindow::createActions() {
    m_pDeleteAction = new QAction(QIcon("images/delete.png"), tr("&Delete"), this);
    m_pDeleteAction ->setShortcut(tr("Delete"));
    m_pDeleteAction ->setStatusTip(tr("Delete item from diagram"));
    connect(m_pDeleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    m_pExitAction = new QAction(tr("E&xit"), this);
    m_pExitAction ->setShortcuts(QKeySequence::Quit);
    m_pExitAction ->setStatusTip(tr("Quit Dark Synthesis"));
    connect(m_pExitAction, SIGNAL(triggered()), this, SLOT(close()));

    m_pAboutAction = new QAction(tr("A&bout"), this);
    m_pAboutAction ->setShortcut(tr("F1"));
    connect(m_pAboutAction, SIGNAL(triggered()), this, SLOT(about()));
}


void CMainWindow::setupToolBars() {
    m_pUI ->ui_mainToolBar;

    m_pEditToolBar = addToolBar(tr("Edit"));
    m_pEditToolBar ->addAction(m_pDeleteAction);

    QToolButton *pPointerButton = new QToolButton;
    pPointerButton ->setCheckable(true);
    pPointerButton ->setChecked(true);
    pPointerButton ->setIcon(QIcon("images/icons/pointer.png"));
    QToolButton *pLinePointerButton = new QToolButton;
    pLinePointerButton ->setCheckable(true);
    pLinePointerButton ->setIcon(QIcon("images/icons/linepointer.png"));

    m_pPointerTypeGroup = new QButtonGroup(this);
    m_pPointerTypeGroup ->addButton(pPointerButton, int(GraphWidget::MoveItem));
    m_pPointerTypeGroup ->addButton(pLinePointerButton, int(GraphWidget::InsertLine));
    connect(m_pPointerTypeGroup, SIGNAL(buttonClicked(int)), this, SLOT(pointerGroupClicked(int)));

    m_pPointerToolbar = addToolBar(tr("Pointer type"));
    m_pPointerToolbar ->addWidget(pPointerButton);
    m_pPointerToolbar ->addWidget(pLinePointerButton);
}

void CMainWindow::setupStatusBar() {
}

void CMainWindow::createDockWindows() {

    // Create the left side
    ModuleNavigator *pDock = new ModuleNavigator(this);
    m_pPhysModNavigator = new PhysModuleNavigator(pDock);
    m_pPhysModNavigator ->setModel(new PhysModuleNavigatorModel());
    pDock -> setWidget(m_pPhysModNavigator);
    addDockWidget(Qt::LeftDockWidgetArea, pDock);

    // Create the right side
    ObjectNavigator *pObjNavDock = new ObjectNavigator(this);
    m_pPhysObjNavigator = new PhysObjectNavigator(pObjNavDock);
    pObjNavDock -> setWidget(m_pPhysObjNavigator);
    addDockWidget(Qt::RightDockWidgetArea, pObjNavDock);

    PhysObjectPropsNavigatorDock *pObjPropsNavDock = new PhysObjectPropsNavigatorDock(this);
    m_pPhysObjPropsNavigator = new PhysObjectPropsNavigator(pObjPropsNavDock);
    pObjPropsNavDock -> setWidget(m_pPhysObjPropsNavigator);
    addDockWidget(Qt::RightDockWidgetArea, pObjPropsNavDock);

    // Create the Bottom area
    PhysOutputNavigatorDock *pOutputDock = new PhysOutputNavigatorDock(this);
    m_pPhysOutputNavigator = new PhysOutputNavigator(pOutputDock);
    pOutputDock -> setWidget(m_pPhysOutputNavigator);
    addDockWidget(Qt::BottomDockWidgetArea, pOutputDock);

    PhysEquationSolverDock *pEquationDock = new PhysEquationSolverDock(this);
    m_pPhysEqSolver = new PhysEqSolverTable(1, 2, pEquationDock);
    pEquationDock -> setWidget(m_pPhysEqSolver);
    addDockWidget(Qt::BottomDockWidgetArea, pEquationDock);
    m_pPhysEqSolver ->ModType(m_pPhysModNavigator ->ModType());

    /*
    pDock = new PhysDockedWidget(tr("XES - Electrostatic Simulator"), this);
    m_pPhysElectroStaticView = new PhysElectroStaticView(pDock);
    m_pPhysElectroStaticView ->sizeHint();
    pDock -> setWidget(m_pPhysElectroStaticView);
    pDock -> setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, pDock);
    */
}

void CMainWindow::createSignalSlots() {
    QMetaObject::Connection val = connect(m_pGraphWidget, SIGNAL(createObj(QGraphicsItem *)), m_pPhysObjNavigator, SLOT(onCreateObj(QGraphicsItem *)));
    val = connect(m_pGraphWidget, SIGNAL(cartesianGraphCreated(CartesianGraphDataObj *)), m_pPhysEqSolver, SLOT(onCartesianGraphCreated(CartesianGraphDataObj *)));
    val = connect(m_pPhysObjNavigator, SIGNAL(changeObj(QGraphicsItem *, QGraphicsItem *)), m_pPhysObjPropsNavigator, SLOT(onChangeObj(QGraphicsItem *, QGraphicsItem *)));
    val = connect(m_pPhysObjNavigator, SIGNAL(clonePhysObj(QGraphicsItem *)), m_pGraphWidget, SLOT(onClonePhysObj(QGraphicsItem *)));
    val = connect(m_pPhysObjNavigator, SIGNAL(removePhysObj(QGraphicsItem *)), m_pGraphWidget, SLOT(onRemovePhysObj(QGraphicsItem *)));
    val = connect(m_pPhysObjPropsNavigator, SIGNAL(repaint()), m_pGraphWidget, SLOT(onRepaint()));
    val = connect(m_pGraphWidget, SIGNAL(reorderObjNav(QGraphicsItem *)), m_pPhysObjNavigator, SLOT(onReorderObjNav(QGraphicsItem *)));
    val = connect(m_pGraphWidget, SIGNAL(changeItemName(const QString &, const QString &)),
                  m_pPhysObjNavigator, SLOT(onChangeItemName(const QString &, const QString &)));
    val = connect(m_pPhysModNavigator, SIGNAL(setModType(int)), m_pPhysEqSolver, SLOT(onSetModType(int)));
    val = connect(m_pPhysObjPropsNavigator, SIGNAL(updateParticleName(const QString, const QString)),
                  m_pPhysEqSolver, SLOT(onUpdateParticleName(const QString, const QString)));

}

void CMainWindow::createBaseObjects() {
    if (m_pGraphWidget) {
        m_pGraphWidget -> createCartesianGraph();
    }
}


void CMainWindow::newFile() {
    m_infoLabel -> setText(tr("Invoked <b>File|New</b>"));
}

void CMainWindow::open() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Xml"), ".", tr("Xml files (*.xml)"));
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        cerr << "Error: Cannot read file " <<
                qPrintable(filename) << ": " << qPrintable(file.errorString()) << endl;
    }
    QXmlStreamReader XMLReader;
    XMLReader.setDevice(&file);
    ReadXMLFile(XMLReader, file);
    file.close();
    if (XMLReader.hasError())
        cerr << "Error: Failed to parse file " << qPrintable(filename) << ": " << qPrintable(XMLReader.errorString()) << endl;
    else if (file.error() != QFile::NoError)
        cerr << "Error: Cannot read file " << qPrintable(filename) << ": " << qPrintable(file.errorString()) << endl;
    statusBar() -> showMessage(tr("Xml Opened"));
    setWindowTitle(filename);
}

void CMainWindow::ReadXMLFile(QXmlStreamReader &XMLReader, QFile &file) {
    XMLReader.readNext();
    while (!XMLReader.atEnd()) {
        if (!XMLReader.isStartElement())
            XMLReader.readNext();
        else {
            if (XMLReader.name() == "LAMPS") {
                XMLReader.readNext();
            }
            else if (XMLReader.name() == "LIGHT1") {
            }
            else if (XMLReader.name() == "LIGHT2") {
            }
            else if (XMLReader.name() == "LIGHT3") {
            }
            else if (XMLReader.name() == "LIGHT4") {
            }
            else {
                XMLReader.raiseError(QObject::tr("Not a bookindex file"));
            }
        }
    }
}

void CMainWindow::save() {
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Xml"), ".", tr("Xml files (*.xml)"));
    QFile file(filename);
    QXmlStreamWriter xmlWriter;
    file.open(QIODevice::WriteOnly);
    xmlWriter.setDevice(&file);
    WriteXMLFile(xmlWriter, file);
    file.close();
    statusBar() -> showMessage(tr("Xml Saved"));
}

void CMainWindow::WriteXMLFile(QXmlStreamWriter &xmlWriter, QFile &file) {
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
/*
    xmlWriter.writeStartElement("LAMPS");
    xmlWriter.writeStartElement("LIGHT1");
    xmlWriter.writeTextElement("State", ui.pushButton1->isChecked()?"Off":"On" );
    xmlWriter.writeTextElement("Room",ui.comboBox1->currentText());
    xmlWriter.writeTextElement("Potencial",QString::number(ui.spinBox1->value()));
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("LIGHT4");
    xmlWriter.writeTextElement("State", ui.pushButton4->isChecked()?"Off":"On" );
    xmlWriter.writeTextElement("Room",ui.comboBox4->currentText());
    xmlWriter.writeTextElement("Potencial",QString::number(ui.spinBox4->value()));
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
*/
    xmlWriter.writeEndDocument();
}
