#include <QPainter>
#include <QString>
#include <math.h>

#include "physvector.h"
#include "physparticle.h"
#include "cartesianlabel.h"
#include "cartesiangraph.h"

PhysVector::PhysVector(CartesianGraph *pParent, const QPointF &startPos, const QString &Label, PhysParticle *pStart, PhysParticle *pEnd, QGraphicsScene *scene) : QGraphicsLineItem(pParent) {
    m_Color = Qt::black;
    m_magnitude = 50.0;
    m_arrowSize = 20;
    m_dragIndex = DI_VECTORLINE;
    m_pLabel = new CartesianLabel(Label, this);
    m_pStartParticle = pStart;
    m_pEndParticle = pEnd;

    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setLine(0, 0, 0 + m_magnitude, 0 + m_magnitude);
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
    const qreal adjust = (pen().width() + 20) / 2.0;
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(), line().p2().y() - line().p1().y()))
            .normalized()
            .adjusted(-adjust, -adjust, adjust, adjust);
}

QPainterPath PhysVector::shape() const {
    path.addPolygon(m_arrowHead);
    QPainterPath path = QGraphicsLineItem::shape();
    return path;
}

void PhysVector::updatePosition() {
    if (m_pStartParticle && m_pEndParticle) {
        QLineF line(mapFromItem(m_pStartParticle, 0, 0), mapFromItem(m_pEndParticle, 0, 0));
        setLine(line);
    }
    else {
    }
}

void PhysVector::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *) {
    QPen myPen = pen();

    //myPen.setColor(m_Color);
    pPainter -> setPen(pen());
    //pPainter -> setBrush(m_Color);

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
    QLineF aLine = line();
    double angle = ::acos(aLine.dx() / aLine.length());
    if (aLine.dy() >= 0) {
        angle = (PI * 2) - angle;
        QPointF arrowP1 = aLine.p1() + QPointF(sin(angle + PI / 3) * m_arrowSize, cos(angle + PI / 3) * m_arrowSize);
        QPointF arrowP2 = aLine.p1() + QPointF(sin(angle + PI - PI / 3) * m_arrowSize, cos(angle + PI - PI / 3) * m_arrowSize);

        m_arrowHead.clear();
        m_arrowHead << aLine.p1() << arrowP1 << arrowP2;
        pPainter -> drawLine(aLine);
        pPainter -> drawPolygon(m_arrowHead);
        if (isSelected())
            pPainter -> setPen(QPen(m_Color, 1, Qt::DashLine));
        QLineF tmpline = aLine;
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
    const QPointF pos = event -> pos();
    const qreal line1 = QLineF(pos, line().p1()).length();
    const qreal line2 = QLineF(pos, line().p2()).length();
    const qreal threshold = 3.5;

    // DI_VECTORLINE = -1, DI_VECTORHEAD, DI_VECTORTAIL

    if (line1 < line2 && line1 < threshold)
        m_dragIndex = DI_VECTORTAIL;
    else if (line2 < line1 && line2 < threshold)
        m_dragIndex = DI_VECTORHEAD;
    else
        m_dragIndex = DI_VECTORLINE;
    event -> setAccepted(m_dragIndex != DI_VECTORLINE);
    update();
    QGraphicsItem::mousePressEvent(event);
}

void PhysVector::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (m_dragIndex == DI_VECTORLINE) {
        event -> pos();
    }
    else
        m_dragIndex = DI_VECTORLINE;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void PhysVector::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if (m_dragIndex != DI_VECTORLINE) {
        const QPointF anchor = (m_dragIndex == DI_VECTORHEAD) ? line().p1() : line().p2();
        QLineF ma = QLineF(anchor, event -> pos());
        ma.setLength(line().length());
        const QPointF rotated = anchor + QPointF(ma.dx(), ma.dy());
        setLine(m_dragIndex == DI_VECTORHEAD ? QLineF(anchor, rotated) : QLineF(rotated, anchor));
    }
    else {

        // handle the movement of the entire vector object
        QGraphicsItem::mouseMoveEvent(event);
    }
}
