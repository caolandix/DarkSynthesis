#include <QtWidgets>

#include "physeqsolvertable.h"
#include "physeqsolverdelegate.h"
#include "physeqsolvertableheader.h"
#include "physeqsolveritem.h"
#include "physparticledataobj.h"
#include "ui_physselectparticledlg.h"
#include "ui_physeqrowdlg.h"
#include "phystimeslicedataobj.h"
#include "physcelldataobj.h"
#include "stargate7.h"
#include "jumpdrive/ExpressionBuilder.h"

PhysEqSolverTable::PhysEqSolverTable(const int rows, const int columns, QWidget *pParent) : QTableWidget(rows, columns, pParent) {
    m_pActColor = NULL;
    m_pActFont = NULL;
    m_pActClear = NULL;
    m_pRowProperties = NULL;
    m_pParent = pParent;

    m_pFormulaInput = new QLineEdit();
    m_pCalcTimer = new PhysCalculateTimer(this, 1000);
    //m_pCalcTimer ->start();

    setupTableLookAndFeel();

    createTableHeader();
    setContextMenuPolicy(Qt::CustomContextMenu);
    setItemPrototype(item(rows - 1, columns - 1));
    setItemDelegate(new PhysEqSolverDelegate());
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    createConnections();
    createTimeSliceRow(TimeSliceValues());
}

PhysEqSolverTable::~PhysEqSolverTable() {
}

void PhysEqSolverTable::createConnections() {
    qDebug("PhysEqSolverTable::createConnections()");
    connect(this, &PhysEqSolverTable::customContextMenuRequested, this, &PhysEqSolverTable::onCustomContextMenu);
    connect(m_pHeader, &PhysEqSolverTableHeader::updateTimeSlices, this, &PhysEqSolverTable::onUpdateTimeSlices);
    connect(this, &PhysEqSolverTable::currentItemChanged, this, &PhysEqSolverTable::updateLineEdit);
    connect(m_pFormulaInput, &QLineEdit::returnPressed, this,  &PhysEqSolverTable::returnPressed);
    connect(this, &PhysEqSolverTable::itemChanged, this, &PhysEqSolverTable::updateLineEdit);
    connect(this, &PhysEqSolverTable::addPhysEqSolverRow, this, &PhysEqSolverTable::onAddPhysEqSolverRow);
    connect(m_pCalcTimer ->Timer(), &QTimer::timeout, this, &PhysEqSolverTable::onCalculate);
    connect(this, &PhysEqSolverTable::addTimeSliceCell, this, &PhysEqSolverTable::onAddTimeSliceCell);
    connect(this, &PhysEqSolverTable::removeTimeSliceCell, this, &PhysEqSolverTable::onRemoveTimeSliceCell);

    connect(this, &QTableWidget::cellActivated, this, &PhysEqSolverTable::oncellActivated);
    connect(this, &QTableWidget::cellChanged, this, &PhysEqSolverTable::oncellChanged);
    connect(this, &QTableWidget::cellClicked, this, &PhysEqSolverTable::oncellClicked);
    connect(this, &QTableWidget::cellDoubleClicked, this, &PhysEqSolverTable::oncellDoubleClicked);
    connect(this, &QTableWidget::cellEntered, this, &PhysEqSolverTable::oncellEntered);
    connect(this, &QTableWidget::cellPressed, this, &PhysEqSolverTable::oncellPressed);
    connect(this, &QTableWidget::currentCellChanged, this, &PhysEqSolverTable::oncurrentCellChanged);
    connect(this, &QTableWidget::currentItemChanged, this, &PhysEqSolverTable::oncurrentItemChanged);
    connect(this, &QTableWidget::itemActivated, this, &PhysEqSolverTable::onitemActivated);
    connect(this, &QTableWidget::itemChanged, this, &PhysEqSolverTable::onitemChanged);
    connect(this, &QTableWidget::itemClicked, this, &PhysEqSolverTable::onitemClicked);
    connect(this, &QTableWidget::itemDoubleClicked, this, &PhysEqSolverTable::onitemDoubleClicked);
    connect(this, &QTableWidget::itemEntered, this, &PhysEqSolverTable::onitemEntered);
    connect(this, &QTableWidget::itemPressed, this, &PhysEqSolverTable::onitemPressed);
    connect(this, &QTableWidget::itemSelectionChanged, this, &PhysEqSolverTable::onitemSelectionChanged);

}

void PhysEqSolverTable::setupTableLookAndFeel() {
    qDebug("PhysEqSolverTable::setupTableLookAndFeel()");
    QColor titleBackground(Qt::lightGray);
    QFont titleFont = font();
    titleFont.setBold(true);
    setMouseTracking(true);
    setItem(0, 0, new PhysEqSolverItem(""));
    item(0, 0) -> setBackgroundColor(titleBackground);
    item(0, 0) -> setFont(titleFont);
}

QTableWidgetItem *PhysEqSolverTable::createTableItem(PhysEqRow *pRow, bool bAttachObj) {
    qDebug("PhysEqSolverTable::createTableItem()");
    QTableWidgetItem *pItem = new QTableWidgetItem(pRow ->Name());
    pItem ->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
    if (bAttachObj) {
        QVariant var;
        var.setValue(pRow);
        pItem ->setData(Qt::UserRole, var);
    }
    return pItem;
}

// Creates both the initial row and the first time slice item
void PhysEqSolverTable::createTimeSliceRow(QList<double> lstTimeSlices) {
    qDebug("PhysEqSolverTable::createTimeSliceRow()");

    // Create the first row...
    PhysEqRow *pRow = new PhysEqRow(PhysEqRow::RT_TIMESLICE, "");
    m_lstRows.push_back(pRow);
    pRow ->Addy(EncodeAddy(m_lstRows.count()));

    // Insert the first cell in the row
    onAddTimeSliceCell(0, lstTimeSlices.at(0));
}

void PhysEqSolverTable::onAddTimeSliceCell(int col, double val) {
    qDebug("PhysEqSolverTable::onAddTimeSliceCell()");
    addPhysDataObjCell(0, col, QString(""), val);
}

// Need to do. Will wait for creation to work first...
void PhysEqSolverTable::onRemoveTimeSliceCell(int idx) {
    qDebug("PhysEqSolverTable::onRemoveTimeSliceCell()");
    int row = idx, col;
}

void PhysEqSolverTable::addPhysDataObjCell(const int row, const int col, const QString variable, const double val) {
    qDebug("PhysEqSolverTable::addPhysDataObjCell()");
    QString Addy = EncodeAddy(row, col);
    PhysEqRow *pRow = m_lstRows.at(row);
    if (pRow) {
        PhysEqGridCell *pCell = NULL;
        if (pRow ->Type() == PhysEqRow::RT_TIMESLICE)
            pCell = new PhysEqGridCell(new PhysTimeSliceDataObj(val), Addy);
        else {
            int type;
            switch (pRow ->Type()) {
            case PhysEqRow::RT_CARTGRAPH:
                type = PhysDataObj::DT_CARTGRAPH;
                break;
            case PhysEqRow::RT_PARTICLE:
                type = PhysDataObj::DT_PARTICLE;
                break;
            case PhysEqRow::RT_VECTOR:
                type = PhysDataObj::DT_VECTOR;
                break;
            case PhysEqRow::RT_PROPERTY:
                type = PhysDataObj::DT_PROPERTY;
                break;
            default:
                qDebug("PhysEqSolver::addPhysDataObjCell(): invalid RowType: %d", pRow ->Type());
                return;
            }
            pCell = new PhysEqGridCell(new PhysCellDataObj((PhysCellDataObj::DataType)type, variable, val), Addy);
        }
        if (pCell)
            pRow ->addCell(pCell);
    }
    else
        qDebug("PhysEqSolver::addPhysDataObjCell(): pRow is NULL");
}

PhysEqRow *PhysEqSolverTable::createPhysDataObjRow(PhysDataObj *pObj) {
    qDebug("PhysEqSolverTable::createPhysDataObjRow()");
    int rowIdx = m_lstRows.count();
    int numCols = columnCount();
    PhysEqRow *pRow = NULL;
    QString variable = "";
    PhysVectorDataObj *pVectorDataObj = NULL;

    if (pObj ->Type() == PhysDataObj::DT_PARTICLE)
        pRow  = new PhysEqRow(PhysEqRow::RT_PARTICLE, pObj ->Name());
    else if (pObj ->Type() == PhysDataObj::DT_VECTOR) {
        pVectorDataObj = static_cast<PhysVectorDataObj *>(pObj);
        pRow  = new PhysEqRow(PhysEqRow::RT_VECTOR, pVectorDataObj ->Name(), pVectorDataObj ->Equation());
        variable = pVectorDataObj ->Variable();
    }
    else if (pObj ->Type() == PhysDataObj::DT_PROPERTY)
        pRow  = new PhysEqRow(PhysEqRow::RT_PROPERTY, pVectorDataObj ->Name());
    else {
    }
    m_lstRows.push_back(pRow);
    pRow ->Addy(EncodeAddy(m_lstRows.count()));

    // Create the list of cells for each column
    for (int col = 0; col < numCols; col++)
        addPhysDataObjCell(rowIdx, col, variable, 0.0);
    return pRow;
}

// Visual and underlying data structure insertion
QTableWidgetItem *PhysEqSolverTable::createRowItem(PhysDataObj *pObj) {
    qDebug("PhysEqSolverTable::createRowItem()");
    PhysEqRow *pRow = createPhysDataObjRow(pObj);
    QTableWidgetItem *pItem = createTableItem(pRow, true);
    return pItem;
}




void PhysEqSolverTable::createParticleItems(int i, PhysParticle *pParticle) {
    qDebug("PhysEqSolverTable::createParticleItems()");
    switch (ModType()) {
    case SINGLEDIM_KINEMATICS:
        create1DKinematicItems(i, pParticle);
        break;
    default:
        qDebug("PhysEqSolver::createParticleItems(): Invalid Module type");
        break;
    }
}

void PhysEqSolverTable::create1DKinematicItems(int i, PhysParticle *pParticle) {
    qDebug("PhysEqSolverTable::create1DKinematicItems()");

    // create the Acceleration, Velocity, Gravity, displacement vectors
    // Important parameters are:
    //      - variable name
    //      - equation that defines it
    //      - boolean value that determines if it is to be drawn or not
    //      - Angle at which it should be represented on the CartesianGraph (if any)
    //      - Magnitude, or the value of the vector
    QList<PhysVector *> vectorList;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Temparary values so I can work on the UI... They will be removed later
    QString equation = QString("v*dt + 0.5*a*dt*dt");
    QString v = "0.0";
    QString a = "0.0";
    QString dx = "0.0";
    vectorList.push_back(new PhysVector(pParticle ->Parent(), pParticle, QString("a"), a, QString("accel"), a.toDouble(), false));
    vectorList.push_back(new PhysVector(pParticle ->Parent(), pParticle, QString("v"), v, QString("speed"), v.toDouble(), false));
    vectorList.push_back(new PhysVector(pParticle ->Parent(), pParticle, QString("dx"), equation, QString("displacement"), dx.toDouble(), false));

    foreach (PhysVector *item, vectorList) {
        insertRow(rowCount());
        QTableWidgetItem *pRowItem = createRowItem(item ->DataObj());
        setItem(rowCount() - 1, 0, pRowItem);
        setCurrentCell(rowCount() - 1, 1);
        for (int col = 1; col < columnCount(); col++)
            setGridTextAtRowColumn(rowCount() - 1, col, item -> Magnitude());
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void PhysEqSolverTable::onAddPhysEqSolverRow(QList<PhysParticle *> lstParticles) {
    qDebug("PhysEqSolver::onAddPhysEqSolverRow");
    m_pCalcTimer ->stop();
    int i = 0;
    foreach(PhysParticle *pParticle, lstParticles) {
        setItem(i++, 0, createRowItem(pParticle ->DataObj()));
        createParticleItems(i, pParticle);
    }
    m_pCalcTimer ->start();
}

void PhysEqSolverTable::setGridTextAtRowColumn(const int row, const int col, const double val) {
    qDebug("PhysEqSolverTable::setGridTextAtRowColumn()");
    if (row != -1 && col != -1) {
        QTableWidgetItem *pItem = item(row, col);
        if (pItem) {
            QString str;
            QTextStream(&str) << val;
            pItem -> setData(Qt::EditRole, str);
        }
    }
}

bool PhysEqSolverTable::resolveEquation(ValueSet &vs, const string equation) {
    qDebug("PhysEqSolverTable::resolveEquation()");
    ExpressionBuilder builder;
    builder.prepData(equation);
    RPNExpression rpnExpr = builder.build();

    std::vector<double> *pResultSet = rpnExpr.calculate(vs = builder.EquationValues());
    vs.resultSet(pResultSet);
    if (vs.empty())
        return false;
    return true;
}

QString PhysEqSolverTable::calculateRows(QList<PhysEqRow *>::Iterator &iterCurrRow, QString baseEq, const double dt, bool bStripConsts) {
    qDebug("PhysEqSolverTable::calculateRows()");
    if (iterCurrRow == m_lstRows.end())
        return "";
    PhysEqRow *pRow = *iterCurrRow;
    if (pRow ->Type() == PhysEqRow::RT_VECTOR) {

        // Make sure that the row has an equation to solve for
        if (!(pRow ->Equation().trimmed().isEmpty())) {
            string eq = baseEq.trimmed().toUtf8().data();
            Stargate7 sg7(pRow ->Equation());
            vector<string> eqTokens;
            map<string, bool> eqTokensMap = m_eqTokensMap;
            if (sg7.parse(eq, eqTokens, eqTokensMap, bStripConsts)) {

                // eqTokens after being parsed lists out the pieces. need to
                // Loop through seeing what is a variable and what is a constant.
                // If it's a variable then we need to look at it's equation and resolve that before continuing.
                for (map<string, bool>::iterator iterTokenMap = eqTokensMap.begin(); iterTokenMap != eqTokensMap.end(); iterTokenMap++) {
                    bool isVariable = (*iterTokenMap).second;
                    if (isVariable) {

                        // Look for the item in the row list
                        for (QList<PhysEqRow *>::Iterator iterRowSearch = m_lstRows.begin(); iterRowSearch != m_lstRows.end(); iterRowSearch++) {
                            if (iterRowSearch == m_iterCurrRow)
                                continue;
                            PhysEqRow *pRow = *iterRowSearch;
                            QString eq = pRow ->Equation();
                            QString value = calculateRows(iterRowSearch, eq, dt);
                            if (!value.isEmpty()) {
                                if (!pRow -> isCalculated()) {
                                    m_strVarAssignments += ", " + pRow ->Variable() + "=" + value;
                                    pRow -> Calculated(true);
                                }
                            }
                        }
                    }

                    // it's an integer so return from the function
                    else
                        return QString::fromStdString(eq);
                }
            }
        }
    }
    return "";
}
// Function Name: getRowAtIndex()
// Purpose: returns the row in the equation grid
//
//
//
PhysEqRow *PhysEqSolverTable::getRowAtIndex(const int idx) {
    qDebug("PhysEqSolverTable::getRowAtIndex()");
    PhysEqRow *pItem = NULL;
    int curr_row = 0;

    for (QList<PhysEqRow *>::Iterator iter = m_lstRows.begin(); iter != m_lstRows.end(); iter++) {
        PhysEqRow *pRow = *iter;
        if (pRow ->Type() == PhysEqRow::RT_VECTOR) {
            curr_row++;
            if (curr_row == idx) {
               pItem = pRow;
               break;
            }
        }
    }

    return pItem;
}
// Function Name: oncellActivated()
// Purpose: Manages the grid edit areas.
// Note: Only the cell for t0 should be editable for values at the beginning.
//
//
void PhysEqSolverTable::oncellActivated(int row, int col) {
    qDebug("PhysEqSolverTable::oncellActivated()");

    // Only col for t0  (col == 1) should be editable for values. Everything after that are calculated based on the equation
    // associated with the row.
    if (col != 1)
        return;
    PhysEqSolverItem *pItem = static_cast<PhysEqSolverItem *>(item(row, col));
    QVariant var = pItem ->data(Qt::EditRole);

    // Get Row item that is associated with the integer value of row
    PhysEqRow *pRow = getRowAtIndex(row);
    if (pRow) {
        pRow ->Equation(var.toString());
        double val = var.toDouble();

        pItem -> setData(Qt::EditRole, QString::number(val));
    }
}

void PhysEqSolverTable::onCalculate() {
    qDebug("PhysEqSolver::onCalculate()");

    if (rowCount() > 0) {

        // Now loop through each column and build a calculation set for that column.
        // Then set the text for that grid cell in the table.
        // NOTE: for future usage, it might be useful to use a matrix for
        //      calculations then loop through it and just dump text.
        double dt;
        for (int i = 1; i < columnCount(); i++) {
            dt = (i > 1) ? TimeSlice(i - 1) : 0.0;

            // Set the time variable
            QString timeVar = QString("dt = %1").arg(dt);

            // Loop through the rows trying to resolve the equations that are there.
            int k = 0;
            for (QList<PhysEqRow *>::Iterator iter = m_lstRows.begin(); iter != m_lstRows.end(); iter++) {
                PhysEqRow *pRow = *iter;
                if (pRow ->Type() == PhysEqRow::RT_VECTOR) {
                    QString strJD;
                    m_strVarAssignments = "";
                    m_eqJumpDrive = pRow ->Equation();
                    m_iterCurrRow = iter;
                    // printRow(pRow, k); k++;
                    calculateRows(iter, m_eqJumpDrive, dt, true);
                    if (m_strVarAssignments.size() > 0)
                        strJD = pRow ->Equation() + m_strVarAssignments + ", " + timeVar;
                    else {
                        m_strVarAssignments = pRow -> Equation();
                        strJD = pRow ->Equation();
                    }

                    if (m_strVarAssignments.size() > 0) {
                        ValueSet vs;
                        string str = strJD.toUtf8().data();
                        if (resolveEquation(vs, str))
                            setGridTextAtRowColumn(m_lstRows.indexOf(pRow) - 1, i, vs.Value());
                    }
                    pRow ->Calculated(false);
                }
            }
        }
    }
}

void PhysEqSolverTable::updateLineEdit(QTableWidgetItem *pItem) {
    qDebug("PhysEqSolverTable::updateLineEdit()");
    if (pItem) {
        if (pItem == currentItem()) {
            if (pItem)
                m_pFormulaInput -> setText(pItem -> data(Qt::EditRole).toString());
            else
                m_pFormulaInput -> clear();
        }
    }
}

void PhysEqSolverTable::returnPressed() {
    qDebug("PhysEqSolverTable::returnPressed()");
    QString text = m_pFormulaInput -> text();
    int row = currentRow();
    int col = currentColumn();
    QTableWidgetItem *pItem = item(row, col);
    if (!pItem)
        setItem(row, col, pItem = new PhysEqSolverItem(text));
    else
        pItem -> setData(Qt::EditRole, text);
    viewport() -> update(visualItemRect(pItem));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Static functions
///
///
void PhysEqSolverTable::DecodeAddy(const QString addy, int *pRow, int *pCol) {
    qDebug("PhysEqSolverTable::DecodeAddy()");
    if (addy.trimmed().isEmpty()) {
        *pCol = -1;
        *pRow = -1;
    }
    else {
        bool bOk;
        QStringList lstAddyParts = addy.split(":");
        QString row = lstAddyParts.at(0);
        *pRow = row.toUInt(&bOk, 16);
        if (pCol) {
            QString col = lstAddyParts.at(1);
            *pCol = col.toUInt(&bOk, 16);
        }
    }
}

QString PhysEqSolverTable::EncodeAddy(const int row, const int col) {
    qDebug("PhysEqSolverTable::EncodeAddy()");
    QString rowHex, columnHex;

    rowHex.asprintf("%x", row);
    if (col == -1)
        return rowHex;
    columnHex.asprintf("%x", col);
    return QString(rowHex + ":" + columnHex);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief PhysEqSolverTable::onUpdateParticleName
/// \param prevName
/// \param name
///
void PhysEqSolverTable::onUpdateParticleName(const QString prevName, const QString name) {
    qDebug("PhysEqSolverTable::onUpdateParticleName()");
    foreach (PhysEqRow *pRow, m_lstRows) {
        if (pRow ->Type() == PhysEqRow::RT_PARTICLE) {
            /*
            pRow ->DataObj() ->Name().compare(prevName)
            if ((pObj) && pObj ->Name().compare(prevName) == 0) {

            }
            */
        }
    }
}

void PhysEqSolverTable::createStandardContextMenu(QMenu *pctxMenu) {
    qDebug("PhysEqSolverTable::createStandardContextMenu()");
    // Primary menu actions
    QAction *pFont = new QAction(tr("Font..."), this);
    connect(pFont, SIGNAL(triggered()), this, SLOT(onSelectFont()));
    QAction *pColor = new QAction(QPixmap(16, 16), tr("Background &Color..."), this);
    connect(pColor, SIGNAL(triggered()), this, SLOT(onSelectColor()));
    QAction *pClear = new QAction(tr("Clear"), this);
    connect(pClear, SIGNAL(triggered()), this, SLOT(onClear()));
    pctxMenu -> addAction(pFont);
    pctxMenu -> addAction(pColor);
    pctxMenu -> addAction(pClear);
}

void PhysEqSolverTable::onCustomContextMenu(const QPoint &pos) {
    qDebug("PhysEqSolverTable::onCustomContextMenu()");

    // Check to see if the pos is inside of the first column, as that needs a different context menu
    QModelIndex index = indexAt(pos);
    QMenu ctxMenu;

    if (index.isValid()) {
        m_currItem.row = index.row();
        m_currItem.column = index.column();

        QMenu subCtxMenu(tr("Physics Objects..."));
        QMenu subCtxMenuVectors(tr("Vectors..."));
        QMenu subCtxMenuOther(tr("Other..."));

        createStandardContextMenu(&ctxMenu);

        // If in first column then we need to check and see what row it is. get that information to populate the
        // dialog box.
        if (m_currItem.column == 0) {
            QAction *m_pRowProperties = new QAction(tr("Properties..."), this);
            connect(m_pRowProperties, SIGNAL(triggered()), this, SLOT(onRowProperties()));
            ctxMenu.addAction(m_pRowProperties);
        }
        else {

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

    // Not right-clicking in a row or column, so bring up the "Add Row, Properties" choices
    else {


        QMenu subCtxMenu(tr("Add Row..."));

        // Secondary submenus
        // Vectors
        QAction *pAddRow = new QAction(tr("Add Row"), this);
        connect(pAddRow, SIGNAL(triggered()), this, SLOT(onAddPhysEqSolverRow(QList<PhysParticle *>)));

        subCtxMenu.addAction(pAddRow);
        ctxMenu.addMenu(&subCtxMenu);
        ctxMenu.exec(mapToGlobal(pos));
    }
}

void PhysEqSolverTable::onRowProperties() {
    qDebug("PhysEqSolverTable::onRowProperties()");
    QDialog *pDlg = new QDialog(0,0);
    Ui_PhysEqRowDlg dlg;
    QVariant itemData = item(currentRow(), 0) ->data(Qt::UserRole);
    PhysEqRow *pRow = itemData.value<PhysEqRow *>();

    if (pRow) {
        dlg.setupUi(pDlg);
        if (pRow ->Type() == PhysEqRow::RT_PARTICLE || pRow ->Type() == PhysEqRow::RT_VECTOR || pRow ->Type() == PhysEqRow::RT_PROPERTY) {
            dlg.edtRowEq ->setText(pRow ->Equation());
            dlg.edtRowVariable ->setText(pRow ->Variable());
            dlg.edtRowLabel ->setText(pRow ->Name());
            if (pDlg ->exec() == QDialog::Accepted) {
                pRow ->Variable(dlg.edtRowVariable ->text());
                pRow ->Equation(dlg.edtRowEq ->text());
                pRow ->Name(dlg.edtRowLabel ->text());
            }
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
            dlg.m_lstParticles ->addItem(new QListWidgetItem(pObj ->Name()));
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
    qDebug("PhysEqSolverTable::onUpdateTimeSlices()");
    m_TimeSliceValues = m_pHeader ->timeSliceList();
    rebuildColumnHeaders();
}

void PhysEqSolverTable::createTableHeader() {
    qDebug("PhysEqSolverTable::createTableHeader()");
    m_TimeSliceValues.push_back(0.0);
    setHorizontalHeader(m_pHeader = new PhysEqSolverTableHeader(m_TimeSliceValues, this));
    setHorizontalHeaderLabels(QStringList() << "" << "t0");
    horizontalHeader() ->setVisible(true);
    rebuildColumnHeaders();
}

void PhysEqSolverTable::insertColumn() {
    qDebug("PhysEqSolverTable::insertColumn()");

    // When inserting a new column with the default value, it should be added to the previous column
    double newValue = m_TimeSliceValues.at(m_TimeSliceValues.count() - 1) + 1.0;
    m_TimeSliceValues.push_back(newValue);
    m_pHeader ->timeSliceList(m_TimeSliceValues);
    model() ->insertColumn(model() ->columnCount());
    rebuildColumnHeaders();

    emit addTimeSliceCell(m_TimeSliceValues.count() - 1, newValue);
}

void PhysEqSolverTable::removeColumn(const int idx) {
    qDebug("PhysEqSolverTable::removeColumn()");
    if (model() ->columnCount() > 2) {
        model() ->removeColumn(idx);
        m_TimeSliceValues.removeAt(idx);
        m_pHeader ->timeSliceList(m_TimeSliceValues);
        rebuildColumnHeaders();
        emit removeTimeSliceCell(idx);
    }
}

QSize PhysEqSolverTable::minimumSizeHint() const {
    qDebug("PhysEqSolverTable::minimumSizeHint()");
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
    qDebug("PhysEqSolverTable::sizeHint()");
    return QTableWidget::sizeHint();//minimumSizeHint();
}

void PhysEqSolverTable::rebuildColumnHeaders() {
    qDebug("PhysEqSolverTable::rebuildColumnHeaders()");
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
    qDebug("PhysEqSolverTable::onSelectColor()");
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
    qDebug("PhysEqSolverTable::onSelectFont()");
    QList<QTableWidgetItem *> items = selectedItems();
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
    qDebug("PhysEqSolverTable::onClear()");
    foreach (QTableWidgetItem *pItem, selectedItems())
        pItem -> setText("");
}

void PhysEqSolverTable::updateColor(QTableWidgetItem *pItem) {
    qDebug("PhysEqSolverTable::updateColor()");
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

void PhysEqSolverTable::printRow(PhysEqRow *pRow, int i) {
    qDebug("PhysEqSolverTable::printRow()");
    qDebug() << "Dumping row #: " << QString::number(i);
    qDebug() << "\tVariable: " << pRow ->Variable();
    qDebug() << "\tEquation: " << pRow -> Equation();
    QString strType;
    switch (pRow ->Type()) {
    case PhysEqRow::RT_VECTOR:
        strType = "Vector";
        break;
    case PhysEqRow::RT_CARTGRAPH:
        strType = "CartGraph";
        break;
    case PhysEqRow::RT_PARTICLE:
        strType = "Particle";
        break;
    case PhysEqRow::RT_PROPERTY:
        strType = "Property";
        break;
    case PhysEqRow::RT_TIMESLICE:
        strType = "Timeslice";
        break;
    }
    qDebug() << "\tType: " << strType;
}

void PhysEqSolverTable::oncellChanged(int row, int col) {
    qDebug("PhysEqSolverTable::oncellChanged()");
    bool bVal = true;

}
void PhysEqSolverTable::oncellClicked(int row, int col) {
    qDebug("PhysEqSolverTable::oncellClicked()");
    bool bVal = true;

}
void PhysEqSolverTable::oncellDoubleClicked(int row, int column) {
    qDebug("PhysEqSolverTable::oncellDoubleClicked()");
    bool bVal = true;

}
void PhysEqSolverTable::oncellEntered(int row, int column) {
    qDebug("PhysEqSolverTable::oncellEntered()");
    bool bVal = true;

}
void PhysEqSolverTable::oncellPressed(int row, int column) {
    qDebug("PhysEqSolverTable::oncellPressed()");
    bool bVal = true;

}
void PhysEqSolverTable::oncurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn) {
    qDebug("PhysEqSolverTable::oncurrentCellChanged()");
    bool bVal = true;

}
void PhysEqSolverTable::oncurrentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous) {
    qDebug("PhysEqSolverTable::oncurrentItemChanged()");
    bool bVal = true;

}
void PhysEqSolverTable::onitemActivated(QTableWidgetItem *item) {
    qDebug("PhysEqSolverTable::onitemActivated()");
    bool bVal = true;

}
void PhysEqSolverTable::onitemChanged(QTableWidgetItem *item) {
    qDebug("PhysEqSolverTable::onitemChanged()");
    bool bVal = true;

}
void PhysEqSolverTable::onitemClicked(QTableWidgetItem *item) {
    qDebug("PhysEqSolverTable::onitemClicked()");
    bool bVal = true;

}
void PhysEqSolverTable::onitemDoubleClicked(QTableWidgetItem *item) {
    qDebug("PhysEqSolverTable::onitemDoubleClicked()");
    bool bVal = true;

}
void PhysEqSolverTable::onitemEntered(QTableWidgetItem *item) {
    qDebug("PhysEqSolverTable::onitemEntered()");
    bool bVal = true;

}
void PhysEqSolverTable::onitemPressed(QTableWidgetItem *item) {
    qDebug("PhysEqSolverTable::onitemPressed()");
    bool bVal = true;

}
void PhysEqSolverTable::onitemSelectionChanged() {
    qDebug("PhysEqSolverTable::onitemSelectionChanged()");
    bool bVal = true;
}
