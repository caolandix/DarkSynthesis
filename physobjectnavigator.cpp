#include <QTreeView>
#include <QGraphicsItem>

#include "physbaseitem.h"
#include "physobjectnavigator.h"

PhysObjectNavigator::PhysObjectNavigator(QWidget *pParent) : QTreeView(pParent) {
}

void PhysObjectNavigator::onCreateObj(QGraphicsItem *pObj) {
    qDebug("PhysObjectNavigator::onCreateObj called");
    if (pObj) {
        int type = pObj -> type();
        switch (type) {
            case PhysBaseItem::VectorType:
                qDebug("PhysObjectNavigator::onCreateObj called, VectorType");
                break;
            case PhysBaseItem::ParticleType:
                qDebug("PhysObjectNavigator::onCreateObj called, ParticleType");
                break;
            case PhysBaseItem::CartesianGraphType:
                qDebug("PhysObjectNavigator::onCreateObj called, CartesianGraphType");
                break;
            default:
                break;
       }
    }
}
