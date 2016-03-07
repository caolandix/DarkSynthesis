#include "physmodulenavigator.h"

PhysModuleNavigator::PhysModuleNavigator(QWidget *pParent) : QListView(pParent), PhysCommon() {
    ModType(SINGLEDIM_KINEMATICS);
}

PhysModuleNavigator::~PhysModuleNavigator() {
}

