#include <QtWidgets>
#include <map>

#include "physeqsolver.h"
#include "physeqsolverdelegate.h"
#include "physeqsolveritem.h"
#include "physprintview.h"
#include "physeqsolvertable.h"
#include "physdataobj.h"
#include "physeqgrid.h"
#include "physcalculatetimer.h"
#include "phystimeslicedataobj.h"
#include "physcelldataobj.h"
#include "physeqrow.h"
#include "physshuntyardparser.h"
#include "stargate7.h"

#include "jumpdrive/ExpressionBuilder.h"

PhysEqSolver::PhysEqSolver(int rows, int cols, QWidget *pParent) : QTableView(pParent) {
    m_pTable = NULL;
    m_pGrid = NULL;
    m_pFormulaInput = new QLineEdit();
    m_pCalcTimer = new PhysCalculateTimer(this, 1000);
    m_pCalcTimer ->start();
    createTable(rows, cols);
    setupContextMenu();
    createConnections();
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    createTimeSliceRow(m_pTable ->TimeSliceValues());
}

void PhysEqSolver::createConnections() {
    connect(m_pTable, SIGNAL(currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)), this, SLOT(updateLineEdit(QTableWidgetItem *)));
    connect(m_pFormulaInput, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(m_pTable, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(updateLineEdit(QTableWidgetItem *)));
    connect(m_pTable, SIGNAL(addPhysEqSolverRow(QList<PhysParticle *>)), this, SLOT(onAddPhysEqSolverRow(QList<PhysParticle *>)));
    connect(m_pCalcTimer ->Timer(), SIGNAL(timeout()), this, SLOT(onCalculate()));
    connect(m_pTable, SIGNAL(addTimeSliceCell(int, double)), this, SLOT(onAddTimeSliceCell(int, double)));
    connect(m_pTable, SIGNAL(removeTimeSliceCell(int)), this, SLOT(onRemoveTimeSliceCell(int)));
}

void PhysEqSolver::onUpdateParticleName(const QString prevName, const QString name) {
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

void PhysEqSolver::createTable(const int rows, const int cols) {
    m_pTable = new PhysEqSolverTable(rows, cols, this);
    setupTableLookAndFeel();

    // Creates the underlying data structure for doing calculations
    createGrid();
}

void PhysEqSolver::setupTableLookAndFeel() {
    QColor titleBackground(Qt::lightGray);
    QFont titleFont = m_pTable -> font();
    titleFont.setBold(true);

    m_pTable -> setItem(0, 0, new PhysEqSolverItem(""));
    m_pTable -> item(0, 0) -> setBackgroundColor(titleBackground);
    m_pTable -> item(0, 0) -> setFont(titleFont);
}

void PhysEqSolver::createGrid() {
    m_pGrid = new PhysEqGrid();
}

QTableWidgetItem *PhysEqSolver::createTableItem(PhysDataObj *pObj, bool bAttachObj) {
    QTableWidgetItem *pItem = new QTableWidgetItem(pObj ->Name());
    pItem ->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    if (bAttachObj) {
        QVariant var;
        var.setValue(pObj);
        pItem ->setData(Qt::UserRole, var);
    }
    return pItem;
}


// Creates both the initial row and the first time slice item
void PhysEqSolver::createTimeSliceRow(QList<double> lstTimeSlices) {

    // Create the first row...
    PhysEqRow *pRow = new PhysEqRow(PhysEqRow::RT_TIMESLICE);
    m_lstRows.push_back(pRow);
    pRow ->Addy(EncodeAddy(m_lstRows.count()));

    // Insert the first cell in the row
    onAddTimeSliceCell(0, lstTimeSlices.at(0));
}

void PhysEqSolver::onAddTimeSliceCell(int col, double val) {
    addPhysDataObjCell(0, col, QString(""), val);
}

// Need to do. Will wait for creation to work first...
void PhysEqSolver::onRemoveTimeSliceCell(int idx) {
    int row = idx, col;
}

void PhysEqSolver::addPhysDataObjCell(const int row, const int col, const QString variable, const double val) {
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

void PhysEqSolver::createPhysDataObjRow(PhysDataObj *pObj) {
    int rowIdx = m_lstRows.count();
    int numCols = m_pTable ->columnCount();
    PhysEqRow *pRow = NULL;
    QString variable = "";
    PhysVectorDataObj *pVectorDataObj = NULL;

    if (pObj ->Type() == PhysDataObj::DT_PARTICLE)
        pRow  = new PhysEqRow(PhysEqRow::RT_PARTICLE);
    else if (pObj ->Type() == PhysDataObj::DT_VECTOR) {
        pVectorDataObj = static_cast<PhysVectorDataObj *>(pObj);
        pRow  = new PhysEqRow(PhysEqRow::RT_VECTOR, pVectorDataObj ->Equation());
        variable = pVectorDataObj ->Variable();
    }
    else if (pObj ->Type() == PhysDataObj::DT_PROPERTY)
        pRow  = new PhysEqRow(PhysEqRow::RT_PROPERTY);
    else {
    }
    m_lstRows.push_back(pRow);
    pRow ->Addy(EncodeAddy(m_lstRows.count()));

    // Create the list of cells for each column
    for (int col = 0; col < numCols; col++)
        addPhysDataObjCell(rowIdx, col, variable, 0.0);
}

// Visual and underlying data structure insertion
QTableWidgetItem *PhysEqSolver::createRowItem(PhysDataObj *pObj) {
    createPhysDataObjRow(pObj);
    return createTableItem(pObj, true);
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
    QList<PhysVector *> lst;
    lst.push_front(new PhysVector(pParticle ->Parent(), pParticle,
                                        QString("a"), QString("0"), QString("accel"), false));
    lst.push_front(new PhysVector(pParticle ->Parent(), pParticle,
                                           QString("v"), QString("12"), QString("speed"), false));
    lst.push_front(new PhysVector(pParticle ->Parent(), pParticle,
                                               QString("dx"), QString("v*dt + 0.5*a*dt*dt"), QString("displacement"), false));

    foreach(PhysVector *item, lst) {
        m_pTable ->insertRow(i);
        m_pTable ->setItem(i, 0, createRowItem(item ->DataObj()));
    }
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
    m_pCalcTimer ->start();
}

QStringList PhysEqSolver::separateEquationFromVariables(QString strEquation) {
    QStringList lst = strEquation.split(",");
    foreach(QString str, lst) {

    }
}

QList<double> PhysEqSolver::findValuesOfVariablesInGrid(PhysEqRow *pRow) {
    QList<double> lstValues;

    return lstValues;
}

void PhysEqSolver::setGridTextAtRowColumn(const int row, const int col, const double val) {
    if (row != -1 && col != -1) {
        QTableWidgetItem *pItem = m_pTable -> item(row, col);
        if (pItem) {
            QString str;
            QTextStream(&str) << val;
            pItem -> setData(Qt::EditRole, str);
            m_pTable -> viewport() -> update(m_pTable ->visualItemRect(pItem));
        }
    }
}

bool PhysEqSolver::resolveEquation(ValueSet &vs, const string equation) {
    ExpressionBuilder builder;
    builder.prepData(equation);
    std::vector<double> *pResultSet = builder.build().calculate(builder.EquationValues());
    vs.resultSet(pResultSet);
    if (vs.empty())
        return false;
    return true;
}

bool PhysEqSolver::resolveVariable(pair<string, double> &resolution, string variable) {

    foreach (PhysEqRow *pRow, m_lstRows) {
        if (pRow ->Variable().compare(QString(variable.c_str()))) {
            resolution = { variable, true };
        }
    }

    return true;
}

QString PhysEqSolver::calculateRows(QList<PhysEqRow *>::Iterator &iterCurrRow, QString baseEq, const double dt, bool bStripConsts) {
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

void PhysEqSolver::onCalculate() {
    qDebug("PhysEqSolver::onCalculate()");

    if (m_pTable ->rowCount() > 0) {

        // Now loop through each column and build a calculation set for that column.
        // Then set the text for that grid cell in the table.
        // NOTE: for future usage, it might be useful to use a matrix for
        //      calculations then loop through it and just dump text.
        double currTimeSlice, prevTimeSlice;
        double dt;
        for (int i = 1; i < m_pTable ->columnCount(); i++) {
            if (i == 1) {
                currTimeSlice = prevTimeSlice = m_pTable ->TimeSlice(0);
                dt = 0.0;
            }
            else {
                currTimeSlice = m_pTable ->TimeSlice(i - 1);
                prevTimeSlice = m_pTable ->TimeSlice(i - 2);
                dt = currTimeSlice - prevTimeSlice;
            }

            // Set the time variable
            QString timeVar = QString("dt = %1").arg(dt);

            // Loop through the rows trying to resolve the equations that are there.
            for (QList<PhysEqRow *>::Iterator iter = m_lstRows.begin(); iter != m_lstRows.end(); iter++) {
                PhysEqRow *pRow = *iter;
                m_strVarAssignments = "";
                m_eqJumpDrive = (*iter) ->Equation();
                m_iterCurrRow = iter;
                calculateRows(iter, m_eqJumpDrive, dt, true);
                if (m_strVarAssignments.size() > 0) {
                    QString strJD = (*iter) ->Equation() + m_strVarAssignments + ", " + timeVar;
                    ValueSet vs;
                    string str = strJD.toUtf8().data();
                    if (resolveEquation(vs, str))
                        setGridTextAtRowColumn(m_lstRows.count() - m_lstRows.indexOf(pRow), i, vs.Value());
                }
                pRow ->Calculated(false);
            }
        }
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
        m_pTable -> setItem(row, col, pItem = new PhysEqSolverItem(text));
    else
        pItem -> setData(Qt::EditRole, text);
    m_pTable -> viewport() -> update(m_pTable ->visualItemRect(pItem));
}

void PhysEqSolver::setupContextMenu() {
    setContextMenuPolicy(Qt::ActionsContextMenu);
}

void PhysEqSolver::DecodeAddy(const QString addy, int *pRow, int *pCol) {
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

QString PhysEqSolver::EncodeAddy(const int row, const int col) {
    QString rowHex, columnHex;

    rowHex.sprintf("%x", row);
    if (col == -1)
        return rowHex;
    columnHex.sprintf("%x", col);
    return QString(rowHex + ":" + columnHex);
}

