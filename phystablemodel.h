#ifndef PHYSTABLEMODEL_H
#define PHYSTABLEMODEL_H

#include <QAbstractTableModel>

class PhysTableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit PhysTableModel(QObject *parent = 0);

    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

public slots:
    void addColumn();

private:
    int m_columns;
};

#endif // PHYSTABLEMODEL_H
