#ifndef PHYSEQSOLVERITEM_H
#define PHYSEQSOLVERITEM_H

#include <QTableWidgetItem>

class PhysEqSolverItem : public QTableWidgetItem {
public:
    PhysEqSolverItem();
    PhysEqSolverItem(const QString &);

    QTableWidgetItem *clone() const Q_DECL_OVERRIDE;
    QVariant data(int) const Q_DECL_OVERRIDE;
    void setData(int, const QVariant &) Q_DECL_OVERRIDE;
    QVariant display() const;

    inline QString formula() const  { return QTableWidgetItem::data(Qt::DisplayRole).toString(); }
    static QVariant computeFormula(const QString &, const QTableWidget *, const QTableWidgetItem * = NULL);
    QVariant resolveSigFigs(const QVariant &);
private:
    mutable bool m_isResolving;
};

#endif // PHYSEQSOLVERITEM_H
