#include <QPainter>
#include <QString>
#include <QAction>
#include <QMenu>
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
    m_pParent = pParent;

    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemSendsScenePositionChanges);
    setFlag(ItemIsFocusable);
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

QVariant PhysVector::itemChange(GraphicsItemChange change, const QVariant &value) {
    switch (change) {
        case ItemPositionHasChanged:
            break;
        default:
            break;
    };
    return QGraphicsItem::itemChange(change, value);
}

void PhysVector::adjust() {
    if (!m_pStartParticle || !m_pEndParticle)
        return;
    else {
        if (m_pStartParticle && !m_pEndParticle) {

        }
        else if (!m_pStartParticle && m_pEndParticle) {

        }
        else {
            // QLineF aline(mapFromItem(m_pStartParticle, 0, 0), mapFromItem(m_pEndParticle, 0, 0));
            qreal length = line().length();
            QLineF my_line(line().p1(), line().p2());

            prepareGeometryChange();
            if (length > qreal(20.)) {
                QPointF edgeOffset((my_line.dx() * 10) / length, (my_line.dy() * 10) / length);
                m_StartPoint = my_line.p1() + edgeOffset;
                m_EndPoint = my_line.p2() - edgeOffset;
            }
            else
                m_StartPoint = m_EndPoint = my_line.p1();
        }
    }
}

QRectF PhysVector::boundingRect() const {
    qreal penWidth = 1;
    qreal extra = (penWidth + m_arrowSize) / 2.0;
    QPointF pt1 = line().p1();
    QPointF pt2 = line().p2();
    QRectF rcBounding(pt1, QSizeF(pt2.x() - pt1.x(), pt2.y() - pt1.y()));

    return rcBounding.normalized().adjusted(-extra, -extra, extra, extra);
}

QPainterPath PhysVector::shape() const {
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(m_arrowHead);
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
    pPainter -> setPen(pen());

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
    QPointF arrowP1, arrowP2;
    double angle = ::acos(aLine.dx() / aLine.length());

    angle = (aLine.dy() >= 0) ? (PI * 2) - angle : (PI * 2) + angle;
    arrowP1 = aLine.p1() + QPointF(sin(angle + PI / 3) * m_arrowSize, cos(angle + PI / 3) * m_arrowSize);
    arrowP2 = aLine.p1() + QPointF(sin(angle + PI - PI / 3) * m_arrowSize, cos(angle + PI - PI / 3) * m_arrowSize);
    m_arrowHead.clear();
    m_arrowHead << line().p1() << arrowP1 << arrowP2;
    pPainter -> drawLine(aLine);
    pPainter -> drawPolygon(m_arrowHead);

    QPainterPath tmpPath;
    QBrush brush(QColor("black"));
    tmpPath.addPolygon(m_arrowHead);
    pPainter -> fillPath(tmpPath, brush);

    if (isSelected()) {
        /*
        QPolygonF selectionBox;
        selectionBox.clear();

        pPainter -> setPen(QPen(m_Color, 1, Qt::DashLine));
        pPainter ->drawPolygon(selectionBox);
        */
    }
}

void PhysVector::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    const QPointF pos = event -> pos();
    const qreal line1 = QLineF(pos, line().p1()).length();
    const qreal line2 = QLineF(pos, line().p2()).length();
    const qreal threshold = 3.5;

    if (line1 < line2 && line1 < threshold)
        m_dragIndex = DI_VECTORTAIL;
    else if (line2 < line1 && line2 < threshold)
        m_dragIndex = DI_VECTORHEAD;
    else {
        m_dragIndex = DI_VECTORLINE;
        m_currPos = event -> pos();
    }
    event -> setAccepted(true);//m_dragIndex != DI_VECTORLINE);
    qDebug("mousePressEvent m_dragIndex: '%d'", m_dragIndex);
    update();
    QGraphicsItem::mousePressEvent(event);
}

void PhysVector::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (m_dragIndex == DI_VECTORLINE) {
        event -> pos();
    }
    else
        m_dragIndex = DI_VECTORLINE;

    // Now check to see if one of the end points collides with a particle. If so, attach to it
    QList<PhysParticle *> particles = m_pParent ->Vectors();
    QPointF pt1 = line().p1();
    QPointF pt2 = line().p2();
    for (QList<PhysParticle *>::Iterator iter = particles.begin(); iter != particles.end(); iter++) {
        PhysParticle *particle = *iter;

        if (collidesWithItem(particle)) {
        }
    }
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void PhysVector::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    qDebug("mouseMoveEvent m_dragIndex: '%d'", m_dragIndex);
    if (m_dragIndex != DI_VECTORLINE) {

        const QPointF anchor = (m_dragIndex == DI_VECTORHEAD) ? line().p1() : line().p2();
        QLineF ma = QLineF(anchor, event -> pos());
        ma.setLength(line().length());
        const QPointF rotated = anchor + QPointF(ma.dx(), ma.dy());
        setLine(m_dragIndex == DI_VECTORHEAD ? QLineF(anchor, rotated) : QLineF(rotated, anchor));
    }
    else {
        QPointF pt1 = line().p1();
        QPointF pt2 = line().p2();
        qreal dx = event -> pos().x() - m_currPos.x();
        qreal dy = event -> pos().y() - m_currPos.y();
        pt1.setX(pt1.x() + dx);
        pt1.setY(pt1.y() + dy);
        pt2.setX(pt2.x() + dx);
        pt2.setY(pt2.y() + dy);
        setLine(QLineF(pt1, pt2));
        m_currPos = event -> pos();
        QGraphicsItem::mouseMoveEvent(event);
    }
    update();
}

void PhysVector::vectorPropsDlg() {
    qDebug("vectorPropsDlg()");
}

void PhysVector::createActions() {
}

void PhysVector::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
}
