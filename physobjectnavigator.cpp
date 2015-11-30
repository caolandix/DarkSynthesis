#include <QTreeWidget>
#include <QGraphicsItem>
#include <QItemSelection>
#include <QTreeWidgetItem>
#include <QMenu>
#include <QModelIndex>
#include <QVariant>

#include "physbaseitem.h"
#include "physobjectnavigator.h"
#include "cartesiangraph.h"
#include "physvector.h"
#include "physparticle.h"

PhysObjectNavigator::PhysObjectNavigator(QWidget *pParent) : QTreeWidget(pParent) {

    // Initialise privates
    m_pCurrObj = m_pPrevObj = NULL;

    // Setup widget
    setColumnCount(2);
    setRootIsDecorated(true);
    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    setContextMenuPolicy(Qt::CustomContextMenu);

    QStringList colLabels;
    colLabels << "PhysObject Name" << "PhysObject Type";
    setHeaderLabels(colLabels);

    // Setup the context Menu
    createContextMenu();
}

void PhysObjectNavigator::createContextMenu() {
    // Hook up the custom Context menu handler
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(onCustomContextMenu(const QPoint &)));
}

void PhysObjectNavigator::cloneObject() {
    QAction *pAction = qobject_cast<QAction *>(sender());
    QVariant itemData = pAction -> data();
    QGraphicsItem *pObj = itemData.value<QGraphicsItem *>();
    QGraphicsItem *pNewObj = NULL;

    if (!pObj)
        qDebug("PhysObjectNavigator::resetObject: PhysObject is NULL");
    else {
        switch (pObj -> type()) {
        case PhysBaseItem::VectorType: {
            PhysVector *pCurr = static_cast<PhysVector *>(pObj);
            PhysVector *pNew = pCurr ->copy();
            pNewObj = static_cast<QGraphicsItem *>(pNew);
            break;
        }
        case PhysBaseItem::ParticleType: {
            PhysParticle *pCurr = static_cast<PhysParticle *>(pObj);
            PhysParticle *pNew = pCurr ->copy();
            pNewObj = static_cast<QGraphicsItem *>(pNew);
            break;
        }
        default:
            qDebug("PhysObjectNavigator::cloneObject: not a supported object type: %d", pObj -> type());
            break;
        }
        if (pNewObj)
            emit clonePhysObj(pNewObj);
    }
}
void PhysObjectNavigator::removeObject() {
    QAction *pAction = qobject_cast<QAction *>(sender());
    QVariant itemData = pAction -> data();
    QGraphicsItem *pObj = itemData.value<QGraphicsItem *>();

    if (!pObj)
        qDebug("PhysObjectNavigator::resetObject: PhysObject is NULL");
    else {
        switch (pObj ->type()) {
        case PhysBaseItem::VectorType:{
            PhysVector *pCurr = static_cast<PhysVector *>(pObj);
            pCurr ->removeFromParticles();
            break;
        }
        case PhysBaseItem::ParticleType:{
            PhysParticle *pCurr = static_cast<PhysParticle *>(pObj);
            pCurr ->DisassociateVectors();
            break;
        }
        default:
            qDebug("PhysObjectNavigator::deleteObject: not a supported object type: %d", pObj -> type());
            break;
        }
        removeFromTreeWidgetParent(pObj);
        emit removePhysObj(pObj);
    }
}

void PhysObjectNavigator::removeFromTreeWidgetParent(QGraphicsItem *pObj) {
    QTreeWidgetItemIterator it(this);
    while (*it) {
        QTreeWidgetItem *pItem = (*it);
        QVariant itemData = pItem ->data(0, Qt::UserRole);
        QGraphicsItem *pCurrObj = itemData.value<QGraphicsItem *>();

        if (pCurrObj == pObj && pCurrObj ->type() != PhysBaseItem::CartesianGraphType) {
            QTreeWidgetItem *pParentItem = pItem ->parent();
            if (pParentItem) {
                pParentItem ->removeChild(pItem);
                qDebug("PhysObjectNavigator::removeFromTreeWidgetParent(): found it!");
                return;
            }
        }
        ++it;
    }
}

void PhysObjectNavigator::resetObject() {
    qDebug("PhysObjectNavigator::resetObject");
    QAction *pAction = qobject_cast<QAction *>(sender());
    QVariant itemData = pAction -> data();
    QGraphicsItem *pObj = itemData.value<QGraphicsItem *>();

    if (!pObj)
        qDebug("PhysObjectNavigator::resetObject: PhysObject is NULL");
    else {
        switch (pObj ->type()) {
        case PhysBaseItem::VectorType:{
            PhysVector *pCurr = static_cast<PhysVector *>(pObj);
            pCurr ->init();
            break;
        }
        case PhysBaseItem::ParticleType:{
            PhysParticle *pCurr = static_cast<PhysParticle *>(pObj);
            pCurr ->init();
            break;
        }
        case PhysBaseItem::CartesianGraphType:{
            CartesianGraph *pCurr = static_cast<CartesianGraph *>(pObj);
            pCurr ->init();
            break;
        }
        default:
            qDebug("PhysObjectNavigator::deleteObject: not a supported object type: %d", pObj -> type());
            break;
        }
    }
}

void PhysObjectNavigator::onCustomContextMenu(const QPoint &pos) {
    QMenu contextMenu(this);
    QModelIndex index = indexAt(pos);

    if (index.isValid()) {
        QTreeWidgetItem *pItem = itemFromIndex(indexAt(pos));
        QVariant itemData = pItem ->data(0, Qt::UserRole);
        QGraphicsItem *pObj = itemData.value<QGraphicsItem *>();

        m_pActCloneItem = new QAction(tr("Clone Item"), this);
        m_pActCloneItem -> setStatusTip(tr("Create an identical Physics object"));
        connect(m_pActCloneItem, SIGNAL(triggered()), this, SLOT(cloneObject()));
        m_pActCloneItem ->setData(itemData);

        m_pActDeleteItem = new QAction(tr("Delete Item"), this);
        m_pActDeleteItem -> setStatusTip(tr("Removes the Physics object"));
        connect(m_pActDeleteItem, SIGNAL(triggered()), this, SLOT(removeObject()));
        m_pActDeleteItem ->setData(itemData);

        m_pActResetItem = new QAction(tr("Reset Item"), this);
        m_pActResetItem -> setStatusTip(tr("Resets the Physics object to default values"));
        connect(m_pActResetItem, SIGNAL(triggered()), this, SLOT(resetObject()));
        m_pActResetItem ->setData(itemData);

        contextMenu.addAction(m_pActCloneItem);
        contextMenu.addAction(m_pActDeleteItem);
        contextMenu.addAction(m_pActResetItem);

        contextMenu.exec(mapToGlobal(pos));
    }
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
    qDebug("PhysObjectNavigator::dropEvent()");
    QTreeWidgetItem *pItem = itemFromIndex(indexAt(pEvent -> pos()));
    QVariant itemData = pItem -> data(0, Qt::UserRole);
    QGraphicsItem *pObj = itemData.value<QGraphicsItem *>();

    // The object must have a parent to be dropped
    if (pObj -> type() != PhysBaseItem::CartesianGraphType) {
        if (PhysBaseItem::VectorType) {

        }
        else if (PhysBaseItem::ParticleType) {

        }
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
            setCurrentItem(pChildItem);
            emit changeObj(m_pCurrObj, m_pPrevObj);
            m_pPrevObj = m_pCurrObj;
            m_pCurrObj = pObj;
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
