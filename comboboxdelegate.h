#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QItemDelegate>
#include <string>
#include <vector>

using namespace std;

class QModelIndex;
class QWidget;
class QVariant;

class ComboBoxDelegate : public QItemDelegate {
    Q_OBJECT
public:
    ComboBoxDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *, const QModelIndex &) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *, QAbstractItemModel *, const QModelIndex &) const Q_DECL_OVERRIDE;
    void updateEditorGeometry(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const Q_DECL_OVERRIDE;
    void paint(QPainter *, const QStyleOptionViewItem &, const QModelIndex &) const;

private:
    vector<string> m_Items;

};
#endif // COMBOBOXDELEGATE_H
