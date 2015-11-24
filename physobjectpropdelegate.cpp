#include <QtWidgets>
#include "physobjectpropdelegate.h"

PhysObjectPropDelegate::PhysObjectPropDelegate(QObject *pParent) : QStyledItemDelegate(pParent) {}

QWidget *PhysObjectPropDelegate::createEditor(QWidget *pParent, const QStyleOptionViewItem &viewItem, const QModelIndex &index) const {
    QLineEdit *pEdit = new QLineEdit(pParent);

    // create a completer with the strings in the column as model
    QStringList allStrings;
    for (int i = 1; i < index.model() -> rowCount(); i++) {
        QString strItem(index.model() -> data(index.sibling(i, index.column()), Qt::EditRole).toString());
        if (!allStrings.contains(strItem))
            allStrings.append(strItem);
    }
    QCompleter *pAutoComplete = new QCompleter(allStrings);
    pEdit -> setCompleter(pAutoComplete);
    connect(pEdit, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
    return pEdit;
}

void PhysObjectPropDelegate::commitAndCloseEditor() {
    QLineEdit *pEdit = qobject_cast<QLineEdit *>(sender());
    emit commitData(pEdit);
    emit closeEditor(pEdit);
}

void PhysObjectPropDelegate::setEditorData(QWidget *pEditor, const QModelIndex &index) const {
    QLineEdit *pEdit = qobject_cast<QLineEdit*>(pEditor);
    if (pEdit) {
        pEdit -> setText(index.model() -> data(index, Qt::EditRole).toString());
        return;
    }
}

void PhysObjectPropDelegate::setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &index) const {
    QLineEdit *pEdit = qobject_cast<QLineEdit *>(pEditor);
    if (pEdit) {
        pModel -> setData(index, pEdit -> text());
        return;
    }
}
