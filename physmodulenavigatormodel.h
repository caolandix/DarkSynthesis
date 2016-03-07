#ifndef PHYSMODULENAVIGATORMODEL_H
#define PHYSMODULENAVIGATORMODEL_H
#include <QAbstractListModel>
#include <QObject>
#include <QStringList>

#include "physmodule.h"

class PhysModuleNavigatorModel : public QAbstractListModel {
    Q_OBJECT
public:
    PhysModuleNavigatorModel(QObject *parent = NULL);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
private:
    QStringList stringList;
    QList<PhysModule *> m_ModuleList;
};

#endif // PHYSMODULENAVIGATORMODEL_H
