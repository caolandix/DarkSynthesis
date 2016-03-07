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
#include "physeqsolver.h"
#include "physdockedwidget.h"
#include "phystablemodel.h"
#include "xes1/physelectrostaticview.h"
#include "physcommon.h"

using namespace std;

CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent), m_pUI(new Ui::CMainWindow) , PhysCommon() {
    init();
    m_pUI -> setupUi(this);
    //m_infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to invoke a context menu</i>"));
    //m_infoLabel -> setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    //m_infoLabel -> setAlignment(Qt::AlignCenter);
    //createActions();
    //createMenus();
    //createToolBars();
    //createStatusBar();
    createDockWindows();

    //GraphWidget *pGraph = new GraphWidget();

    //setGraphWidget(pGraph);
    //setCentralWidget(pGraph);
    //createSignalSlots();
    //createBaseObjects();
    setWindowTitle(tr("The Physicist's Workbench"));
}

CMainWindow::~CMainWindow() {
    delete m_pUI;
}

void CMainWindow::init() {
    //m_pUI = new Ui::CMainWindow();
    m_pFileMenu = NULL;
    m_pEditMenu = NULL;
    m_pHelpMenu = NULL;
    m_pSettingsMenu = NULL;
    m_pcartGraphSettings = NULL;
    m_pactNew = NULL;
    m_pactOpen = NULL;
    m_pactSave = NULL;
    m_pactPrint = NULL;
    m_pactExit = NULL;
    m_pactAbout = NULL;
    m_pactAboutQt = NULL;
    m_infoLabel = NULL;
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

void CMainWindow::createActions() {
    m_pactNew = new QAction(tr("&New"), this);
    m_pactNew -> setShortcuts(QKeySequence::New);
    m_pactNew -> setStatusTip(tr("Create a new file"));
    connect(m_pactNew, SIGNAL(triggered()), this, SLOT(newFile()));

    m_pactOpen = new QAction(tr("&Open..."), this);
    m_pactOpen -> setShortcuts(QKeySequence::Open);
    m_pactOpen -> setStatusTip(tr("Open an existing file"));
    connect(m_pactOpen, SIGNAL(triggered()), this, SLOT(open()));

    m_pactSave = new QAction(tr("&Save"), this);
    m_pactSave -> setShortcuts(QKeySequence::Save);
    m_pactSave -> setStatusTip(tr("Save the document to disk"));
    connect(m_pactSave, SIGNAL(triggered()), this, SLOT(save()));

    m_pactPrint = new QAction(tr("&Print..."), this);
    m_pactPrint -> setShortcuts(QKeySequence::Print);
    m_pactPrint -> setStatusTip(tr("Print the document"));
    connect(m_pactPrint, SIGNAL(triggered()), this, SLOT(print()));

    m_pactExit = new QAction(tr("E&xit"), this);
    m_pactExit -> setShortcuts(QKeySequence::Quit);
    m_pactExit -> setStatusTip(tr("Exit the application"));
    connect(m_pactExit, SIGNAL(triggered()), this, SLOT(close()));

    m_pactAbout = new QAction(tr("&About"), this);
    m_pactAbout -> setStatusTip(tr("Show the application's About box"));
    connect(m_pactAbout, SIGNAL(triggered()), this, SLOT(about()));

    m_pactAboutQt = new QAction(tr("About &Qt"), this);
    m_pactAboutQt -> setStatusTip(tr("Show the Qt library's About box"));
    connect(m_pactAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(m_pactAboutQt, SIGNAL(triggered()), this, SLOT(aboutQt()));

    m_pcartGraphSettings = new QAction(tr("C&artesian Graph Settings..."), this);
    m_pcartGraphSettings -> setShortcut(tr("Ctrl+A"));
    m_pcartGraphSettings -> setStatusTip(tr("Allows adjustment of the Cartesian Graph"));
    connect(m_pcartGraphSettings, SIGNAL(triggered()), this, SLOT(cartesianGraphOptions()));
}

void CMainWindow::createMenus() {

    // The file menu
    m_pFileMenu = menuBar() -> addMenu(tr("&File"));
    m_pFileMenu -> addAction(m_pactNew);
    m_pFileMenu -> addAction(m_pactOpen);
    m_pFileMenu -> addAction(m_pactSave);
    m_pFileMenu -> addAction(m_pactPrint);
    m_pFileMenu -> addSeparator();
    m_pFileMenu -> addAction(m_pactExit);

    // The Edit menu
    m_pEditMenu = menuBar() -> addMenu(tr("&Edit"));

    // The Settings menu
    m_pSettingsMenu = menuBar() -> addMenu(tr("&Settings"));
    m_pSettingsMenu -> addAction(m_pcartGraphSettings);
    m_pSettingsMenu -> addSeparator();

    // The Help Menu
    m_pHelpMenu = menuBar() -> addMenu(tr("&Help"));
    m_pHelpMenu -> addAction(m_pactAbout);
    m_pHelpMenu -> addAction(m_pactAboutQt);
}

void CMainWindow::createToolBars() {
    //QToolBar *pToolBar = new QToolBar(tr("Main"), this);
    //pToolBar -> addSeparator();
}

void CMainWindow::createStatusBar() {
}

#include "modulenavigator.h"
#include "physmodulenavigatormodel.h"

void CMainWindow::createDockWindows() {

    // Create the left side
    ModuleNavigator *pDock = new ModuleNavigator(this);
    m_pPhysModNavigator = new PhysModuleNavigator(pDock);
    m_pPhysModNavigator ->setModel(new PhysModuleNavigatorModel());
    pDock -> setWidget(m_pPhysModNavigator);
    pDock -> setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, pDock);

    // Create the right side
    /*
    QDockWidget *pDock = new QDockWidget(tr("Physics Objects"), this);
    m_pPhysObjNavigator = new PhysObjectNavigator(pDock);
    pDock -> setWidget(m_pPhysObjNavigator);
    pDock -> setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, pDock);

    pDock = new QDockWidget(tr("Physics Properties"), this);
    m_pPhysObjPropsNavigator = new PhysObjectPropsNavigator(pDock);
    pDock -> setWidget(m_pPhysObjPropsNavigator);
    pDock -> setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, pDock);

    // Create the Bottom area
    pDock = new QDockWidget(tr("Output"), this);
    m_pPhysOutputNavigator = new PhysOutputNavigator(pDock);
    pDock -> setWidget(m_pPhysOutputNavigator);
    pDock -> setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, pDock);

    PhysDockedWidget *pPhysDock = new PhysDockedWidget(tr("Equation Solver"), this);
    m_pPhysEqSolver = new PhysEqSolver(1, 2, pPhysDock);
    m_pPhysEqSolver ->setModel(new PhysTableModel(this));
    pPhysDock -> setWidget(m_pPhysEqSolver);
    pPhysDock -> setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, pPhysDock);
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
