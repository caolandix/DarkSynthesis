#include <QtWidgets>
#include "phystablemodel.h"

PhysTableModel::PhysTableModel(QObject *parent) : QAbstractTableModel(parent), m_columns(1) {

}

int PhysTableModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return m_columns;
}

int PhysTableModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return 10;
}

QVariant PhysTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();
    if (role != Qt::DisplayRole) return QVariant();

    return QString().sprintf("r%04d/c%04d", index.row(), index.column());
}

void PhysTableModel::addColumn() {
    const int newColumnIndex = m_columns;
    beginInsertColumns(QModelIndex(), newColumnIndex, newColumnIndex);
    m_columns++;
    endInsertColumns();
}

