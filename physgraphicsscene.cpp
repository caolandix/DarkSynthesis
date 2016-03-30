#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>

#include "physgraphicsscene.h"
#include "physvector.h"


PhysGraphicsScene::PhysGraphicsScene(QMenu *pItemMenu, QObject *parent) : QGraphicsScene(parent) {
    m_currAction = MoveItem;
    m_pItemMenu = pItemMenu;
    m_currItemType = PhysDataObj::DT_UNASSIGNED;
    m_pLine = NULL;
    m_pCurrTextItem = NULL;
    m_currItemColor = Qt::white;
    m_currTextColor = Qt::black;
    m_currLineColor = Qt::black;
}

void PhysGraphicsScene::setLineColor(const QColor &color) {
    /*
    myLineColor = color;
    if (isItemChange(Arrow::Type)) {
        PhysVector *item = qgraphicsitem_cast<Arrow *>(selectedItems().first());
        item ->setColor(myLineColor);
        update();
    }
    */
}

void PhysGraphicsScene::setTextColor(const QColor &color) {
    m_currTextColor = color;
    if (isItemChange(PhysBaseItem::PhysTextType)) {
        CartesianLabel *pItem = qgraphicsitem_cast<CartesianLabel *>(selectedItems().first());
        pItem ->setDefaultTextColor(m_currTextColor);
    }
}

void PhysGraphicsScene::setItemColor(const QColor &color) {
    /*
    myItemColor = color;
    if (isItemChange(DiagramItem::Type)) {
        DiagramItem *item = qgraphicsitem_cast<DiagramItem *>(selectedItems().first());
        item->setBrush(myItemColor);
    }
    */
}

void PhysGraphicsScene::setFont(const QFont &font) {
    m_currFont = font;

    if (isItemChange(PhysBaseItem::PhysTextType)) {
        CartesianLabel *pItem = qgraphicsitem_cast<CartesianLabel *>(selectedItems().first());
        //At this point the selection can change so the first selected item might not be a DiagramTextItem
        if (pItem)
            pItem ->setFont(m_currFont);
    }
}

void PhysGraphicsScene::setAction(Actions action) {
    m_currAction = action;
}

void PhysGraphicsScene::setItemType(int type) {
    m_currItemType = type;
}

void PhysGraphicsScene::editorLostFocus(CartesianLabel *pItem) {
    QTextCursor cursor = pItem ->textCursor();
    cursor.clearSelection();
    pItem ->setTextCursor(cursor);

    if (pItem ->toPlainText().isEmpty()) {
        removeItem(pItem);
        pItem ->deleteLater();
    }
}

void PhysGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent ->button() != Qt::LeftButton)
        return;

    PhysParticle *pItem = NULL;
    switch (m_currAction) {
    /*
        case InsertItem:
            item = new PhysParticle(myItemType, myItemMenu);
            item ->setBrush(myItemColor);
            addItem(item);
            item ->setPos(mouseEvent->scenePos());
            emit itemInserted(item);
            break;
        case InsertLine:
            m_pLine = new QGraphicsLineItem(QLineF(mouseEvent ->scenePos(), mouseEvent ->scenePos()));
            m_pLine ->setPen(QPen(myLineColor, 2));
            addItem(m_pLine);
            break;
            */
        case InsertText:
            m_pCurrTextItem = new CartesianLabel();
            m_pCurrTextItem ->setFont(m_currFont);
            m_pCurrTextItem ->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_pCurrTextItem ->setZValue(1000.0);
            connect(m_pCurrTextItem, SIGNAL(lostFocus(CartesianLabel *)), this, SLOT(editorLostFocus(CartesianLabel *)));
            connect(m_pCurrTextItem, SIGNAL(selectedChange(QGraphicsItem *)), this, SIGNAL(itemSelected(QGraphicsItem *)));
            addItem(m_pCurrTextItem);
            m_pCurrTextItem ->setDefaultTextColor(m_currTextColor);
            m_pCurrTextItem ->setPos(mouseEvent ->scenePos());
            emit textInserted(m_pCurrTextItem);
    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void PhysGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    /*
    if (myMode == InsertLine && m_pLine) {
        QLineF newLine(m_pLine ->line().p1(), mouseEvent ->scenePos());
        m_pLine ->setLine(newLine);
    }
    else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
    */
}

void PhysGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    /*
    if (line && myMode == InsertLine) {
        QList<QGraphicsItem *> startItems = items(m_pLine ->line().p1());
        if (startItems.count() && startItems.first() == m_pLine)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(m_pLine ->line().p2());
        if (endItems.count() && endItems.first() == m_pLine)
            endItems.removeFirst();

        removeItem(m_pLine);
        delete m_pLine;

        if (startItems.count() > 0 && endItems.count() > 0 && startItems.first() ->type() == PhysParticle::Type &&
            endItems.first() ->type() == PhysParticle::Type && startItems.first() != endItems.first()) {

            PhysParticle *startItem = qgraphicsitem_cast<PhysParticle *>(startItems.first());
            PhysParticle *endItem = qgraphicsitem_cast<PhysParticle *>(endItems.first());
            PhysVector *arrow = new PhysVector(startItem, endItem);
            arrow ->setColor(myLineColor);
            startItem ->addVector(arrow);
            endItem ->addVector(arrow);
            arrow ->setZValue(-1000.0);
            addItem(arrow);
            arrow ->updatePosition();
        }
    }
    m_pLine = NULL;
    */
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool PhysGraphicsScene::isItemChange(int type) {
    foreach (QGraphicsItem *pItem, selectedItems()) {
        if (pItem ->type() == type)
            return true;
    }
    return false;
}
