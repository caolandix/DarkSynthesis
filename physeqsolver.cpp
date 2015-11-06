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

PhysEqSolver::PhysEqSolver(int rows, int cols, QWidget *parent) : QTableView(parent) {
    m_pFormulaInput = new QLineEdit();

/*
    cellLabel = new QLabel(parent ->toolBar);
    cellLabel -> setMinimumSize(80, 0);

    toolBar -> addWidget(cellLabel);
    toolBar -> addWidget(m_pFormulaInput);
*/
    m_pTable = new QTableWidget(rows, cols, this);
    m_pTable -> setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    for (int c = 0; c < cols; ++c) {
        QString character(QChar('A' + c));
        m_pTable -> setHorizontalHeaderItem(c, new QTableWidgetItem(character));
    }

    m_pTable -> setItemPrototype(m_pTable -> item(rows - 1, cols - 1));
    m_pTable -> setItemDelegate(new PhysEqSolverDelegate());

    createActions();
    updateColor(0);
    setupMenuBar();
    setupContents();
    setupContextMenu();
    // setCentralWidget(m_pTable);

    // statusBar();
    connect(m_pTable, SIGNAL(currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)), this, SLOT(updateStatus(QTableWidgetItem *)));
    connect(m_pTable, SIGNAL(currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)), this, SLOT(updateColor(QTableWidgetItem *)));
    connect(m_pTable, SIGNAL(currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)), this, SLOT(updateLineEdit(QTableWidgetItem *)));
    connect(m_pTable, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(updateStatus(QTableWidgetItem *)));
    connect(m_pFormulaInput, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(m_pTable, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(updateLineEdit(QTableWidgetItem *)));
    setWindowTitle(tr("Physics Equation Solver"));
}

void PhysEqSolver::createActions() {
    cell_sumAction = new QAction(tr("Sum"), this);
    connect(cell_sumAction, SIGNAL(triggered()), this, SLOT(actionSum()));

    cell_addAction = new QAction(tr("&Add"), this);
    cell_addAction->setShortcut(Qt::CTRL | Qt::Key_Plus);
    connect(cell_addAction, SIGNAL(triggered()), this, SLOT(actionAdd()));

    cell_subAction = new QAction(tr("&Subtract"), this);
    cell_subAction->setShortcut(Qt::CTRL | Qt::Key_Minus);
    connect(cell_subAction, SIGNAL(triggered()), this, SLOT(actionSubtract()));

    cell_mulAction = new QAction(tr("&Multiply"), this);
    cell_mulAction->setShortcut(Qt::CTRL | Qt::Key_multiply);
    connect(cell_mulAction, SIGNAL(triggered()), this, SLOT(actionMultiply()));

    cell_divAction = new QAction(tr("&Divide"), this);
    cell_divAction->setShortcut(Qt::CTRL | Qt::Key_division);
    connect(cell_divAction, SIGNAL(triggered()), this, SLOT(actionDivide()));

    fontAction = new QAction(tr("Font..."), this);
    fontAction->setShortcut(Qt::CTRL | Qt::Key_F);
    connect(fontAction, SIGNAL(triggered()), this, SLOT(selectFont()));

    colorAction = new QAction(QPixmap(16, 16), tr("Background &Color..."), this);
    connect(colorAction, SIGNAL(triggered()), this, SLOT(selectColor()));

    clearAction = new QAction(tr("Clear"), this);
    clearAction->setShortcut(Qt::Key_Delete);
    connect(clearAction, SIGNAL(triggered()), this, SLOT(clear()));

    exitAction = new QAction(tr("E&xit"), this);
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    printAction = new QAction(tr("&Print"), this);
    connect(printAction, SIGNAL(triggered()), this, SLOT(print()));

    firstSeparator = new QAction(this);
    firstSeparator -> setSeparator(true);

    secondSeparator = new QAction(this);
    secondSeparator -> setSeparator(true);
}

void PhysEqSolver::setupMenuBar() {
    /*
    QMenu *pFileMenu = menuBar() -> addMenu(tr("&File"));
    pFileMenu -> addAction(printAction);
    pFileMenu -> addAction(exitAction);

    QMenu *pCellMenu = menuBar() -> addMenu(tr("&Cell"));
    pCellMenu -> addAction(cell_addAction);
    pCellMenu -> addAction(cell_subAction);
    pCellMenu -> addAction(cell_mulAction);
    pCellMenu -> addAction(cell_divAction);
    pCellMenu -> addAction(cell_sumAction);
    pCellMenu -> addSeparator();
    pCellMenu -> addAction(colorAction);
    pCellMenu -> addAction(fontAction);
    */
}

void PhysEqSolver::updateStatus(QTableWidgetItem *pItem) {
    /*
    if (pItem && pItem == m_pTable -> currentItem()) {
        statusBar() -> showMessage(pItem -> data(Qt::StatusTipRole).toString(), 1000);
        cellLabel -> setText(tr("Cell: (%1)").arg(encode_pos(m_pTable -> row(pItem), m_pTable -> column(pItem))));
    }
    */
}

void PhysEqSolver::updateColor(QTableWidgetItem *pItem) {
    QPixmap pix(16, 16);
    QColor col;
    if (pItem)
        col = pItem -> backgroundColor();
    if (!col.isValid())
        col = palette().base().color();

    QPainter pt(&pix);
    pt.fillRect(0, 0, 16, 16, col);

    QColor lighter = col.light();
    pt.setPen(lighter);
    QPoint lightFrame[] = { QPoint(0, 15), QPoint(0, 0), QPoint(15, 0) };
    pt.drawPolyline(lightFrame, 3);

    pt.setPen(col.dark());
    QPoint darkFrame[] = { QPoint(1, 15), QPoint(15, 15), QPoint(15, 1) };
    pt.drawPolyline(darkFrame, 3);
    pt.end();
    colorAction -> setIcon(pix);
}

void PhysEqSolver::updateLineEdit(QTableWidgetItem *pItem) {
    if (pItem != m_pTable -> currentItem())
        return;
    if (pItem)
        m_pFormulaInput -> setText(pItem -> data(Qt::EditRole).toString());
    else
        m_pFormulaInput -> clear();
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

void PhysEqSolver::selectColor() {
    QTableWidgetItem *pItem = m_pTable -> currentItem();
    QColor col = pItem ? pItem -> backgroundColor() : m_pTable -> palette().base().color();
    col = QColorDialog::getColor(col, this);
    if (!col.isValid())
        return;

    QList<QTableWidgetItem *> selected = m_pTable -> selectedItems();
    if (selected.count() == 0)
        return;

    foreach (QTableWidgetItem *pItem, selected) {
        if (pItem)
            pItem -> setBackgroundColor(col);
    }
    updateColor(m_pTable -> currentItem());
}

void PhysEqSolver::selectFont() {
    QList<QTableWidgetItem*> selected = m_pTable -> selectedItems();
    if (selected.count() == 0)
        return;

    bool ok = false;
    QFont fnt = QFontDialog::getFont(&ok, font(), this);

    if (!ok)
        return;
    foreach (QTableWidgetItem *pItem, selected) {
        if (pItem)
            pItem -> setFont(fnt);
    }
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

void PhysEqSolver::actionSum() {
    int row_first = 0;
    int row_last = 0;
    int row_cur = 0;
    int col_first = 0;
    int col_last = 0;
    int col_cur = 0;

    QList<QTableWidgetItem*> selected = m_pTable->selectedItems();

    if (!selected.isEmpty()) {
        QTableWidgetItem *pFirst = selected.first();
        QTableWidgetItem *pLast = selected.last();
        row_first = m_pTable -> row(pFirst);
        row_last = m_pTable -> row(pLast);
        col_first = m_pTable -> column(pFirst);
        col_last = m_pTable -> column(pLast);
    }

    QTableWidgetItem *pCurrent = m_pTable -> currentItem();
    if (pCurrent) {
        row_cur = m_pTable -> row(pCurrent);
        col_cur = m_pTable -> column(pCurrent);
    }

    QString cell1 = encode_pos(row_first, col_first);
    QString cell2 = encode_pos(row_last, col_last);
    QString out = encode_pos(row_cur, col_cur);
    if (runInputDialog(tr("Sum cells"), tr("First cell:"), tr("Last cell:"),
                       QString("%1").arg(QChar(0x03a3)), tr("Output to:"), &cell1, &cell2, &out)) {
        int row;
        int col;
        decode_pos(out, &row, &col);
        m_pTable -> item(row, col) -> setText(tr("sum %1 %2").arg(cell1, cell2));
    }
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

void PhysEqSolver::actionAdd() {
    actionMath_helper(tr("Addition"), "+");
}

void PhysEqSolver::actionSubtract() {
    actionMath_helper(tr("Subtraction"), "-");
}

void PhysEqSolver::actionMultiply() {
    actionMath_helper(tr("Multiplication"), "*");
}
void PhysEqSolver::actionDivide() {
    actionMath_helper(tr("Division"), "/");
}

void PhysEqSolver::clear() {
    foreach (QTableWidgetItem *pItem, m_pTable -> selectedItems())
        pItem -> setText("");
}

void PhysEqSolver::setupContextMenu() {
    addAction(cell_addAction);
    addAction(cell_subAction);
    addAction(cell_mulAction);
    addAction(cell_divAction);
    addAction(cell_sumAction);
    addAction(firstSeparator);
    addAction(colorAction);
    addAction(fontAction);
    addAction(secondSeparator);
    addAction(clearAction);
    setContextMenuPolicy(Qt::ActionsContextMenu);
}

void PhysEqSolver::setupContents() {
    QColor titleBackground(Qt::lightGray);
    QFont titleFont = m_pTable -> font();
    titleFont.setBold(true);

    // column 0
    m_pTable -> setItem(0, 0, new PhysEqSolverItem("Item"));
    m_pTable -> item(0, 0) -> setBackgroundColor(titleBackground);
    m_pTable -> item(0, 0) -> setToolTip("This column shows the purchased item/service");
    m_pTable -> item(0, 0) -> setFont(titleFont);

    m_pTable -> setItem(1, 0, new PhysEqSolverItem("AirportBus"));
    m_pTable -> setItem(2, 0, new PhysEqSolverItem("Flight (Munich)"));
    m_pTable -> setItem(3, 0, new PhysEqSolverItem("Lunch"));
    m_pTable -> setItem(4, 0, new PhysEqSolverItem("Flight (LA)"));
    m_pTable -> setItem(5, 0, new PhysEqSolverItem("Taxi"));
    m_pTable -> setItem(6, 0, new PhysEqSolverItem("Dinner"));
    m_pTable -> setItem(7, 0, new PhysEqSolverItem("Hotel"));
    m_pTable -> setItem(8, 0, new PhysEqSolverItem("Flight (Oslo)"));
    m_pTable -> setItem(9, 0, new PhysEqSolverItem("Total:"));

    m_pTable -> item(9, 0) -> setFont(titleFont);
    m_pTable -> item(9, 0) -> setBackgroundColor(Qt::lightGray);

    // column 1
    m_pTable -> setItem(0, 1, new PhysEqSolverItem("Date"));
    m_pTable -> item(0, 1) -> setBackgroundColor(titleBackground);
    m_pTable -> item(0, 1) -> setToolTip("This column shows the purchase date, double click to change");
    m_pTable -> item(0, 1) -> setFont(titleFont);

    m_pTable -> setItem(1, 1, new PhysEqSolverItem("15/6/2006"));
    m_pTable -> setItem(2, 1, new PhysEqSolverItem("15/6/2006"));
    m_pTable -> setItem(3, 1, new PhysEqSolverItem("15/6/2006"));
    m_pTable -> setItem(4, 1, new PhysEqSolverItem("21/5/2006"));
    m_pTable -> setItem(5, 1, new PhysEqSolverItem("16/6/2006"));
    m_pTable -> setItem(6, 1, new PhysEqSolverItem("16/6/2006"));
    m_pTable -> setItem(7, 1, new PhysEqSolverItem("16/6/2006"));
    m_pTable -> setItem(8, 1, new PhysEqSolverItem("18/6/2006"));

    m_pTable -> setItem(9, 1, new PhysEqSolverItem());
    m_pTable -> item(9, 1) -> setBackgroundColor(Qt::lightGray);

    // column 2
    m_pTable -> setItem(0, 2, new PhysEqSolverItem("Price"));
    m_pTable -> item(0, 2) -> setBackgroundColor(titleBackground);
    m_pTable -> item(0, 2) -> setToolTip("This column shows the price of the purchase");
    m_pTable -> item(0, 2) -> setFont(titleFont);

    m_pTable -> setItem(1, 2, new PhysEqSolverItem("150"));
    m_pTable -> setItem(2, 2, new PhysEqSolverItem("2350"));
    m_pTable -> setItem(3, 2, new PhysEqSolverItem("-14"));
    m_pTable -> setItem(4, 2, new PhysEqSolverItem("980"));
    m_pTable -> setItem(5, 2, new PhysEqSolverItem("5"));
    m_pTable -> setItem(6, 2, new PhysEqSolverItem("120"));
    m_pTable -> setItem(7, 2, new PhysEqSolverItem("300"));
    m_pTable -> setItem(8, 2, new PhysEqSolverItem("1240"));

    m_pTable -> setItem(9, 2, new PhysEqSolverItem());
    m_pTable -> item(9, 2) -> setBackgroundColor(Qt::lightGray);

    // column 3
    m_pTable -> setItem(0, 3, new PhysEqSolverItem("Currency"));
    m_pTable -> item(0, 3)-> setBackgroundColor(titleBackground);
    m_pTable -> item(0, 3)-> setToolTip("This column shows the currency");
    m_pTable -> item(0, 3)-> setFont(titleFont);

    m_pTable -> setItem(1, 3, new PhysEqSolverItem("NOK"));
    m_pTable -> setItem(2, 3, new PhysEqSolverItem("NOK"));
    m_pTable -> setItem(3, 3, new PhysEqSolverItem("EUR"));
    m_pTable -> setItem(4, 3, new PhysEqSolverItem("EUR"));
    m_pTable -> setItem(5, 3, new PhysEqSolverItem("USD"));
    m_pTable -> setItem(6, 3, new PhysEqSolverItem("USD"));
    m_pTable -> setItem(7, 3, new PhysEqSolverItem("USD"));
    m_pTable -> setItem(8, 3, new PhysEqSolverItem("USD"));

    m_pTable -> setItem(9, 3, new PhysEqSolverItem());
    m_pTable -> item(9,3)->setBackgroundColor(Qt::lightGray);

    // column 4
    m_pTable -> setItem(0, 4, new PhysEqSolverItem("Ex. Rate"));
    m_pTable -> item(0, 4) -> setBackgroundColor(titleBackground);
    m_pTable -> item(0, 4) -> setToolTip("This column shows the exchange rate to NOK");
    m_pTable -> item(0, 4) -> setFont(titleFont);

    m_pTable -> setItem(1, 4, new PhysEqSolverItem("1"));
    m_pTable -> setItem(2, 4, new PhysEqSolverItem("1"));
    m_pTable -> setItem(3, 4, new PhysEqSolverItem("8"));
    m_pTable -> setItem(4, 4, new PhysEqSolverItem("8"));
    m_pTable -> setItem(5, 4, new PhysEqSolverItem("7"));
    m_pTable -> setItem(6, 4, new PhysEqSolverItem("7"));
    m_pTable -> setItem(7, 4, new PhysEqSolverItem("7"));
    m_pTable -> setItem(8, 4, new PhysEqSolverItem("7"));

    m_pTable -> setItem(9, 4, new PhysEqSolverItem());
    m_pTable -> item(9,4) -> setBackgroundColor(Qt::lightGray);

    // column 5
    m_pTable -> setItem(0, 5, new PhysEqSolverItem("NOK"));
    m_pTable -> item(0, 5) -> setBackgroundColor(titleBackground);
    m_pTable -> item(0, 5) -> setToolTip("This column shows the expenses in NOK");
    m_pTable -> item(0, 5) -> setFont(titleFont);

    m_pTable -> setItem(1, 5, new PhysEqSolverItem("* C2 E2"));
    m_pTable -> setItem(2, 5, new PhysEqSolverItem("* C3 E3"));
    m_pTable -> setItem(3, 5, new PhysEqSolverItem("* C4 E4"));
    m_pTable -> setItem(4, 5, new PhysEqSolverItem("* C5 E5"));
    m_pTable -> setItem(5, 5, new PhysEqSolverItem("* C6 E6"));
    m_pTable -> setItem(6, 5, new PhysEqSolverItem("* C7 E7"));
    m_pTable -> setItem(7, 5, new PhysEqSolverItem("* C8 E8"));
    m_pTable -> setItem(8, 5, new PhysEqSolverItem("* C9 E9"));
    m_pTable -> setItem(9, 5, new PhysEqSolverItem("sum F2 F9"));
    m_pTable -> item(9, 5) -> setBackgroundColor(Qt::lightGray);
}

const char *htmlText =
"<HTML>"
"<p><b>This demo shows use of <c>QTableWidget</c> with custom handling for"
" individual cells.</b></p>"
"<p>Using a customized table item we make it possible to have dynamic"
" output in different cells. The content that is implemented for this"
" particular demo is:"
"<ul>"
"<li>Adding two cells.</li>"
"<li>Subtracting one cell from another.</li>"
"<li>Multiplying two cells.</li>"
"<li>Dividing one cell with another.</li>"
"<li>Summing the contents of an arbitrary number of cells.</li>"
"</HTML>";

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

void PhysEqSolver::print() {
    /*
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrinter printer(QPrinter::ScreenResolution);
    QPrintPreviewDialog dlg(&printer);
    PhysPrintView view;
    view.setModel(table->model());
    connect(&dlg, SIGNAL(paintRequested(QPrinter*)), &view, SLOT(print(QPrinter*)));
    dlg.exec();
#endif
*/
}
