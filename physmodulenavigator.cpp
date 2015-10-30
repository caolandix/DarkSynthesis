#include "physmodulenavigator.h"

PhysModuleNavigator::PhysModuleNavigator(QWidget *pParent) : QListWidget(pParent) {
    m_ModuleList.push_back(new PhysModule("Kinematics in One Dimension"));
    m_ModuleList.push_back(new PhysModule("Kinematics in Two Dimensions"));
    m_ModuleList.push_back(new PhysModule("Force and Motion"));
    m_ModuleList.push_back(new PhysModule("Dynamics I: Motion Along a Line"));
    m_ModuleList.push_back(new PhysModule("Newton's Third Law"));
    m_ModuleList.push_back(new PhysModule("Dynamics II: Motion in a Plane"));
    m_ModuleList.push_back(new PhysModule("Impulse and Momentum"));
    m_ModuleList.push_back(new PhysModule("Energy"));
    m_ModuleList.push_back(new PhysModule("Work"));
    m_ModuleList.push_back(new PhysModule("Rotation of a Rigid Body"));

    for (int i = 0; i < m_ModuleList.count(); i++) {
        PhysModule *pObj = m_ModuleList[i];
        QListWidgetItem *pItem = new QListWidgetItem(pObj -> Name(), this);
        insertItem(i, pItem);
    }
}

