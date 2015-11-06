#include <QtWidgets>

#include "physeqsolverdelegate.h"


PhysEqSolverDelegate::PhysEqSolverDelegate(QObject *pParent) : QItemDelegate(pParent) {}

QWidget *PhysEqSolverDelegate::createEditor(QWidget *pParent, const QStyleOptionViewItem &viewItem, const QModelIndex &index) const {
    if (index.column() == 1) {
        QDateTimeEdit *pDateEditor = new QDateTimeEdit(pParent);
        pDateEditor -> setDisplayFormat("dd/M/yyyy");
        pDateEditor -> setCalendarPopup(true);
        return pDateEditor;
    }

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

void PhysEqSolverDelegate::commitAndCloseEditor() {
    QLineEdit *pEdit = qobject_cast<QLineEdit *>(sender());
    emit commitData(pEdit);
    emit closeEditor(pEdit);
}

void PhysEqSolverDelegate::setEditorData(QWidget *pEditor, const QModelIndex &index) const {
    QLineEdit *pEdit = qobject_cast<QLineEdit*>(pEditor);
    if (pEdit) {
        pEdit -> setText(index.model() -> data(index, Qt::EditRole).toString());
        return;
    }

    QDateTimeEdit *pDateEditor = qobject_cast<QDateTimeEdit *>(pEditor);
    if (pDateEditor) {
        pDateEditor -> setDate(QDate::fromString(index.model() -> data(index, Qt::EditRole).toString(), "d/M/yyyy"));
    }
}

void PhysEqSolverDelegate::setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &index) const {
    QLineEdit *pEdit = qobject_cast<QLineEdit *>(pEditor);
    if (pEdit) {
        pModel -> setData(index, pEdit -> text());
        return;
    }

    QDateTimeEdit *pDateEditor = qobject_cast<QDateTimeEdit *>(pEditor);
    if (pDateEditor)
        pModel -> setData(index, pDateEditor -> date().toString("dd/M/yyyy"));
}
