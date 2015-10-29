#include <QTreeWidget>
#include <QGraphicsItem>
#include <QTreeWidgetItem>

#include "physbaseitem.h"
#include "physobjectnavigator.h"
#include "cartesiangraph.h"
#include "physvector.h"
#include "physparticle.h"

PhysObjectNavigator::PhysObjectNavigator(QWidget *pParent) : QTreeWidget(pParent) {
    setColumnCount(2);
    setRootIsDecorated(true);

    QStringList colLabels;
    colLabels.push_back("PhysObject Name");
    colLabels.push_back("PhysObject Type");
    setHeaderLabels(colLabels);
}

void PhysObjectNavigator::onCreateObj(QGraphicsItem *pObj) {
    if (pObj) {
        switch (pObj -> type()) {
            case PhysBaseItem::VectorType:
                insertVector(static_cast<PhysVector *>(pObj));
                break;
            case PhysBaseItem::ParticleType:
                insertParticle(static_cast<PhysParticle *>(pObj));
                break;
            case PhysBaseItem::CartesianGraphType:
                insertCartesianGraph(static_cast<CartesianGraph *>(pObj));
                break;
            default:
                qDebug("PhysObjectNavigator::onCreateObj: not a supported object type: %d", pObj -> type());
                break;
       }
    }
}

void PhysObjectNavigator::insertVector(PhysVector *pObj) {
}

void PhysObjectNavigator::insertParticle(PhysParticle *pObj) {
}

void PhysObjectNavigator::insertCartesianGraph(CartesianGraph *pObj) {
    QTreeWidgetItem *pTopLevelItem = topLevelItem(0);

    if (!pTopLevelItem) {
        pTopLevelItem = new QTreeWidgetItem(this);
        pTopLevelItem -> setText(0, pObj -> Name());
        pTopLevelItem -> setText(1, pObj -> TypeName(pObj -> type()));
        addTopLevelItem(pTopLevelItem);
        setCurrentItem(pTopLevelItem);
        emit changeObj(pObj);
    }

    // Top level item exists so delete the current and rebuild
    else {
        removeItemWidget(pTopLevelItem, 0);
    }
}
