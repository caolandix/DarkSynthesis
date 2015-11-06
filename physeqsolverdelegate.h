#ifndef PHYSEQSOLVERDELEGATE_H
#define PHYSEQSOLVERDELEGATE_H

#include <QItemDelegate>
#include "physeqsolver.h"

class PhysEqSolverDelegate : public QItemDelegate {
    Q_OBJECT
public:
    PhysEqSolverDelegate(QObject * = NULL);
    QWidget *createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *, const QModelIndex &) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *, QAbstractItemModel *, const QModelIndex &) const Q_DECL_OVERRIDE;

private slots:
    void commitAndCloseEditor();
};

#endif // PHYSEQSOLVERDELEGATE_H
