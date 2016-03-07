#ifndef PHYSOBJECTNAVIGATORMODEL_H
#define PHYSOBJECTNAVIGATORMODEL_H

#include <QAbstractItemModel>
#include "treeitem.h"

class PhysObjectNavigatorModel : public QAbstractItemModel {
    Q_OBJECT
public:
    explicit PhysObjectNavigatorModel(QObject *parent = NULL);
    ~PhysObjectNavigatorModel();

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

private:
    void setupModelData(const QStringList &lines, TreeItem *parent);
    TreeItem *rootItem;
};

#endif // PHYSOBJECTNAVIGATORMODEL_H
