#include "physobjectpropeditor.h"

PhysObjectPropEditor::PhysObjectPropEditor() : QTableWidgetItem(), m_isResolving(false) {
}

PhysObjectPropEditor::PhysObjectPropEditor(const QString &text) : QTableWidgetItem(text), m_isResolving(false) {
}

QTableWidgetItem *PhysObjectPropEditor::clone() const {
    PhysObjectPropEditor *pItem = new PhysObjectPropEditor();
    *pItem = *this;
    return pItem;
}

QVariant PhysObjectPropEditor::data(int role) const {
    if (role == Qt::EditRole || role == Qt::StatusTipRole)
        return formula();
    if (role == Qt::DisplayRole)
        return display();

    QString t = display().toString();
    bool isNumber = false;
    int number = t.toInt(&isNumber);

    if (role == Qt::TextColorRole) {
        if (!isNumber)
            return QVariant::fromValue(QColor(Qt::black));
        else if (number < 0)
            return QVariant::fromValue(QColor(Qt::red));
        return QVariant::fromValue(QColor(Qt::blue));
    }
    if (role == Qt::TextAlignmentRole)
        if (!t.isEmpty() && (t.at(0).isNumber() || t.at(0) == '-'))
            return (int)(Qt::AlignRight | Qt::AlignVCenter);
     return QTableWidgetItem::data(role);
 }

void PhysObjectPropEditor::setData(int role, const QVariant &value) {
    QTableWidgetItem::setData(role, value);
    if (tableWidget())
        tableWidget() ->viewport() ->update();
}

QVariant PhysObjectPropEditor::display() const {

    // avoid circular dependencies
    if (m_isResolving)
        return QVariant();
    m_isResolving = true;
    QVariant result;// = computeFormula(formula(), tableWidget(), this);
    m_isResolving = false;
    return result;
}
