#ifndef PHYSOBJECTPROPDELEGATE_H
#define PHYSOBJECTPROPDELEGATE_H

#include <QItemDelegate>

class PhysObjectPropDelegate : public QItemDelegate {
    Q_OBJECT
public:
    PhysObjectPropDelegate(QObject * = NULL);
    QWidget *createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *, const QModelIndex &) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *, QAbstractItemModel *, const QModelIndex &) const Q_DECL_OVERRIDE;

private slots:
    void commitAndCloseEditor();
};

#endif // PHYSOBJECTPROPDELEGATE_H
