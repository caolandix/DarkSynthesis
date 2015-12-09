#include <QtWidgets>
#include "physeqsolvertable.h"
#include "physeqsolverdelegate.h"
#include "physeqsolvertableheader.h"


PhysEqSolverTable::PhysEqSolverTable(const int rows, const int columns, QWidget *pParent) : QTableWidget(rows, columns, pParent) {
    m_pActColor = NULL;
    m_pActFont = NULL;
    m_pActClear = NULL;
    setHorizontalHeader(m_pHeader = new PhysEqSolverTableHeader(this));
    setHorizontalHeaderLabels(QStringList() << "" << "t0");
    verticalHeader() ->setVisible(false);

    setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    setItemPrototype(item(rows - 1, columns - 1));
    setItemDelegate(new PhysEqSolverDelegate());
    createActions();
    setupContextMenu();
}

PhysEqSolverTable::~PhysEqSolverTable() {
}

void PhysEqSolverTable::insertColumn() {
    model() ->insertColumn(model() ->columnCount());
    rebuildColumnHeaders();
    resizeColumnsToContents();
}

void PhysEqSolverTable::removeColumn(const int idx) {
    model() ->removeColumn(idx);
    rebuildColumnHeaders();
}

void PhysEqSolverTable::rebuildColumnHeaders() {
    QStringList headers;

    // rebuild column headers
    headers.push_back(QString(""));
    for (int i = 1; i < model() ->columnCount(); i++)
        headers.push_back(QString("t") + QString::number(i - 1));
    setHorizontalHeaderLabels(headers);
}

void PhysEqSolverTable::createActions() {
    m_pActFont = new QAction(tr("Font..."), this);
    m_pActFont->setShortcut(Qt::CTRL | Qt::Key_F);
    connect(m_pActFont, SIGNAL(triggered()), this, SLOT(selectFont()));

    m_pActColor = new QAction(QPixmap(16, 16), tr("Background &Color..."), this);
    connect(m_pActColor, SIGNAL(triggered()), this, SLOT(selectColor()));

    m_pActClear = new QAction(tr("Clear"), this);
    m_pActClear->setShortcut(Qt::Key_Delete);
    connect(m_pActClear, SIGNAL(triggered()), this, SLOT(clear()));
}

void PhysEqSolverTable::setupContextMenu() {
    addAction(m_pActColor);
    addAction(m_pActFont);
    addAction(m_pActClear);
    setContextMenuPolicy(Qt::ActionsContextMenu);
}

void PhysEqSolverTable::selectColor() {
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

void PhysEqSolverTable::selectFont() {
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

void PhysEqSolverTable::clear() {
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

