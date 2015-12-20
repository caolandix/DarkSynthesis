#include <QtWidgets>

#include "ui_physselectparticledlg.h"

#include "physeqsolvertable.h"
#include "physeqsolverdelegate.h"
#include "physeqsolvertableheader.h"
#include "physparticledataobj.h"


PhysEqSolverTable::PhysEqSolverTable(const int rows, const int columns, QWidget *pParent) : QTableWidget(rows, columns, pParent) {
    m_pActColor = NULL;
    m_pActFont = NULL;
    m_pActClear = NULL;

    createTableHeader();
    setContextMenuPolicy(Qt::CustomContextMenu);
    setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    setItemPrototype(item(rows - 1, columns - 1));
    setItemDelegate(new PhysEqSolverDelegate());
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));
    connect(m_pHeader, SIGNAL(updateTimeSlices(const int, const int)), this, SLOT(onUpdateTimeSlices(const int, const int)));
}

PhysEqSolverTable::~PhysEqSolverTable() {
}

void PhysEqSolverTable::onCustomContextMenu(const QPoint &pos) {
    QMenu subCtxMenu(tr("Physics Objects..."));
    QMenu subCtxMenuVectors(tr("Vectors..."));
    QMenu subCtxMenuOther(tr("Other..."));
    QMenu ctxMenu;

    // Primary menu actions
    QAction *pFont = new QAction(tr("Font..."), this);
    connect(pFont, SIGNAL(triggered()), this, SLOT(onSelectFont()));
    QAction *pColor = new QAction(QPixmap(16, 16), tr("Background &Color..."), this);
    connect(pColor, SIGNAL(triggered()), this, SLOT(onSelectColor()));
    QAction *pClear = new QAction(tr("Clear"), this);
    connect(pClear, SIGNAL(triggered()), this, SLOT(onClear()));
    ctxMenu.addAction(pFont);
    ctxMenu.addAction(pColor);
    ctxMenu.addAction(pClear);

    // Secondary submenus
    // Vectors
    QAction *pVel = new QAction(tr("Velocity"), this);
    connect(pVel, SIGNAL(triggered()), this, SLOT(onSelectVelVector()));
    QAction *pAccel = new QAction(tr("Acceleration"), this);
    connect(pAccel, SIGNAL(triggered()), this, SLOT(onSelectAccelVector()));
    QAction *pGrav = new QAction(tr("Gravity"), this);
    connect(pGrav, SIGNAL(triggered()), this, SLOT(onSelectGravVector()));
    QAction *pDisplacement = new QAction(tr("Displacement"), this);
    connect(pDisplacement, SIGNAL(triggered()), this, SLOT(onSelectDisplacementVector()));

    // Particles
    QAction *pGenPart = new QAction(tr("Particle"), this);
    connect(pGenPart, SIGNAL(triggered()), this, SLOT(onSelectParticle()));

    // Vectors Submenu
    subCtxMenuVectors.addAction(pVel);
    subCtxMenuVectors.addAction(pAccel);
    subCtxMenuVectors.addAction(pGrav);
    subCtxMenuVectors.addAction(pDisplacement);

    // Particles submenu
    subCtxMenu.addAction(pGenPart);

    // Other submenu

    // Connect up submenu chain
    subCtxMenu.addMenu(&subCtxMenuOther);
    subCtxMenu.addMenu(&subCtxMenuVectors);

    ctxMenu.addMenu(&subCtxMenu);

    // Execute the menu
    ctxMenu.exec(mapToGlobal(pos));
}

void PhysEqSolverTable::onSelectVelVector() {
    qDebug("PhysEqSolverTable::onSelectVelVector()");
}

void PhysEqSolverTable::onSelectAccelVector() {
    qDebug("PhysEqSolverTable::onSelectAccelVector()");
}

void PhysEqSolverTable::onSelectGravVector() {
    qDebug("PhysEqSolverTable::onSelectGravVector()");
}


void PhysEqSolverTable::onSelectDisplacementVector() {
    qDebug("PhysEqSolverTable::onSelectDisplacementVector()");
}

void PhysEqSolverTable::onSelectParticle() {
    qDebug("PhysEqSolverTable::onSelectParticle()");

    QDialog *pDlg = new QDialog(0,0);
    Ui_PhysSelectParticleDlg dlg;
    dlg.setupUi(pDlg);

    foreach (PhysParticle *pObj, m_pDataObj ->Particles()) {
        if (pObj)
            dlg.m_lstParticles->addItem(new QListWidgetItem(pObj ->Name()));
    }
    pDlg ->show();
    if (pDlg ->result() == QDialog::Accepted) {
        foreach(QListWidgetItem *pItem, dlg.m_lstParticles ->selectedItems()) {
            if (pItem)
                emit addPhysEqSolverRow(pItem -> text());
        }
    }
}

void PhysEqSolverTable::onUpdateTimeSlices(const int logicalIndex, const int timeVal) {
    m_TimeSliceValues = m_pHeader ->timeSliceList();
    rebuildColumnHeaders();
}

void PhysEqSolverTable::createTableHeader() {
    m_TimeSliceValues.push_back(1.0);
    setHorizontalHeader(m_pHeader = new PhysEqSolverTableHeader(m_TimeSliceValues, this));
    setHorizontalHeaderLabels(QStringList() << "" << "t0");
    verticalHeader() ->setVisible(false);
    rebuildColumnHeaders();
}

void PhysEqSolverTable::insertColumn() {

    // When inserting a new column with the default value, it should be added to the previous column
    int idx = m_TimeSliceValues.count() - 1;
    int newValue = m_TimeSliceValues.at(idx) + 1.0;
    m_TimeSliceValues.push_back(newValue);
    m_pHeader ->timeSliceList(m_TimeSliceValues);
    model() ->insertColumn(model() ->columnCount());
    rebuildColumnHeaders();
}

void PhysEqSolverTable::removeColumn(const int idx) {
    if (model() ->columnCount() > 2) {
        model() ->removeColumn(idx);
        m_TimeSliceValues.removeAt(idx);
        m_pHeader ->timeSliceList(m_TimeSliceValues);
        rebuildColumnHeaders();
    }
}

QSize PhysEqSolverTable::minimumSizeHint() const {
    QSize size(QTableWidget::sizeHint());
    int width = 0;
    for (int a = 0; a < columnCount(); ++a)
        width += columnWidth(a);
    size.setWidth(width + (columnCount() * 1));
    int height = horizontalHeader()->height();
    for (int a = 0; a < rowCount(); ++a)
        height += rowHeight(a);
    size.setHeight(height + (rowCount() * 1));
    return size;
}
QSize PhysEqSolverTable::sizeHint() const {
    return minimumSizeHint();
}

void PhysEqSolverTable::rebuildColumnHeaders() {
    QStringList headers;
    QList<int> lst = m_pHeader ->timeSliceList();

    // rebuild column headers
    headers.push_back(QString(""));
    for (int i = 1; i < model() ->columnCount(); i++) {
        QString hdrString = QString("t%1 = %2s").arg(i - 1).arg(lst.at(i - 1));
        headers.push_back(hdrString);
    }
    setHorizontalHeaderLabels(headers);
}

void PhysEqSolverTable::onSelectColor() {
    QTableWidgetItem *pItem = currentItem();
    QColor col = pItem ? pItem -> backgroundColor() : palette().base().color();
    col = QColorDialog::getColor(col, this);
    if (!col.isValid())
        return;

    QList<QTableWidgetItem *> items = selectedItems();
    if (items.count() == 0)
        return;

    foreach (QTableWidgetItem *pItem, items) {
        if (pItem)
            pItem -> setBackgroundColor(col);
    }
    updateColor(currentItem());
}

void PhysEqSolverTable::onSelectFont() {
    QList<QTableWidgetItem*> items = selectedItems();
    if (items.count() == 0)
        return;

    bool ok = false;
    QFont fnt = QFontDialog::getFont(&ok, font(), this);

    if (!ok)
        return;
    foreach (QTableWidgetItem *pItem, items) {
        if (pItem)
            pItem -> setFont(fnt);
    }
}

void PhysEqSolverTable::onClear() {
    foreach (QTableWidgetItem *pItem, selectedItems())
        pItem -> setText("");
}

void PhysEqSolverTable::updateColor(QTableWidgetItem *pItem) {
    QPixmap pix(16, 16);
    QColor colour;
    if (pItem)
        colour = pItem -> backgroundColor();
    if (!colour.isValid())
        colour = palette().base().color();

    QPainter pt(&pix);
    pt.fillRect(0, 0, 16, 16, colour);

    QColor lighter = colour.light();
    pt.setPen(lighter);
    QPoint lightFrame[] = { QPoint(0, 15), QPoint(0, 0), QPoint(15, 0) };
    pt.drawPolyline(lightFrame, 3);

    pt.setPen(colour.dark());
    QPoint darkFrame[] = { QPoint(1, 15), QPoint(15, 15), QPoint(15, 1) };
    pt.drawPolyline(darkFrame, 3);
    pt.end();
    m_pActColor -> setIcon(pix);
}

