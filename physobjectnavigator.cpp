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

    m_pCurrObj = m_pPrevObj = NULL;
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

void PhysObjectNavigator::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    qDebug("PhysObjectNavigator::selectionChanged()");
    QModelIndex index;
    QModelIndexList items = selected.indexes();

    index = items.at(0);
    QTreeWidgetItem *pItem = itemFromIndex(index);
    if (pItem) {
        QVariant itemData = pItem ->data(0, Qt::UserRole);
        QGraphicsItem *pObj = itemData.value<QGraphicsItem *>();
        m_pPrevObj = m_pCurrObj;
        m_pCurrObj = pObj;
    }

    // Changing the currentitem
    // If we're brand new then there is no pPrevObj
    if (!m_pPrevObj)
        emit changeObj(m_pCurrObj, m_pPrevObj);
    else {
        if (m_pPrevObj ->type() != m_pCurrObj ->type())
            emit changeObj(m_pCurrObj, m_pPrevObj);
        else
            emit updateObj(m_pCurrObj);
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
            var.setValue(static_cast<QGraphicsItem *>(pObj));
            pChildItem -> setData(0, Qt::UserRole, var);
            pParentItem -> addChild(pChildItem);
            m_pPrevObj = m_pCurrObj;
            m_pCurrObj = pObj;
            setCurrentItem(pChildItem);
            emit changeObj(m_pCurrObj, m_pPrevObj);
        }
    }
}

void PhysObjectNavigator::insertParticle(PhysParticle *pObj) {
    qDebug("PhysObjectNavigator::insertParticle()");


    // particles are always a direct child of the CartesianGraph they're tied to
    QTreeWidgetItem *pTopLevelItem = topLevelItem(0);
    if (pTopLevelItem) {
        QTreeWidgetItem *pChildItem = new QTreeWidgetItem(pTopLevelItem);
        pChildItem -> setText(0, pObj -> Name());
        pChildItem -> setText(1, pObj -> TypeName(pObj -> type()));

        QVariant var;
        var.setValue(static_cast<QGraphicsItem *>(pObj));
        pChildItem -> setData(0, Qt::UserRole, var);
        pTopLevelItem -> addChild(pChildItem);
        m_pPrevObj = m_pCurrObj;
        m_pCurrObj = pObj;
        setCurrentItem(pChildItem);
        emit changeObj(m_pCurrObj, m_pCurrObj);
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
    var.setValue(static_cast<QGraphicsItem *>(pObj));
    pTopLevelItem -> setData(0, Qt::UserRole, var);
    addTopLevelItem(pTopLevelItem);

    // There are currently only one of these being created.
    // When 2D kinematics are supported we'll add in support for two.
    m_pCurrObj = m_pPrevObj = pObj;
    emit changeObj(pObj, NULL);
}
