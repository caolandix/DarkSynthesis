#include <QTreeView>
#include <QGraphicsItem>

#include "physbaseitem.h"
#include "physobjectnavigator.h"

PhysObjectNavigator::PhysObjectNavigator(QWidget *pParent) : QTreeView(pParent) {
}

void PhysObjectNavigator::onCreateObj(QGraphicsItem *pObj) {
    qDebug("PhysObjectNavigator::onCreateObj called");
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
