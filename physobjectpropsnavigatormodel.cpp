#include "physobjectpropsnavigatormodel.h"

PhysObjectPropsNavigatorModel::PhysObjectPropsNavigatorModel(QObject *parent) : QAbstractTableModel(parent) {
    std::vector<float> column1;
    column1.push_back(10);
    column1.push_back(20);
    column1.push_back(30);
    column1.push_back(40);

    Columns.push_back(column1);

    std::vector<float> column2;
    column2.push_back(50);
    column2.push_back(60);
    column2.push_back(70);
    column2.push_back(80);

    Columns.push_back(column2);
}

QVariant PhysObjectPropsNavigatorModel::headerData(int section, Qt::Orientation orientation, int role) const {

    if(role == Qt::DisplayRole) {
      std::string ss;
      if(orientation == Qt::Horizontal) {
        // ss << "H_" << section;
        return QString("H_");
        }
      else if(orientation == Qt::Vertical)
        {
        // ss << "V_" << section;
        return QString("V_");
        }

      }

    return QVariant::Invalid;
}

int PhysObjectPropsNavigatorModel::rowCount(const QModelIndex &parent) const {
    if (!parent.isValid())
        return 0;
  return Columns[0].size();
}

int PhysObjectPropsNavigatorModel::columnCount(const QModelIndex &parent) const {
    if (!parent.isValid())
        return 0;
  return Columns.size();
}

QVariant PhysObjectPropsNavigatorModel::data(const QModelIndex &index, int role) const {
    if(role == Qt::DisplayRole)
      {
      return Columns[index.column()][index.row()];
      }
    return QVariant::Invalid;
}
