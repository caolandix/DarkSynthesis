#include <QtWidgets>
#include "physctrldoublespinboxdelegate.h"

PhysCtrlDoubleSpinBoxDelegate::PhysCtrlDoubleSpinBoxDelegate(const int precision, QObject *parent) : QStyledItemDelegate(parent) {
    m_precision = precision;
}

QWidget *PhysCtrlDoubleSpinBoxDelegate::createEditor(QWidget *pParent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QDoubleSpinBox *pEditor = new QDoubleSpinBox(pParent);
    pEditor -> setDecimals(m_precision);
    pEditor -> setFrame(false);
    pEditor -> setMinimum(0);
    pEditor -> setMaximum(100);
    return pEditor;
}

void PhysCtrlDoubleSpinBoxDelegate::setEditorData(QWidget *pEditor, const QModelIndex &index) const {
    double value = index.model() -> data(index, Qt::EditRole).toDouble();
    QDoubleSpinBox *pSpinBox = static_cast<QDoubleSpinBox *>(pEditor);
    pSpinBox -> setValue(value);
}

void PhysCtrlDoubleSpinBoxDelegate::setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &index) const {
    QDoubleSpinBox *pSpinBox = static_cast<QDoubleSpinBox *>(pEditor);
    pSpinBox -> interpretText();
    double value = pSpinBox -> value();
    pModel -> setData(index, value, Qt::EditRole);
}

void PhysCtrlDoubleSpinBoxDelegate::updateEditorGeometry(QWidget *pEditor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    pEditor -> setGeometry(option.rect);
}
