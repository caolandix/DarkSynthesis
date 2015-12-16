#include <QtWidgets>
#ifndef QT_NO_PRINTER
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#endif

#include "physeqsolver.h"
#include "physeqsolverdelegate.h"
#include "physeqsolveritem.h"
#include "physprintview.h"
#include "physeqsolvertable.h"

PhysEqSolver::PhysEqSolver(int rows, int cols, QWidget *pParent) : QTableView(pParent) {
    m_pTable = NULL;
    m_pFormulaInput = new QLineEdit();

    createTable(rows, cols);
    setupContents();
    setupContextMenu();
    createConnections();
}

void PhysEqSolver::createConnections() {
    connect(m_pTable, SIGNAL(currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)), this, SLOT(updateLineEdit(QTableWidgetItem *)));
    connect(m_pTable, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(updateStatus(QTableWidgetItem *)));
    connect(m_pFormulaInput, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(m_pTable, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(updateLineEdit(QTableWidgetItem *)));
    connect(m_pTable, SIGNAL(addPhysEqSolverRow(QString)), this, SLOT(onAddPhysEqSolverRow(QString)));
}

void PhysEqSolver::createTable(const int rows, const int cols) {
    m_pTable = new PhysEqSolverTable(rows, cols, this);
}

void PhysEqSolver::onAddPhysEqSolverRow(QString objName) {

}

void PhysEqSolver::updateLineEdit(QTableWidgetItem *pItem) {
    if (pItem == m_pTable -> currentItem()) {
        if (pItem)
            m_pFormulaInput -> setText(pItem -> data(Qt::EditRole).toString());
        else
            m_pFormulaInput -> clear();
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

void PhysEqSolver::actionMath_helper(const QString &title, const QString &op) {
    QString cell1 = "C1";
    QString cell2 = "C2";
    QString out = "C3";

    QTableWidgetItem *pCurrent = m_pTable -> currentItem();
    if (pCurrent)
        out = encode_pos(m_pTable -> currentRow(), m_pTable -> currentColumn());

    if (runInputDialog(title, tr("Cell 1"), tr("Cell 2"), op, tr("Output to:"), &cell1, &cell2, &out)) {
        int row, col;
        decode_pos(out, &row, &col);
        m_pTable -> item(row, col) -> setText(tr("%1 %2 %3").arg(op, cell1, cell2));
    }
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
    if (runInputDialog(tr("Sum cells"), tr("First cell:"), tr("Last cell:"),
                       QString("%1").arg(QChar(0x03a3)), tr("Output to:"), &cell1, &cell2, &out)) {
        int row;
        int col;
        decode_pos(out, &row, &col);
        m_pTable -> item(row, col) -> setText(tr("sum %1 %2").arg(cell1, cell2));
    }
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

bool PhysEqSolver::runInputDialog(const QString &title, const QString &c1Text, const QString &c2Text,
                                 const QString &opText, const QString &outText, QString *pCell1,
                                  QString *pCell2, QString *pOutCell) {
    QStringList rows, cols;
    for (int c = 0; c < m_pTable -> columnCount(); ++c)
        cols << QChar('A' + c);
    for (int r = 0; r < m_pTable -> rowCount(); ++r)
        rows << QString::number(1 + r);

    QDialog addDialog(this);
    addDialog.setWindowTitle(title);

    QGroupBox group(title, &addDialog);
    group.setMinimumSize(250, 100);

    QLabel cell1Label(c1Text, &group);
    QComboBox cell1RowInput(&group);
    int c1Row, c1Col;
    decode_pos(*pCell1, &c1Row, &c1Col);
    cell1RowInput.addItems(rows);
    cell1RowInput.setCurrentIndex(c1Row);

    QComboBox cell1ColInput(&group);
    cell1ColInput.addItems(cols);
    cell1ColInput.setCurrentIndex(c1Col);

    QLabel operatorLabel(opText, &group);
    operatorLabel.setAlignment(Qt::AlignHCenter);

    QLabel cell2Label(c2Text, &group);
    QComboBox cell2RowInput(&group);
    int c2Row, c2Col;
    decode_pos(*pCell2, &c2Row, &c2Col);
    cell2RowInput.addItems(rows);
    cell2RowInput.setCurrentIndex(c2Row);
    QComboBox cell2ColInput(&group);
    cell2ColInput.addItems(cols);
    cell2ColInput.setCurrentIndex(c2Col);

    QLabel equalsLabel("=", &group);
    equalsLabel.setAlignment(Qt::AlignHCenter);

    QLabel outLabel(outText, &group);
    QComboBox outRowInput(&group);
    int outRow, outCol;

    decode_pos(*pOutCell, &outRow, &outCol);
    outRowInput.addItems(rows);
    outRowInput.setCurrentIndex(outRow);
    QComboBox outColInput(&group);
    outColInput.addItems(cols);
    outColInput.setCurrentIndex(outCol);

    QPushButton cancelButton(tr("Cancel"), &addDialog);
    connect(&cancelButton, SIGNAL(clicked()), &addDialog, SLOT(reject()));

    QPushButton okButton(tr("OK"), &addDialog);
    okButton.setDefault(true);
    connect(&okButton, SIGNAL(clicked()), &addDialog, SLOT(accept()));

    QHBoxLayout *pButtonsLayout = new QHBoxLayout;
    pButtonsLayout -> addStretch(1);
    pButtonsLayout -> addWidget(&okButton);
    pButtonsLayout -> addSpacing(10);
    pButtonsLayout -> addWidget(&cancelButton);

    QVBoxLayout *pDialogLayout = new QVBoxLayout(&addDialog);
    pDialogLayout -> addWidget(&group);
    pDialogLayout -> addStretch(1);
    pDialogLayout -> addItem(pButtonsLayout);

    QHBoxLayout *pCell1Layout = new QHBoxLayout;
    pCell1Layout -> addWidget(&cell1Label);
    pCell1Layout -> addSpacing(10);
    pCell1Layout -> addWidget(&cell1ColInput);
    pCell1Layout -> addSpacing(10);
    pCell1Layout -> addWidget(&cell1RowInput);

    QHBoxLayout *pCell2Layout = new QHBoxLayout;
    pCell2Layout -> addWidget(&cell2Label);
    pCell2Layout -> addSpacing(10);
    pCell2Layout -> addWidget(&cell2ColInput);
    pCell2Layout -> addSpacing(10);
    pCell2Layout -> addWidget(&cell2RowInput);

    QHBoxLayout *pOutLayout = new QHBoxLayout;
    pOutLayout -> addWidget(&outLabel);
    pOutLayout -> addSpacing(10);
    pOutLayout -> addWidget(&outColInput);
    pOutLayout -> addSpacing(10);
    pOutLayout -> addWidget(&outRowInput);

    QVBoxLayout *pVLayout = new QVBoxLayout(&group);
    pVLayout -> addItem(pCell1Layout);
    pVLayout -> addWidget(&operatorLabel);
    pVLayout -> addItem(pCell2Layout);
    pVLayout -> addWidget(&equalsLabel);
    pVLayout -> addStretch(1);
    pVLayout -> addItem(pOutLayout);

    if (addDialog.exec()) {
        *pCell1 = cell1ColInput.currentText() + cell1RowInput.currentText();
        *pCell2 = cell2ColInput.currentText() + cell2RowInput.currentText();
        *pOutCell = outColInput.currentText() + outRowInput.currentText();
        return true;
    }
    return false;
}
