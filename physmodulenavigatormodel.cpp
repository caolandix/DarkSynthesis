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

    for (int i = 0; i < m_ModuleList.count(); i++) {
        PhysModule *pObj = m_ModuleList[i];
        QListWidgetItem *pItem = new QListWidgetItem(pObj -> Name(), this);
        insertItem(i, pItem);
    }
    setCurrentIndex(model()->index(0, 0));
    ModType(SINGLEDIM_KINEMATICS);

}

QVariant PhysModuleNavigatorModel::headerData(int section, Qt::Orientation orientation, int role) const {
    // FIXME: Implement me!
}

int PhysModuleNavigatorModel::rowCount(const QModelIndex &parent) const {
    if (!parent.isValid())
        return 0;
    return m_ModuleList.count();
}

QVariant PhysModuleNavigatorModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        return stringList.at(index.row());
    return QVariant();
}
