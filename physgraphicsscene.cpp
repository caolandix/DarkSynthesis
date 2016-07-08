#include <QGraphicsSceneMouseEvent>

#include "physgraphicsscene.h"
#include "physvector.h"


PhysGraphicsScene::PhysGraphicsScene(QObject *parent) : QGraphicsScene(parent) {
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
            m_pCurrTextItem = new CartesianLabel("");
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
