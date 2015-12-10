#include <QtWidgets>
#include "physeqsolvertable.h"
#include "physeqsolverdelegate.h"
#include "physeqsolvertableheader.h"


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
}

PhysEqSolverTable::~PhysEqSolverTable() {
}

void PhysEqSolverTable::onCustomContextMenu(const QPoint &pos) {
    QMenu subCtxMenu(tr("Physics Objects..."));
    QMenu subCtxMenuParticles(tr("Particles..."));
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
    QAction *pGenPart = new QAction(tr("Free-form"), this);
    connect(pGenPart, SIGNAL(triggered()), this, SLOT(onSelectFreeParticle()));
    QAction *pXPart = new QAction(tr("Horizontal Only"), this);
    connect(pXPart, SIGNAL(triggered()), this, SLOT(onSelectXLockedParticle()));
    QAction *pYPart = new QAction(tr("Vertical Only"), this);
    connect(pYPart, SIGNAL(triggered()), this, SLOT(onSelectYLockedParticle()));

    // Vectors Submenu
    subCtxMenuVectors.addAction(pVel);
    subCtxMenuVectors.addAction(pAccel);
    subCtxMenuVectors.addAction(pGrav);
    subCtxMenuVectors.addAction(pDisplacement);

    // Particles submenu
    subCtxMenuParticles.addAction(pGenPart);
    subCtxMenuParticles.addAction(pXPart);
    subCtxMenuParticles.addAction(pYPart);

    // Other submenu

    // Connect up submenu chain
    subCtxMenu.addMenu(&subCtxMenuOther);
    subCtxMenu.addMenu(&subCtxMenuParticles);
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

void PhysEqSolverTable::onSelectFreeParticle() {
    qDebug("PhysEqSolverTable::onSelectFreeParticle()");
}

void PhysEqSolverTable::onSelectXLockedParticle() {
    qDebug("PhysEqSolverTable::onSelectXLockedParticle()");
}

void PhysEqSolverTable::onSelectYLockedParticle() {
    qDebug("PhysEqSolverTable::onSelectYLockedParticle()");
}

void PhysEqSolverTable::onSelectDisplacementVector() {
    qDebug("PhysEqSolverTable::onSelectDisplacementVector()");
}

void PhysEqSolverTable::createTableHeader() {
    setHorizontalHeader(m_pHeader = new PhysEqSolverTableHeader(this));
    setHorizontalHeaderLabels(QStringList() << "" << "t0");
    verticalHeader() ->setVisible(false);
}

void PhysEqSolverTable::insertColumn() {
    model() ->insertColumn(model() ->columnCount());
    rebuildColumnHeaders();
    resizeColumnsToContents();
}

void PhysEqSolverTable::removeColumn(const int idx) {
    if (model() ->columnCount() > 2) {
        model() ->removeColumn(idx);
        rebuildColumnHeaders();
    }
}

void PhysEqSolverTable::rebuildColumnHeaders() {
    QStringList headers;

    // rebuild column headers
    headers.push_back(QString(""));
    for (int i = 1; i < model() ->columnCount(); i++)
        headers.push_back(QString("t") + QString::number(i - 1));
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

