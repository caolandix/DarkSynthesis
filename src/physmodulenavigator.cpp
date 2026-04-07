#include "physmodulenavigator.h"

PhysModuleNavigator::PhysModuleNavigator(QWidget *pParent) : QListView(pParent), PhysCommon() {
    ModType(SINGLEDIM_KINEMATICS);

    QAbstractItemModel *pModel = this ->model();
}

PhysModuleNavigator::~PhysModuleNavigator() {
}

