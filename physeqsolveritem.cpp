#include "physeqsolveritem.h"

PhysEqSolverItem::PhysEqSolverItem() : QTableWidgetItem(), m_isResolving(false) {
}

PhysEqSolverItem::PhysEqSolverItem(const QString &text) : QTableWidgetItem(text), m_isResolving(false) {
}

QTableWidgetItem *PhysEqSolverItem::clone() const {
    PhysEqSolverItem *pItem = new PhysEqSolverItem();
    *pItem = *this;
    return pItem;
}

QVariant PhysEqSolverItem::data(int role) const {
    if (role == Qt::EditRole || role == Qt::StatusTipRole)
        return formula();
    if (role == Qt::DisplayRole)
        return display();

    QString str = display().toString();
    bool isNumber = false;
    int number = str.toInt(&isNumber);

    if (role == Qt::TextColorRole) {
        if (!isNumber)
            return QVariant::fromValue(QColor(Qt::black));
        else if (number < 0)
            return QVariant::fromValue(QColor(Qt::red));
        return QVariant::fromValue(QColor(Qt::blue));
    }
    if (role == Qt::TextAlignmentRole)
        if (!str.isEmpty() && (str.at(0).isNumber() || str.at(0) == '-'))
            return (int)(Qt::AlignRight | Qt::AlignVCenter);
     return QTableWidgetItem::data(role);
 }

void PhysEqSolverItem::setData(int role, const QVariant &value) {
    QTableWidgetItem::setData(role, value);
    if (tableWidget())
        tableWidget() ->viewport() ->update();
}

QVariant PhysEqSolverItem::display() const {

    // avoid circular dependencies
    if (m_isResolving)
        return QVariant();
    m_isResolving = true;
    QVariant result = computeFormula(formula(), tableWidget(), this);
    m_isResolving = false;
    return result;
}

/*
Rules for resolving sigfigs:
A. Read from the left and start counting sig figs when you encounter the first non-zero digit
    1. All non zero numbers are  significant  (meaning they count as sig figs)
                          613 has three sig figs
                          123456 has six sig figs
    2. Zeros located between non-zero digits are  significant  (they count)
                          5004 has four sig figs
                          602 has three sig figs
                          6000000000000002 has 16 sig figs!
    3. Trailing zeros (those at the end) are significant  only if the number contains a decimal point; otherwise
        they are insignificant (they  don’t  count)
                          5.640 has four sig figs
                          120000. has six sig figs
                          120000 has two sig figs – unless you’re given additional information in the problem
    4. Zeros to left of the first nonzero digit are  insignificant (they don’t count); they are only placeholders!
                          0.000456 has three sig figs
                          0.052 has two sig figs
                          0.000000000000000000000000000000000052 also has two sig figs!
B. Rules for addition/subtraction problems
    Your calculated value cannot be more precise than the least precise quantity used in the calculation. The
    least precise quantity has the fewest digits to the right of the decimal point. Your calculated value will
    have the same number of digits to the right of the  decimal point as that of the least precise quantity. In
    practice, find the quantity with the fewest digits to the right of the decimal point. In the example below,
    this would be 11.1 (this is the least precise quantity).
        7.939 + 6.26 + 11.1 = 25.299 (this is what your calculator spits out)
    In this case, your final answer is limited to one sig fig to the right of the decimal or 25.3 (rounded up).
C. Rules for multiplication/division problems
    The number of sig figs in the final calculated value will be the same as that of the quantity
    with the fewest number of sig figs used in the calculation.
    In practice, find the quantity with the fewest number of sig figs. In the example below, the
    quantity with the fewest number of sig figs is 27.2 (three sig figs). Your final answer is therefore
    limited to three sig figs.
        (27.2 x 15.63) ÷ 1.846 = 230.3011918 (this is what you calculator spits out)
    In this case, since your final answer it limited to three sig figs, the answer is 230. (rounded down)
D. Rules for combined addition/subtraction and multiplication/division problems
    Use the order of mathematical operations to determine which order to apply the rules for addition/subtraction
    (determine the number of sig figs for that step) or the rules for multiplication/division.
        (23 + 7) ÷ 10.0 =  3 (this is what your calculator spits out)
    In this case, your answer should have 2 significant figures, 3.0.
*/
QVariant PhysEqSolverItem::resolveSigFigs(const QVariant &calcResult) {
    QVariant result;

    return result;
}

QVariant PhysEqSolverItem::computeFormula(const QString &formula, const QTableWidget *pWidget, const QTableWidgetItem *self) {

    // check if the s tring is actually a formula or not
    QStringList list = formula.split(' ');
    if (list.isEmpty() || !pWidget)
        return formula; // it is a normal string

    QString op = list.value(0).toLower();

    int firstRow = -1;
    int firstCol = -1;
    int secondRow = -1;
    int secondCol = -1;

    if (list.count() > 1)
        decode_pos(list.value(1), &firstRow, &firstCol);

    if (list.count() > 2)
        decode_pos(list.value(2), &secondRow, &secondCol);

    const QTableWidgetItem *pStart = pWidget ->item(firstRow, firstCol);
    const QTableWidgetItem *pEnd = pWidget ->item(secondRow, secondCol);

    int firstVal = pStart ? pStart ->text().toInt() : 0;
    int secondVal = pEnd ? pEnd ->text().toInt() : 0;

    QVariant result;
    if (op == "sum") {
        int sum = 0;
        for (int row = firstRow; row <= secondRow; ++row) {
            for (int col = firstCol; col <= secondCol; ++col) {
                const QTableWidgetItem *tableItem = pWidget ->item(row, col);
                if (tableItem && tableItem != self)
                    sum += tableItem ->text().toInt();
            }
        }

        result = sum;
    }
    else if (op == "+")
        result = (firstVal + secondVal);
    else if (op == "-")
        result = (firstVal - secondVal);
    else if (op == "*")
        result = (firstVal * secondVal);
    else if (op == "/") {
        if (secondVal == 0)
            result = QString("Not a Number");
        else
            result = (firstVal / secondVal);
    }
    else if (op == "=") {
        if (pStart)
            result = pStart->text();
    }
    else
        result = formula;
    return result;
}
