#include "physparticle.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

PhysParticle::PhysParticle(GraphWidget *graphWidget) : graph(graphWidget) {
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

QRectF PhysParticle::boundingRect() const {
    qreal adjust = 2.0;
    return QRectF(-10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath PhysParticle::shape() const {
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void PhysParticle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
}

QVariant PhysParticle::itemChange(GraphicsItemChange change, const QVariant &value) {
    switch (change) {
        case ItemPositionHasChanged:
            break;
        default:
            break;
    };
    return QGraphicsItem::itemChange(change, value);
}

void PhysParticle::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mousePressEvent(event);
}

void PhysParticle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
