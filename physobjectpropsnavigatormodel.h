#ifndef PHYSOBJECTPROPSNAVIGATORMODEL_H
#define PHYSOBJECTPROPSNAVIGATORMODEL_H

#include <QAbstractTableModel>

class PhysObjectPropsNavigatorModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit PhysObjectPropsNavigatorModel(QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
      std::vector<std::vector<float> > Columns;
};

#endif // PHYSOBJECTPROPSNAVIGATORMODEL_H
