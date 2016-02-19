#include <QtWidgets>

#include "physeqsolvertable.h"
#include "physeqsolverdelegate.h"
#include "physeqsolvertableheader.h"
#include "physeqsolveritem.h"
#include "physeqsolver.h"
#include "physparticledataobj.h"
#include "ui_physselectparticledlg.h"
#include "ui_physeqrowdlg.h"

PhysEqSolverTable::PhysEqSolverTable(const int rows, const int columns, QWidget *pParent) : QTableWidget(rows, columns, pParent) {
    m_pActColor = NULL;
    m_pActFont = NULL;
    m_pActClear = NULL;
    m_pRowProperties = NULL;
    m_pParent = pParent;

    createTableHeader();
    setContextMenuPolicy(Qt::CustomContextMenu);
    setItemPrototype(item(rows - 1, columns - 1));
    setItemDelegate(new PhysEqSolverDelegate());
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    createConnections();
}

PhysEqSolverTable::~PhysEqSolverTable() {
}

void PhysEqSolverTable::createConnections() {
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));
    connect(m_pHeader, SIGNAL(updateTimeSlices(const int, const double)), this, SLOT(onUpdateTimeSlices(const int, const double)));
}

void PhysEqSolverTable::onCustomContextMenu(const QPoint &pos) {

    // Check to see if the pos is inside of the first column, as that needs a different context menu
    QModelIndex index = indexAt(pos);
    if (index.isValid()) {
        m_currItem.row = index.row();
        m_currItem.column = index.column();

        QMenu ctxMenu;
        QMenu subCtxMenu(tr("Physics Objects..."));
        QMenu subCtxMenuVectors(tr("Vectors..."));
        QMenu subCtxMenuOther(tr("Other..."));

        // If in first column then we need to check and see what row it is. get that information to populate the
        // dialog box.
        if (m_currItem.column == 0) {
            QAction *m_pRowProperties = new QAction(tr("Properties..."), this);
            connect(m_pRowProperties, SIGNAL(triggered()), this, SLOT(onRowProperties()));
            ctxMenu.addAction(m_pRowProperties);
        }
        else {
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
        }
        ctxMenu.exec(mapToGlobal(pos));
    }
}

void PhysEqSolverTable::onRowProperties() {
    QDialog *pDlg = new QDialog(0,0);
    Ui_PhysEqRowDlg dlg;
    dlg.setupUi(pDlg);
    PhysEqRow *pCurrRow = NULL;
    PhysEqSolver *pParent = static_cast<PhysEqSolver *>(m_pParent);
    QList<PhysEqRow *> lstRows = pParent ->Rows();
    int i = 0;
    foreach (PhysEqRow *pRow, lstRows) {
        if (i == m_currItem.row) {
            pCurrRow = pRow;
            break;
        }
        i++;
    }
    if (pCurrRow) {
        dlg.edtRowEq->setText(pCurrRow ->Equation());
        dlg.edtRowVariable ->setText(pCurrRow ->Variable());
        //dlg.edtRowLabel ->setText(pCurrRow ->Label());
        if (pDlg ->exec() == QDialog::Accepted) {
            QString eq = dlg.edtRowEq ->text();
            QString label = dlg.edtRowLabel ->text();
            QString variable = dlg.edtRowVariable ->text();
            pCurrRow ->Variable(variable);
            pCurrRow ->Equation(eq);
            //pCurrRow ->Label(label);
        }
    }
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
            dlg.m_lstParticles  ->addItem(new QListWidgetItem(pObj ->Name()));
    }
    pDlg ->exec();
    if (pDlg ->result() == QDialog::Accepted) {
        QList<PhysParticle *> lst;
        foreach(QListWidgetItem *pItem, dlg.m_lstParticles ->selectedItems()) {
            if (pItem) {
                foreach(PhysParticle *pPart, m_pDataObj ->Particles()) {
                    if (pPart ->Name().compare(pItem ->text()) == 0)
                        lst.push_back(pPart);
                }
            }
        }
        emit addPhysEqSolverRow(lst);
    }
}

void PhysEqSolverTable::onUpdateTimeSlices(const int logicalIndex, const double timeVal) {
    m_TimeSliceValues = m_pHeader ->timeSliceList();
    rebuildColumnHeaders();
}

void PhysEqSolverTable::createTableHeader() {
    m_TimeSliceValues.push_back(0.0);
    setHorizontalHeader(m_pHeader = new PhysEqSolverTableHeader(m_TimeSliceValues, this));
    setHorizontalHeaderLabels(QStringList() << "" << "t0");
    horizontalHeader() ->setVisible(true);
    rebuildColumnHeaders();
}

void PhysEqSolverTable::insertColumn() {

    // When inserting a new column with the default value, it should be added to the previous column
    double newValue = m_TimeSliceValues.at(m_TimeSliceValues.count() - 1) + 1.0;
    m_TimeSliceValues.push_back(newValue);
    m_pHeader ->timeSliceList(m_TimeSliceValues);
    model() ->insertColumn(model() ->columnCount());
    rebuildColumnHeaders();

    emit addTimeSliceCell(m_TimeSliceValues.count() - 1, newValue);
}

void PhysEqSolverTable::removeColumn(const int idx) {
    if (model() ->columnCount() > 2) {
        model() ->removeColumn(idx);
        m_TimeSliceValues.removeAt(idx);
        m_pHeader ->timeSliceList(m_TimeSliceValues);
        rebuildColumnHeaders();
        emit removeTimeSliceCell(idx);
    }
}

QSize PhysEqSolverTable::minimumSizeHint() const {
    QSize size(QTableWidget::sizeHint());
    int width = 0;
    int height = horizontalHeader()->height();

    for (int i = 0; i < columnCount(); ++i)
        width += columnWidth(i);
    size.setWidth(width + (columnCount() * 1));

    for (int i = 0; i < rowCount(); ++i)
        height += rowHeight(i);
    size.setHeight(height + (rowCount() * 1));

    return size;
}

QSize PhysEqSolverTable::sizeHint() const {
    return QTableWidget::sizeHint();//minimumSizeHint();
}

void PhysEqSolverTable::rebuildColumnHeaders() {
    QStringList headers;
    QList<double> lst = m_pHeader ->timeSliceList();
    int precision = 4;

    // rebuild column headers
    headers.push_back(QString(""));
    for (int i = 1; i < model() ->columnCount(); i++) {
        char str[25];
        sprintf(str, "t%d = %.*f", i - 1, precision, lst.at(i - 1));
        headers.push_back(QString(str));
    }
    setHorizontalHeaderLabels(headers);
}

void PhysEqSolverTable::onSelectColor() {
    QTableWidgetItem *pItem = currentItem();
    QColor col = pItem ? pItem ->backgroundColor() : palette().base().color();
    col = QColorDialog::getColor(col, this);
    if (!col.isValid())
        return;

    QList<QTableWidgetItem *> items = selectedItems();
    if (items.count() == 0)
        return;

    foreach (QTableWidgetItem *pItem, items) {
        if (pItem)
            pItem ->setBackgroundColor(col);
    }
    updateColor(currentItem());
}

void PhysEqSolverTable::onSelectFont() {
    QList<QTableWidgetItem*> items = selectedItems();
    if (items.count() == 0)
        return;

    bool bOK = false;
    QFont fnt = QFontDialog::getFont(&bOK, font(), this);
    if (!bOK)
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
    QPainter pt(&pix);
    QColor colour;
    QColor lighter = colour.light();
    QPoint lightFrame[] = { QPoint(0, 15), QPoint(0, 0), QPoint(15, 0) };
    QPoint darkFrame[] = { QPoint(1, 15), QPoint(15, 15), QPoint(15, 1) };

    if (pItem)
        colour = pItem -> backgroundColor();

    if (!colour.isValid())
        colour = palette().base().color();

    pt.fillRect(0, 0, 16, 16, colour);
    pt.setPen(lighter);
    pt.drawPolyline(lightFrame, 3);
    pt.setPen(colour.dark());
    pt.drawPolyline(darkFrame, 3);
    pt.end();
    m_pActColor -> setIcon(pix);
}
