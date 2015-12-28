#include <QtWidgets>

#include "physeqsolver.h"
#include "physeqsolverdelegate.h"
#include "physeqsolveritem.h"
#include "physprintview.h"
#include "physeqsolvertable.h"
#include "physdataobj.h"

PhysEqSolver::PhysEqSolver(int rows, int cols, QWidget *pParent) : QTableView(pParent) {
    m_pTable = NULL;
    m_pCalcTimer = new QTimer(this);
    m_CalcInterval = 1000;              // 1000ms = 1 sec -- should be adjustable: PS-36
    m_pFormulaInput = new QLineEdit();
    createTable(rows, cols);
    setupContents();
    setupContextMenu();
    createConnections();
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    m_pCalcTimer ->start(m_CalcInterval);
}

void PhysEqSolver::createConnections() {
    connect(m_pTable, SIGNAL(currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)), this, SLOT(updateLineEdit(QTableWidgetItem *)));
    connect(m_pFormulaInput, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(m_pTable, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(updateLineEdit(QTableWidgetItem *)));
    connect(m_pTable, SIGNAL(addPhysEqSolverRow(QList<PhysParticle *>)), this, SLOT(onAddPhysEqSolverRow(QList<PhysParticle *>)));
    connect(m_pCalcTimer, SIGNAL(timeout()), this, SLOT(Calculate()));
}

void PhysEqSolver::createTable(const int rows, const int cols) {
    m_pTable = new PhysEqSolverTable(rows, cols, this);
}

QTableWidgetItem *PhysEqSolver::createRowItem(PhysVectorDataObj *pObj) {
    QTableWidgetItem *pItem = new QTableWidgetItem(pObj ->Name());
    pItem ->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    PhysEqRowProps *pRowProps = new PhysEqRowProps(pObj);
    PhysEqRow *pRow = new PhysEqRow(pRowProps);
    m_lstRows.push_back(pRow);
    return pItem;
}
QTableWidgetItem *PhysEqSolver::createRowItem(PhysParticleDataObj *pObj) {
    QTableWidgetItem *pItem = new QTableWidgetItem(pObj ->Name());
    pItem ->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

    QVariant var;
    var.setValue(pObj);

    pItem ->setData(Qt::UserRole, var);
    return pItem;
}

void PhysEqSolver::createParticleItems(int i, PhysParticle *pParticle) {
    switch (ModType()) {
    case SINGLEDIM_KINEMATICS:
        create1DKinematicItems(i, pParticle);
        break;
    default:
        qDebug("PhysEqSolver::createParticleItems(): Invalid Module type");
        break;
    }
}

void PhysEqSolver::create1DKinematicItems(int i, PhysParticle *pParticle) {

    // create the Acceleration, Velocity, Gravity, displacement vectors
    // Important parameters are:
    //      - variable name
    //      - equation that defines it
    //      - boolean value that determines if it is to be drawn or not
    //      - Angle at which it should be represented on the CartesianGraph (if any)
    //      - Magnitude, or the value of the vector
    PhysVector *pAccel = new PhysVector(pParticle ->Parent(), pParticle,
                                        QString("a"), QString("diff(dx/dv)"), QString("Acceleration"), false);
    PhysVector *pVelocity = new PhysVector(pParticle ->Parent(), pParticle,
                                           QString("v"), QString("diff(dx/dy)"), QString("Velocity"), false);
    PhysVector *pDisplacement = new PhysVector(pParticle ->Parent(), pParticle,
                                               QString("y"), QString("v*t"), QString("Displacement"), false);
    PhysVector *pGravity = new PhysVector(pParticle ->Parent(), pParticle,
                                          QString("g"), QString("-9.8"), QString("Gravity"), false, -90.0, -9.8);
    m_pTable ->insertRow(i);
    m_pTable ->setItem(i, 0, createRowItem(pAccel ->DataObj()));
    m_pTable ->insertRow(++i);
    m_pTable ->setItem(i, 0, createRowItem(pVelocity ->DataObj()));
    m_pTable ->insertRow(++i);
    m_pTable ->setItem(i, 0, createRowItem(pDisplacement ->DataObj()));
    m_pTable ->insertRow(++i);
    m_pTable ->setItem(i, 0, createRowItem(pGravity ->DataObj()));
}

void PhysEqSolver::onAddPhysEqSolverRow(QList<PhysParticle *> lstParticles) {
    qDebug("PhysEqSolver::onAddPhysEqSolverRow");

    m_pCalcTimer ->stop();

    int i = 0;
    foreach(PhysParticle *pParticle, lstParticles) {
        // Create entry in underlying data structure used for doing the mathematics

        // Insert and populate UI row
        m_pTable ->insertRow(m_pTable ->rowCount());
        m_pTable ->setItem(i++, 0, createRowItem(pParticle ->DataObj()));
        createParticleItems(i, pParticle);
    }
    m_pCalcTimer ->start(m_CalcInterval);
}

void PhysEqSolver::Calculate() {
    qDebug("PhysEqSolver::Calculate()");

    // The first row doesn't count
    if (m_pTable ->rowCount() > 1) {

    }
}

void PhysEqSolver::updateLineEdit(QTableWidgetItem *pItem) {
    if (pItem) {
        if (pItem == m_pTable -> currentItem()) {
            if (pItem)
                m_pFormulaInput -> setText(pItem -> data(Qt::EditRole).toString());
            else
                m_pFormulaInput -> clear();
        }
    }
}

void PhysEqSolver::returnPressed() {
    QString text = m_pFormulaInput -> text();
    int row = m_pTable -> currentRow();
    int col = m_pTable -> currentColumn();
    QTableWidgetItem *pItem = m_pTable -> item(row, col);
    if (!pItem)
        m_pTable -> setItem(row, col, new PhysEqSolverItem(text));
    else
        pItem -> setData(Qt::EditRole, text);
    m_pTable -> viewport() -> update();
}

void PhysEqSolver::setupContextMenu() {
    setContextMenuPolicy(Qt::ActionsContextMenu);
}

void PhysEqSolver::setupContents() {
    QColor titleBackground(Qt::lightGray);
    QFont titleFont = m_pTable -> font();
    titleFont.setBold(true);

    m_pTable -> setItem(0, 0, new PhysEqSolverItem(""));
    m_pTable -> item(0, 0) -> setBackgroundColor(titleBackground);
    m_pTable -> item(0, 0) -> setFont(titleFont);
}

void PhysEqSolver::actionSum() {
    int rowFirst = 0;
    int rowLast = 0;
    int rowCur = 0;
    int colFirst = 0;
    int colLast = 0;
    int colCur = 0;

    QList<QTableWidgetItem*> selected = m_pTable ->selectedItems();

    if (!selected.isEmpty()) {
        QTableWidgetItem *pFirst = selected.first();
        QTableWidgetItem *pLast = selected.last();
        rowFirst = m_pTable -> row(pFirst);
        rowLast = m_pTable -> row(pLast);
        colFirst = m_pTable -> column(pFirst);
        colLast = m_pTable -> column(pLast);
    }

    QTableWidgetItem *pCurrent = m_pTable -> currentItem();
    if (pCurrent) {
        rowCur = m_pTable -> row(pCurrent);
        colCur = m_pTable -> column(pCurrent);
    }

    QString cell1 = encode_pos(rowFirst, colFirst);
    QString cell2 = encode_pos(rowLast, colLast);
    QString out = encode_pos(rowCur, colCur);

        int row;
        int col;
        decode_pos(out, &row, &col);
        m_pTable -> item(row, col) -> setText(tr("sum %1 %2").arg(cell1, cell2));

}

void decode_pos(const QString &pos, int *pRow, int *pCol) {
    if (pos.isEmpty()) {
        *pCol = -1;
        *pRow = -1;
    }
    else {
        *pCol = pos.at(0).toLatin1() - 'A';
        *pRow = pos.right(pos.size() - 1).toInt() - 1;
    }
}

QString encode_pos(int row, int col) {
    return QString(col + 'A') + QString::number(row + 1);
}

