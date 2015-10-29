#include <QTableWidget>
#include <QGraphicsItem>

#include "physobjectpropsnavigator.h"
#include "physbaseitem.h"

PhysObjectPropsNavigator::PhysObjectPropsNavigator(QWidget *pParent) : QTableWidget(pParent) {

}

void PhysObjectPropsNavigator::onChangeObj(QGraphicsItem *pObj) {
    qDebug("PhysObjectPropsNavigator::onChangeObj()");

    switch (pObj -> type()) {
    case PhysBaseItem::VectorType:
        break;
    case PhysBaseItem::ParticleType:
        break;
    case PhysBaseItem::CartesianGraphType:
        buildPropertyTable(pObj);
        break;
    default:
        qDebug("PhysObjectPropsNavigator::onChangeObj(): not a valid Object type");
        break;
    }
}

void PhysObjectPropsNavigator::buildPropertyTable(QGraphicsItem *pObj) {

}


