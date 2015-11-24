#ifndef PHYSCTRLDOUBLESPINBOXDELEGATE_H
#define PHYSCTRLDOUBLESPINBOXDELEGATE_H

#include <QStyledItemDelegate>

class PhysCtrlDoubleSpinBoxDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    PhysCtrlDoubleSpinBoxDelegate(const int = 6, QObject * = 0);

    QWidget *createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *, const QModelIndex &) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *, QAbstractItemModel *, const QModelIndex &) const Q_DECL_OVERRIDE;
    void updateEditorGeometry(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const Q_DECL_OVERRIDE;
private:
    int m_precision;
};

#endif // PHYSCTRLDOUBLESPINBOXDELEGATE_H
