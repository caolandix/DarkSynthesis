#include <QTreeView>
#include <QGraphicsItem>

#include "physbaseitem.h"
#include "physobjectnavigator.h"

PhysObjectNavigator::PhysObjectNavigator(QWidget *pParent) : QTreeView(pParent) {
}

void PhysObjectNavigator::newPhysObj(QGraphicsItem *pObj) {
    if (pObj) {
        switch (pObj -> type()) {
            case PhysBaseItem::VectorType:
                break;
            case PhysBaseItem::ParticleType:
                break;
            case PhysBaseItem::CartesianGraphType:
                break;
            default:
                break;
       }
    }
}
