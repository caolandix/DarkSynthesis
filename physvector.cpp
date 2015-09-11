#include <QPainter>
#include <math.h>

#include "physvector.h"
#include "physparticle.h"
#include "cartesianlabel.h"
#include "cartesiangraph.h"

PhysVector::PhysVector(CartesianGraph *pParent, const QPointF &startPos, PhysParticle *pStart, PhysParticle *pEnd, QGraphicsScene *scene) : QGraphicsLineItem(pParent) {
    m_Color = Qt::black;
    m_magnitude = 50.0;
    m_arrowSize = 20;
    m_pLabel = new CartesianLabel(QString("Vector"), this);
    m_pStartParticle = pStart;
    m_pEndParticle = pEnd;

    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setLine(startPos.x(), startPos.y(), startPos.x() + m_magnitude, startPos.y() + m_magnitude);
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
    QPen myPen = pen();

    myPen.setColor(m_Color);
    pPainter -> setPen(myPen);
    pPainter -> setBrush(m_Color);

    // If there are two particles to attach to then draw a the vector and attach to them
    if (m_pStartParticle && m_pEndParticle) {
        if (m_pStartParticle -> collidesWithItem(m_pEndParticle))
            return;
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
    }

    // else if there is a starting particle and no ending particle then handle
    else if (m_pStartParticle && !m_pEndParticle) {
    }

    // likewise if there is no starting particle but an ending particle, handle
    else if (!m_pStartParticle && m_pEndParticle) {

    }

    // The default case of NO particles, is just a vector. We do nothing and just drop into the vector draw
    else {
    }

    // Draw the vector
    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (PI * 2) - angle;
        QPointF arrowP1 = line().p1() + QPointF(sin(angle + PI / 3) * m_arrowSize, cos(angle + PI / 3) * m_arrowSize);
        QPointF arrowP2 = line().p1() + QPointF(sin(angle + PI - PI / 3) * m_arrowSize, cos(angle + PI - PI / 3) * m_arrowSize);

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
