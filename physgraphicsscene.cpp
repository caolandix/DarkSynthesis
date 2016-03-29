#include "physgraphicsscene.h"
#include "physvector.h"
#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>

PhysGraphicsScene::PhysGraphicsScene(QMenu *itemMenu, QObject *parent) : QGraphicsScene(parent) {
    /*
    myMode = MoveItem;
    myItemType = DiagramItem::Step;
    line = 0;
    textItem = 0;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;
    */
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
    /*
    myTextColor = color;
    if (isItemChange(DiagramTextItem::Type)) {
        DiagramTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        item->setDefaultTextColor(myTextColor);
    }
    */
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
    /*
    myFont = font;

    if (isItemChange(DiagramTextItem::Type)) {
        CartesianLabel *item = qgraphicsitem_cast<CartesianLabel *>(selectedItems().first());
        //At this point the selection can change so the first selected item might not be a DiagramTextItem
        if (item)
            item ->setFont(myFont);
    }
    */
}

void PhysGraphicsScene::setMode(Mode mode) {
    // myMode = mode;
}

void PhysGraphicsScene::setItemType(PhysDataObj::DataType type) {
    // myItemType = type;
}

void PhysGraphicsScene::editorLostFocus(CartesianLabel *item) {
    /*
    QTextCursor cursor = item ->textCursor();
    cursor.clearSelection();
    item ->setTextCursor(cursor);

    if (item ->toPlainText().isEmpty()) {
        removeItem(item);
        item ->deleteLater();
    }
    */
}

void PhysGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    /*
    if (mouseEvent ->button() != Qt::LeftButton)
        return;

    PhysParticle *item;
    switch (myMode) {
        case InsertItem:
            item = new PhysParticle(myItemType, myItemMenu);
            item ->setBrush(myItemColor);
            addItem(item);
            item ->setPos(mouseEvent->scenePos());
            emit itemInserted(item);
            break;
        case InsertLine:
            line = new QGraphicsLineItem(QLineF(mouseEvent ->scenePos(), mouseEvent ->scenePos()));
            line ->setPen(QPen(myLineColor, 2));
            addItem(line);
            break;
        case InsertText:
            textItem = new CartesianLabel();
            textItem ->setFont(myFont);
            textItem ->setTextInteractionFlags(Qt::TextEditorInteraction);
            textItem ->setZValue(1000.0);
            connect(textItem, SIGNAL(lostFocus(CartesianLabel *)), this, SLOT(editorLostFocus(CartesianLabel *)));
            connect(textItem, SIGNAL(selectedChange(QGraphicsItem *)), this, SIGNAL(itemSelected(QGraphicsItem *)));
            addItem(textItem);
            textItem ->setDefaultTextColor(myTextColor);
            textItem ->setPos(mouseEvent ->scenePos());
            emit textInserted(textItem);
    default:
        ;
    }
    */
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void PhysGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    /*
    if (myMode == InsertLine && line != 0) {
        QLineF newLine(line ->line().p1(), mouseEvent ->scenePos());
        line ->setLine(newLine);
    }
    else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
    */
}

void PhysGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    /*
    if (line != 0 && myMode == InsertLine) {
        QList<QGraphicsItem *> startItems = items(line ->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line ->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;

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
    line = 0;
    */
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool PhysGraphicsScene::isItemChange(int type) {
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item ->type() == type)
            return true;
    }
    return false;
}
