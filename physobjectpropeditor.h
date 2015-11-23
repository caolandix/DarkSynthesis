#ifndef PHYSOBJECTPROPEDITOR_H
#define PHYSOBJECTPROPEDITOR_H

#include <QTableWidgetItem>

class PhysObjectPropEditor : public QTableWidgetItem {
public:
    PhysObjectPropEditor();
    PhysObjectPropEditor(const QString &);

    QTableWidgetItem *clone() const Q_DECL_OVERRIDE;
    QVariant data(int) const Q_DECL_OVERRIDE;
    void setData(int, const QVariant &) Q_DECL_OVERRIDE;
    QVariant display() const ;

    QString formula() const { return QTableWidgetItem::data(Qt::DisplayRole).toString(); }
private:
    mutable bool m_isResolving;
};

#endif // PHYSOBJECTPROPEDITOR_H
