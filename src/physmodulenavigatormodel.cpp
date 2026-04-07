#include "physmodulenavigatormodel.h"

PhysModuleNavigatorModel::PhysModuleNavigatorModel(QObject *parent) : QAbstractListModel(parent) {
    // PHYS-221
    m_ModuleList.push_back(new PhysModule("1D Kinematics"));
    m_ModuleList.push_back(new PhysModule("2D Kinematics"));
    m_ModuleList.push_back(new PhysModule("Force and Motion"));
    m_ModuleList.push_back(new PhysModule("Dynamics I: Motion Along a Line"));
    m_ModuleList.push_back(new PhysModule("Newton's Third Law"));
    m_ModuleList.push_back(new PhysModule("Dynamics II: Motion in a Plane"));
    m_ModuleList.push_back(new PhysModule("Impulse and Momentum"));
    m_ModuleList.push_back(new PhysModule("Energy"));
    m_ModuleList.push_back(new PhysModule("Work"));
    m_ModuleList.push_back(new PhysModule("Rotation of a Rigid Body"));

    // PHYS-222
    m_ModuleList.push_back(new PhysModule("Electric Charges and Forces"));
    m_ModuleList.push_back(new PhysModule("The Electric Field"));
    m_ModuleList.push_back(new PhysModule("Gauss's Law"));
    m_ModuleList.push_back(new PhysModule("Current and Conductivity"));
    m_ModuleList.push_back(new PhysModule("The Electric Potential"));
    m_ModuleList.push_back(new PhysModule("Potential and Field"));
    m_ModuleList.push_back(new PhysModule("Fundamentals of Circuits"));
    m_ModuleList.push_back(new PhysModule("The Magnetic Field"));
    m_ModuleList.push_back(new PhysModule("Electromagnetic Induction"));
    m_ModuleList.push_back(new PhysModule("Electromagnetic Fields and Waves"));
    m_ModuleList.push_back(new PhysModule("AC Circuits"));

    // PHYS-223
    m_ModuleList.push_back(new PhysModule("Newton's Theory of Gravity"));
    m_ModuleList.push_back(new PhysModule("Oscillations"));
    m_ModuleList.push_back(new PhysModule("Fluids and Elasticity"));
    m_ModuleList.push_back(new PhysModule("A Macroscopic Description of Matter"));
    m_ModuleList.push_back(new PhysModule("Work, Heat, and the First Law of Thermodynamics"));
    m_ModuleList.push_back(new PhysModule("The Micro/Macro Connection"));
    m_ModuleList.push_back(new PhysModule("Heat Engines and Refrigerators"));
    m_ModuleList.push_back(new PhysModule("Traveling Waves"));
    m_ModuleList.push_back(new PhysModule("Superposition"));
    m_ModuleList.push_back(new PhysModule("Wave Optics"));
    m_ModuleList.push_back(new PhysModule("Ray Optics"));
    m_ModuleList.push_back(new PhysModule("Modern Optics and Matter Waves"));

    // Advanced
    m_ModuleList.push_back(new PhysModule("Relativity"));
    m_ModuleList.push_back(new PhysModule("The End of Classical Physics"));
    m_ModuleList.push_back(new PhysModule("Quantization"));
    m_ModuleList.push_back(new PhysModule("Wave Functions and Probabilities"));
    m_ModuleList.push_back(new PhysModule("One-Dimensional Quantum Mechanics"));
    m_ModuleList.push_back(new PhysModule("Atomic Physics"));
    m_ModuleList.push_back(new PhysModule("Nuclear Physics"));
    m_ModuleList.push_back(new PhysModule("Electromagnetism"));
    m_ModuleList.push_back(new PhysModule("Magnetohydrodynamics"));
    m_ModuleList.push_back(new PhysModule("1D Electrostatics"));
    m_ModuleList.push_back(new PhysModule("Intro to Plasma Physics"));
    foreach(PhysModule *pObj, m_ModuleList)
        stringList << pObj ->Name();
}

int PhysModuleNavigatorModel::rowCount(const QModelIndex &parent) const {
    return stringList.count();
}

QVariant PhysModuleNavigatorModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    if (index.row() >= stringList.size())
        return QVariant();
    if (role == Qt::DisplayRole)
        return stringList.at(index.row());
    else
        return QVariant();
}

QVariant PhysModuleNavigatorModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

Qt::ItemFlags PhysModuleNavigatorModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index);
}

bool PhysModuleNavigatorModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        stringList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool PhysModuleNavigatorModel::insertRows(int position, int rows, const QModelIndex &parent) {
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; ++row)
        stringList.insert(position, "");
    endInsertRows();
    return true;
}

bool PhysModuleNavigatorModel::removeRows(int position, int rows, const QModelIndex &parent) {
    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; ++row)
        stringList.removeAt(position);
    endRemoveRows();
    return true;
}
