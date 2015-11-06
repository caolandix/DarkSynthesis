#include <QTreeWidget>
#include <QGraphicsItem>
#include <QItemSelection>
#include <QTreeWidgetItem>


#include "physbaseitem.h"
#include "physobjectnavigator.h"
#include "cartesiangraph.h"
#include "physvector.h"
#include "physparticle.h"

PhysObjectNavigator::PhysObjectNavigator(QWidget *pParent) : QTreeWidget(pParent) {
    setColumnCount(2);
    setRootIsDecorated(true);
    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::InternalMove);

    QStringList colLabels;
    colLabels << "PhysObject Name" << "PhysObject Type";
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

void PhysObjectNavigator::currentChanged(const QModelIndex &current, const QModelIndex &previous) {
    qDebug("PhysObjectNavigator::currentChanged");
    QVariant varCurrent = current.data(Qt::UserRole);
    QVariant varPrev = previous.data(Qt::UserRole);

    QGraphicsItem *pCurrObj = qvariant_cast<QGraphicsItem *>(varCurrent);
    QGraphicsItem *pPrevObj = qvariant_cast<QGraphicsItem *>(varPrev);

    // Changing the currentitem
    // If we're brand new then there is no pPrevObj
    if (!pPrevObj)
        emit changeObj(pCurrObj);
    else {
        if (pPrevObj ->type() != pCurrObj ->type())
            emit changeObj(pCurrObj);
        else
            emit updateObj(pCurrObj);
    }
}

void PhysObjectNavigator::dropEvent(QDropEvent *pEvent) {
    QModelIndex dropIndex = indexAt(pEvent -> pos());

    // The object must have a parent to be dropped
    if (dropIndex.parent().isValid()) {
        QTreeWidget::dropEvent(pEvent);
    }
}

void PhysObjectNavigator::insertVector(PhysVector *pObj) {
    QTreeWidgetItem *pParentItem = topLevelItem(0);

    if (pParentItem) {
        QTreeWidgetItem *pChildItem = NULL;
        if (!pObj -> StartParticle() && !pObj -> EndParticle())
            pChildItem = new QTreeWidgetItem(pParentItem);
        else {
            QString strParticle = (pObj -> StartParticle()) ?
                        pObj -> StartParticle() -> Name() :
                        pObj -> EndParticle() -> Name();
            QList<QTreeWidgetItem *> itemList = findItems(strParticle, Qt::MatchExactly);
            if (itemList.count() > 0) {
                pParentItem = itemList.at(0);
                pChildItem = new QTreeWidgetItem(pParentItem);
            }
        }
        if (pChildItem) {
            QString str = pObj -> Name();
            pChildItem ->setFlags(Qt::ItemIsDragEnabled);
            pChildItem -> setText(0, pObj -> Name());
            pChildItem -> setText(1, pObj -> TypeName(pObj -> type()));

            QVariant var;
            var.setValue(pObj);
            pChildItem -> setData(0, Qt::UserRole, var);

            pParentItem -> addChild(pChildItem);
            setCurrentItem(pChildItem);
            emit changeObj(pObj);
        }
    }
}

void PhysObjectNavigator::insertParticle(PhysParticle *pObj) {
    QTreeWidgetItem *pTopLevelItem = topLevelItem(0);

    if (pTopLevelItem) {
        QTreeWidgetItem *pChildItem = new QTreeWidgetItem(pTopLevelItem);
        QString str = pObj -> Name();
        pChildItem ->setFlags(Qt::ItemIsDragEnabled);
        pChildItem -> setText(0, pObj -> Name());
        pChildItem -> setText(1, pObj -> TypeName(pObj -> type()));
        pTopLevelItem -> addChild(pChildItem);
        setCurrentItem(pChildItem);
        emit changeObj(pObj);
    }
}

void PhysObjectNavigator::insertCartesianGraph(CartesianGraph *pObj) {
    QTreeWidgetItem *pTopLevelItem = topLevelItem(0);

    if (pTopLevelItem)
        removeItemWidget(pTopLevelItem, 0);
    pTopLevelItem = new QTreeWidgetItem(this);
    pTopLevelItem -> setText(0, pObj -> Name());
    pTopLevelItem -> setText(1, pObj -> TypeName(pObj -> type()));

    addTopLevelItem(pTopLevelItem);
    setCurrentItem(pTopLevelItem);
    emit changeObj(pObj);
}
