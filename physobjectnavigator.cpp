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
    qDebug("PhysObjectNavigator::onCreateObj()");
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
    qDebug("PhysObjectNavigator::currentChanged()");
    QVariant varCurrent = current.data(Qt::UserRole);
    QVariant varPrev = previous.data(Qt::UserRole);

    QGraphicsItem *pCurrObj = qvariant_cast<QGraphicsItem *>(varCurrent);
    QGraphicsItem *pPrevObj = qvariant_cast<QGraphicsItem *>(varPrev);

    if (!pCurrObj && !pPrevObj)
        return;

    // Changing the currentitem
    // If we're brand new then there is no pPrevObj
    if (!pPrevObj)
        emit changeObj(pCurrObj, pPrevObj);
    else {
        if (pPrevObj ->type() != pCurrObj ->type())
            emit changeObj(pCurrObj, pPrevObj);
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
    qDebug("PhysObjectNavigator::insertVector()");
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
            pChildItem -> setText(0, pObj -> Name());
            pChildItem -> setText(1, pObj -> TypeName(pObj -> type()));

            QVariant var;
            var.setValue(pObj);
            pChildItem -> setData(0, Qt::UserRole, var);

            pParentItem -> addChild(pChildItem);
            QTreeWidgetItem *pCurrentItem = currentItem();

            var = pCurrentItem -> data(0, Qt::UserRole);
            QGraphicsItem *pCurrItemDataObj = var.value<QGraphicsItem *>();

            setCurrentItem(pChildItem);
            emit changeObj(pObj, pCurrItemDataObj);
        }
    }
}

void PhysObjectNavigator::insertParticle(PhysParticle *pObj) {
    qDebug("PhysObjectNavigator::insertVector()");

    QTreeWidgetItem *pTopLevelItem = topLevelItem(0);
    if (pTopLevelItem) {
        QTreeWidgetItem *pChildItem = new QTreeWidgetItem(pTopLevelItem);
        QString str = pObj -> Name();
        pChildItem -> setText(0, pObj -> Name());
        pChildItem -> setText(1, pObj -> TypeName(pObj -> type()));

        QVariant var;
        var.setValue(pObj);
        pChildItem -> setData(0, Qt::UserRole, var);

        pTopLevelItem -> addChild(pChildItem);


        QTreeWidgetItem *pCurrentItem = currentItem();
        var = pCurrentItem -> data(0, Qt::UserRole);
        QGraphicsItem *pCurrItemDataObj = (QGraphicsItem *) var.value<void *>();
        setCurrentItem(pChildItem);
        emit changeObj(pObj, pCurrItemDataObj);
    }
}

void PhysObjectNavigator::insertCartesianGraph(CartesianGraph *pObj) {
    QTreeWidgetItem *pTopLevelItem = topLevelItem(0);

    if (pTopLevelItem)
        removeItemWidget(pTopLevelItem, 0);
    pTopLevelItem = new QTreeWidgetItem(this);
    pTopLevelItem -> setText(0, pObj -> Name());
    pTopLevelItem -> setText(1, pObj -> TypeName(pObj -> type()));

    QVariant var;
    var.setValue(pObj);
    pTopLevelItem -> setData(0, Qt::UserRole, var);
    addTopLevelItem(pTopLevelItem);

    // There are currently only one of these being created.
    // When 2D kinematics are supported we'll add in support for two.
    emit changeObj(pObj, NULL);
}
