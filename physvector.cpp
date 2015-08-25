#include <QPainter>
#include <math.h>

#include "physvector.h"
#include "physparticle.h"
#include "cartesianlabel.h"

PhysVector::PhysVector(QGraphicsItem *parent, PhysParticle *pStart, PhysParticle *pEnd, QGraphicsScene *scene) : QGraphicsLineItem(parent) {
    m_magnitude = 0.0;
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    m_Color = Qt::black;
    setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    m_pLabel = new CartesianLabel(QString("Vector"), this);
    m_pStartParticle = pStart;
    m_pEndParticle = pEnd;
}

PhysVector::~PhysVector() {
    if (m_pLabel) {
        delete m_pLabel;
        m_pLabel = NULL;
    }
    m_pStartParticle = NULL;
    m_pEndParticle = NULL;
}

QRectF PhysVector::boundingRect() const {
    const qreal adjust = 2.0;
    return QRectF(-10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath PhysVector::shape() const {
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(m_arrowHead);
    return path;
}

void PhysVector::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *) {
    if (m_pStartParticle -> collidesWithItem(m_pEndParticle))
        return;
    QPen myPen = pen();
    qreal arrowSize = 20;

    myPen.setColor(m_Color);
    pPainter -> setPen(myPen);
    pPainter -> setBrush(m_Color);

    QLineF centerLine(m_pStartParticle -> pos(), m_pEndParticle -> pos());
    QPolygonF endPolygon = m_pEndParticle -> polygon();
    QPointF p1 = endPolygon.first() + m_pEndParticle -> pos();
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;

    for (int i = 1; i < endPolygon.count(); ++i) {
        p2 = endPolygon.at(i) + m_pEndParticle -> pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType = polyLine.intersect(centerLine, &intersectPoint);
        if (intersectType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }
    setLine(QLineF(intersectPoint, m_pStartParticle -> pos()));

    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (PI * 2) - angle;
        QPointF arrowP1 = line().p1() + QPointF(sin(angle + PI / 3) * arrowSize, cos(angle + PI / 3) * arrowSize);
        QPointF arrowP2 = line().p1() + QPointF(sin(angle + PI - PI / 3) * arrowSize, cos(angle + PI - PI / 3) * arrowSize);

        m_arrowHead.clear();
        m_arrowHead << line().p1() << arrowP1 << arrowP2;
        pPainter -> drawLine(line());
        pPainter -> drawPolygon(m_arrowHead);
        if (isSelected()) {
            pPainter -> setPen(QPen(m_Color, 1, Qt::DashLine));
        QLineF tmpline = line();
        tmpline.translate(0, 4.0);
        pPainter -> drawLine(tmpline);
        tmpline.translate(0, -8.0);
        pPainter -> drawLine(tmpline);
    }
}

QVariant PhysVector::itemChange(GraphicsItemChange change, const QVariant &value) {
    switch (change) {
        case ItemPositionHasChanged:
            break;
        default:
            break;
    };
    return QGraphicsItem::itemChange(change, value);
}

void PhysVector::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mousePressEvent(event);
}

void PhysVector::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
