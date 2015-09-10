#include <QContextMenuEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QXmlStreamReader>

#include <iostream>

#include "cmainwindow.h"
#include "ui_cmainwindow.h"
#include "cartesiangraphsettingsdlg.h"
#include "cartesiangraphdataobj.h"

using namespace std;

CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::CMainWindow) {
    ui -> setupUi(this);

    infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to invoke a context menu</i>"));
    infoLabel -> setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel -> setAlignment(Qt::AlignCenter);
    createActions();
    createMenus();
}

CMainWindow::~CMainWindow() {
    delete ui;
}


void CMainWindow::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
    menu.exec(event -> globalPos());
}

void CMainWindow::newFile() {
    infoLabel -> setText(tr("Invoked <b>File|New</b>"));
}

void CMainWindow::open() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Xml"), ".", tr("Xml files (*.xml)"));
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        std::cerr << "Error: Cannot read file " <<
            qPrintable(filename) <<
            ": " <<
            qPrintable(file.errorString()) <<
            std::endl;
    }
    QXmlStreamReader XMLReader;
    XMLReader.setDevice(&file);
    ReadXMLFile(XMLReader, file);
    file.close();
    if (XMLReader.hasError()) {
        std::cerr <<
            "Error: Failed to parse file " <<
            qPrintable(filename) <<
            ": " <<
            qPrintable(XMLReader.errorString()) <<
            std::endl;
    }
    else if (file.error() != QFile::NoError) {
        std::cerr <<
            "Error: Cannot read file " <<
            qPrintable(filename) <<
            ": " <<
            qPrintable(file.errorString()) <<
            std::endl;
    }
    statusBar() -> showMessage(tr("Xml Opened"));
    setWindowTitle(filename);
}

void CMainWindow::ReadXMLFile(QXmlStreamReader &XMLReader, QFile &file) {
    XMLReader.readNext();
    while (!XMLReader.atEnd()) {
        if (XMLReader.isStartElement()) {
            if (XMLReader.name() == "LAMPS") {
                XMLReader.readNext();
            }
            else if(XMLReader.name() == "LIGHT1") {
            }
            else if(XMLReader.name() == "LIGHT2") {
            }
            else if(XMLReader.name() == "LIGHT3") {
            }
            else if(XMLReader.name() == "LIGHT4") {
            }
            else {
                XMLReader.raiseError(QObject::tr("Not a bookindex file"));
            }
        }
        else {
            XMLReader.readNext();
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


void CMainWindow::print() {
    infoLabel->setText(tr("Invoked <b>File|Print</b>"));
}

void CMainWindow::undo() {
    infoLabel->setText(tr("Invoked <b>Edit|Undo</b>"));
}

void CMainWindow::redo() {
    infoLabel->setText(tr("Invoked <b>Edit|Redo</b>"));
}

void CMainWindow::cut() {
    infoLabel->setText(tr("Invoked <b>Edit|Cut</b>"));
}

void CMainWindow::copy() {
    infoLabel->setText(tr("Invoked <b>Edit|Copy</b>"));
}

void CMainWindow::paste() {
    infoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
}

void CMainWindow::bold() {
    infoLabel->setText(tr("Invoked <b>Edit|Format|Bold</b>"));
}

void CMainWindow::italic() {
    infoLabel->setText(tr("Invoked <b>Edit|Format|Italic</b>"));
}

void CMainWindow::setLineSpacing() {
    infoLabel -> setText(tr("Invoked <b>Edit|Format|Set Line Spacing</b>"));
}

void CMainWindow::setParagraphSpacing() {
    infoLabel -> setText(tr("Invoked <b>Edit|Format|Set Paragraph Spacing</b>"));
}

void CMainWindow::about() {
    infoLabel -> setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About Menu"), tr("The <b>Menu</b> example shows how to create menu-bar menus and context menus."));
}

void CMainWindow::aboutQt() {
    infoLabel -> setText(tr("Invoked <b>Help|About Qt</b>"));
}

void CMainWindow::cartesianGraphOptions() {
    CartesianGraphSettingsDlg dlg(graph_widget -> cartesianGraph() -> DataObj());
    if (dlg.exec() == QDialog::Accepted) {

        // get values stored
        bool bVal = false;
    }
}

void CMainWindow::createActions() {
    newAct = new QAction(tr("&New"), this);
    newAct -> setShortcuts(QKeySequence::New);
    newAct -> setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(tr("&Open..."), this);
    openAct -> setShortcuts(QKeySequence::Open);
    openAct -> setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(tr("&Save"), this);
    saveAct -> setShortcuts(QKeySequence::Save);
    saveAct -> setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    printAct = new QAction(tr("&Print..."), this);
    printAct -> setShortcuts(QKeySequence::Print);
    printAct -> setStatusTip(tr("Print the document"));
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct -> setShortcuts(QKeySequence::Quit);
    exitAct -> setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    undoAct = new QAction(tr("&Undo"), this);
    undoAct -> setShortcuts(QKeySequence::Undo);
    undoAct -> setStatusTip(tr("Undo the last operation"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    redoAct = new QAction(tr("&Redo"), this);
    redoAct -> setShortcuts(QKeySequence::Redo);
    redoAct -> setStatusTip(tr("Redo the last operation"));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    cutAct = new QAction(tr("Cu&t"), this);
    cutAct -> setShortcuts(QKeySequence::Cut);
    cutAct -> setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(tr("&Copy"), this);
    copyAct -> setShortcuts(QKeySequence::Copy);
    copyAct -> setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct -> setShortcuts(QKeySequence::Paste);
    pasteAct -> setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

    boldAct = new QAction(tr("&Bold"), this);
    boldAct -> setCheckable(true);
    boldAct -> setShortcut(QKeySequence::Bold);
    boldAct -> setStatusTip(tr("Make the text bold"));
    connect(boldAct, SIGNAL(triggered()), this, SLOT(bold()));

    QFont boldFont = boldAct->font();
    boldFont.setBold(true);
    boldAct->setFont(boldFont);

    italicAct = new QAction(tr("&Italic"), this);
    italicAct -> setCheckable(true);
    italicAct -> setShortcut(QKeySequence::Italic);
    italicAct -> setStatusTip(tr("Make the text italic"));
    connect(italicAct, SIGNAL(triggered()), this, SLOT(italic()));


    QFont italicFont = italicAct -> font();
    italicFont.setItalic(true);
    italicAct -> setFont(italicFont);

    setLineSpacingAct = new QAction(tr("Set &Line Spacing..."), this);
    setLineSpacingAct -> setStatusTip(tr("Change the gap between the lines of a paragraph"));
    connect(setLineSpacingAct, SIGNAL(triggered()), this, SLOT(setLineSpacing()));

    setParagraphSpacingAct = new QAction(tr("Set &Paragraph Spacing..."), this);
    setParagraphSpacingAct -> setStatusTip(tr("Change the gap between paragraphs"));
    connect(setParagraphSpacingAct, SIGNAL(triggered()), this, SLOT(setParagraphSpacing()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct -> setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct -> setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

    m_pcartGraphSettings = new QAction(tr("C&artesian Graph Settings..."), this);
    m_pcartGraphSettings -> setShortcut(tr("Ctrl+A"));
    m_pcartGraphSettings -> setStatusTip(tr("Allows adjustment of the Cartesian Graph"));
    connect(m_pcartGraphSettings, SIGNAL(triggered()), this, SLOT(cartesianGraphOptions()));
}

void CMainWindow::createMenus() {
    fileMenu = menuBar() -> addMenu(tr("&File"));
    fileMenu -> addAction(newAct);
    fileMenu -> addAction(openAct);
    fileMenu -> addAction(saveAct);
    fileMenu -> addAction(printAct);
    fileMenu -> addSeparator();
    fileMenu -> addAction(exitAct);

    editMenu = menuBar() -> addMenu(tr("&Edit"));
    editMenu -> addAction(redoAct);
    editMenu -> addSeparator();
    editMenu -> addAction(cutAct);
    editMenu -> addAction(copyAct);
    editMenu -> addAction(pasteAct);
    editMenu -> addSeparator();

    helpMenu = menuBar() -> addMenu(tr("&Help"));
    helpMenu -> addAction(aboutAct);
    helpMenu -> addAction(aboutQtAct);

    formatMenu = editMenu -> addMenu(tr("&Format"));
    formatMenu -> addAction(boldAct);
    formatMenu -> addAction(italicAct);
    formatMenu -> addSeparator();
    formatMenu -> addAction(setLineSpacingAct);
    formatMenu -> addAction(setParagraphSpacingAct);

    m_pSettingsMenu = menuBar() -> addMenu(tr("&Settings"));
    m_pSettingsMenu -> addAction(m_pcartGraphSettings);
    m_pSettingsMenu -> addSeparator();
}
