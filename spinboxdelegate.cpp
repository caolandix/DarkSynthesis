#include <QDoubleSpinBox>

#include "spinboxdelegate.h"

SpinBoxDelegate::SpinBoxDelegate(QObject *pParent) : QStyledItemDelegate(pParent) {
}

QWidget *SpinBoxDelegate::createEditor(QWidget *pParent, const QStyleOptionViewItem &styleOption, const QModelIndex &modelIndex) const {
    QDoubleSpinBox *pSpinBox = new QDoubleSpinBox(pParent);
    pSpinBox -> setFrame(false);
    pSpinBox -> setMinimum(0);
    pSpinBox -> setMaximum(100);
    return pSpinBox;
}

void SpinBoxDelegate::setEditorData(QWidget *pEditor, const QModelIndex &modelIndex) const {
    double value = modelIndex.model() -> data(modelIndex, Qt::EditRole).toInt();
    QDoubleSpinBox *pSpinBox = static_cast<QDoubleSpinBox *>(pEditor);

    pSpinBox -> setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &modelIndex) const {
    QDoubleSpinBox *pSpinBox = static_cast<QDoubleSpinBox *>(pEditor);
    pSpinBox -> interpretText();
    double value = pSpinBox -> value();

    pModel -> setData(modelIndex, value, Qt::EditRole);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *pEditor, const QStyleOptionViewItem &styleOption, const QModelIndex &modelIndex) const {
    pEditor -> setGeometry(styleOption.rect);
}

