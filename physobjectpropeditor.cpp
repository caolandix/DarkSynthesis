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
    qDebug("PhysObjectPropEditor::data(), role: %d", role);
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

void PhysObjectPropEditor::setData(int role, const QVariant &value) {
    QString str = value.toString();
    qDebug("PhysObjectPropEditor::setData(), role: %d, value: %s", role, qPrintable(value.toString()));
    QTableWidgetItem::setData(role, value);
    if (tableWidget())
        tableWidget() -> viewport() ->update();
}

QVariant PhysObjectPropEditor::display() const {
    qDebug("PhysObjectPropEditor::display()");
    // avoid circular dependencies
    if (m_isResolving)
        return QVariant();
    m_isResolving = true;
    QVariant result = formula();
    m_isResolving = false;
    return result;
}
