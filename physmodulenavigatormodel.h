#ifndef PHYSMODULENAVIGATORMODEL_H
#define PHYSMODULENAVIGATORMODEL_H

#include <QAbstractListModel>

class PhysModuleNavigatorModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit PhysModuleNavigatorModel(QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QList<PhysModule *> m_ModuleList;
};

#endif // PHYSMODULENAVIGATORMODEL_H
