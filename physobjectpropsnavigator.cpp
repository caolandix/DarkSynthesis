#include <QTableWidget>
#include <QGraphicsItem>
#include <QHeaderView>

#include "physobjectpropsnavigator.h"
#include "physbaseitem.h"

PhysObjectPropsNavigator::PhysObjectPropsNavigator(QWidget *pParent) : QTableWidget(pParent) {
    setShowGrid(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setColumnCount(2);
    QStringList tableHeader;

    tableHeader << "Property" << "Value";
    setHorizontalHeaderLabels(tableHeader);
    verticalHeader()->setVisible(false);
}

void PhysObjectPropsNavigator::onChangeObj(QGraphicsItem *pObj) {
    qDebug("PhysObjectPropsNavigator::onChangeObj()");

    switch (pObj -> type()) {
    case PhysBaseItem::VectorType:
        buildVectorTable(pObj);
        break;
    case PhysBaseItem::ParticleType:
        buildParticleTable(pObj);
        break;
    case PhysBaseItem::CartesianGraphType:
        buildCartesianGraphTable(pObj);
        break;
    default:
        qDebug("PhysObjectPropsNavigator::onChangeObj(): not a valid Object type");
        break;
    }
}

void PhysObjectPropsNavigator::buildCartesianGraphTable(QGraphicsItem *pObj) {
    qDebug("PhysObjectPropsNavigator::buildCartesianGraphTable()");
}

void PhysObjectPropsNavigator::buildVectorTable(QGraphicsItem *pObj) {
    qDebug("PhysObjectPropsNavigator::buildVectorTable()");
}

void PhysObjectPropsNavigator::buildParticleTable(QGraphicsItem *pObj) {
    qDebug("PhysObjectPropsNavigator::buildParticleTable()");
}


