#include "physvector.h"
#include "cartesianlabel.h"

PhysVector::PhysVector(PhysParticle *pStart, PhysParticle *pEnd, QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsLineItem(parent, scene) {
    m_magnitude = 0.0;
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    m_Color = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    m_pLabel = new CartesianLabel(QString("Vector"), this);
    m_StartParticle = pStart;
    m_EndParticle = pEnd;
}
PhysVector::~PhysVector() {
    if (m_pLabel) {
        delete m_pLabel;
        m_pLabel = NULL;
    }

    m_StartParticle = NULL;
    m_EndParticle = NULL;
}


QRectF PhysVector::boundingRect() const {
    const qreal adjust = 2.0;
    return QRectF(-10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath PhysVector::shape() const {
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void PhysVector::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *) {
    if (m_StartParticle -> collidesWithItem(m_EndParticle))
        return;
    QPen myPen = pen();
    qreal arrowSize = 20;

    myPen.setColor(m_Color);
    pPainter -> setPen(myPen);
    pPainter -> setBrush(m_Color);

    QLineF centerLine(m_StartParticle -> pos(), m_EndParticle -> pos());
    QPolygonF endPolygon = m_EndParticle -> polygon();
    QPointF p1 = endPolygon.first() + myEndItem -> pos();
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;

    for (int i = 1; i < endPolygon.count(); ++i) {
        p2 = endPolygon.at(i) + myEndItem -> pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType = polyLine.intersect(centerLine, &intersectPoint);
        if (intersectType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }
    setLine(QLineF(intersectPoint, m_StartParticle -> pos()));

    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (PI * 2) - angle;
        QPointF arrowP1 = line().p1() + QPointF(sin(angle + PI / 3) * arrowSize, cos(angle + PI / 3) * arrowSize);
        QPointF arrowP2 = line().p1() + QPointF(sin(angle + PI - PI / 3) * arrowSize, cos(angle + PI - PI / 3) * arrowSize);

        arrowHead.clear();
        arrowHead << line().p1() << arrowP1 << arrowP2;
        pPainter -> drawLine(line());
        pPainter -> drawPolygon(arrowHead);
        if (isSelected()) {
            pPainter -> setPen(QPen(m_Color, 1, Qt::DashLine));
        QLineF line = line();
        line.translate(0, 4.0);
        pPainter -> drawLine(line);
        line.translate(0, -8.0);
        pPainter -> drawLine(line);
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

Arrow::Arrow(DiagramItem *startItem, DiagramItem *endItem, QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsLineItem(parent, scene) {
    myStartItem = startItem;
    myEndItem = endItem;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void Arrow::updatePosition()
{
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
}
