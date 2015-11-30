#include <QPainter>
#include <QString>
#include <QAction>
#include <QMenu>
#include <math.h>
#include <map>

#include "physbaseitem.h"
#include "physvector.h"
#include "physvectordataobj.h"
#include "physparticle.h"
#include "cartesianlabel.h"
#include "cartesiangraph.h"
#include "physscience.h"

const map<PhysVector::AxisOrientation, QString> PhysVector::createMap() {
    std::map<PhysVector::AxisOrientation, QString> mMap;
    mMap.insert(std::make_pair(AXIS_HORIZ, QString("Horizontal")));
    mMap.insert(std::make_pair(AXIS_VERT, QString("Vertical")) );
    return mMap;
}
const std::map<PhysVector::AxisOrientation, QString> PhysVector::m_OrientationLabelMap = PhysVector::createMap();

std::map<int, QString> PhysVector::m_listEditableProps = {
    {0, QString("Name")},
    {1, QString("Magnitude")},
    {2, QString("Theta - Angle")},
    {3, QString("Theta - Axis Orientation")},
    {4, QString("Associated Particle")}
};

PhysVector::PhysVector(CartesianGraph *pParent, const QPointF &startPos, const QString &Label, PhysParticle *pStart, PhysParticle *pEnd, QGraphicsScene *scene) :
    QGraphicsLineItem(pParent), PhysBaseItem() {
    m_pLabel = NULL;
    m_pParent = NULL;
    m_Color = Qt::black;
    m_arrowSize = 20;
    m_dragIndex = DI_VECTORLINE;


    m_magnitude = 50.0;
    m_Theta.bAboveAxis = true;
    m_Theta.degrees = 45.0;
    m_Theta.axisOrientation = AXIS_HORIZ;
    m_pStartParticle = NULL;
    m_pEndParticle = NULL;
    m_pLabel = new CartesianLabel(this);
    Name(Label);

    if (pStart)
        StartParticle(pStart);
    if (pEnd)
        EndParticle(pEnd);
    m_pParent = pParent;

    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemSendsScenePositionChanges);
    setFlag(ItemIsFocusable);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setLine(0 + m_magnitude, 0 + m_magnitude, 0, 0);
}

PhysVector::~PhysVector() {
    if (m_pLabel) {
        delete m_pLabel;
        m_pLabel = NULL;
    }
    m_pStartParticle = NULL;
    m_pEndParticle = NULL;
}

void PhysVector::clearParticle(PhysParticle *pObj) {
    qDebug("PhysVector::clearParticle()");
    if (m_pStartParticle == pObj)
        m_pStartParticle = NULL;
    if (m_pEndParticle == pObj)
        m_pEndParticle = NULL;
}

void PhysVector::init() {
    qDebug("PhysVector::init()");

    m_magnitude = 50.0;
    removeFromParticles();
    m_Theta.bAboveAxis = true;
    m_Theta.degrees = 45.0;
    m_Theta.axisOrientation = AXIS_HORIZ;
    setLine(0 + m_magnitude, 0 + m_magnitude, 0, 0);
}

PhysVector *PhysVector::copy() {
    PhysVector *pObj = NULL;
    pObj = new PhysVector(static_cast<CartesianGraph *>(parentItem()), pos(), Name());
    pObj -> theta(theta());
    pObj -> Magnitude(m_magnitude);
    pObj -> StartPoint(m_StartPoint);
    pObj -> EndPoint(m_EndPoint);
    pObj -> CurrPos(m_currPos);
    pObj ->StartParticle(m_pStartParticle);
    pObj ->EndParticle(m_pEndParticle);
    return pObj;
}

void PhysVector::Name(const QString &str) {
    qDebug("PhysVector::Name()");
    m_Name = str;
    QString formattedLabel;
    formattedLabel.sprintf("%s: (%.6f, @=%3.2f", m_Name.toStdString().c_str(), m_magnitude, m_Theta.degrees);
    m_pLabel ->setPlainText(formattedLabel);
}

void PhysVector::StartParticle(PhysParticle *pObj) {
    qDebug("PhysVector::StartParticle()");
    if (pObj) {
        m_pStartParticle = pObj;
        m_pStartParticle -> addVector(this);
    }
}
void PhysVector::EndParticle(PhysParticle *pObj) {
    qDebug("PhysVector::EndParticle()");
    if (pObj) {
        m_pEndParticle = pObj;
        m_pEndParticle -> addVector(this);
    }
}

void PhysVector::removeFromParticles() {
    qDebug("PhysVector::removeFromParticles()");
    if (m_pStartParticle) {
        m_pStartParticle ->removeVector(this);
        m_pStartParticle = NULL;
    }
    if (m_pEndParticle) {
        m_pEndParticle ->removeVector(this);
        m_pEndParticle = NULL;
    }
}

QVariant PhysVector::itemChange(GraphicsItemChange change, const QVariant &value) {
    qDebug("PhysVector::itemChange()");
    switch (change) {
        case ItemPositionHasChanged:
            break;
        default:
            break;
    };
    return QGraphicsItem::itemChange(change, value);
}

void PhysVector::adjust() {
    qDebug("PhysVector::adjust()");
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
            QPointF pt1 = my_line.p1(), pt2 = my_line.p2();
            prepareGeometryChange();
            if (length > qreal(20.0)) {
                QPointF edgeOffset((my_line.dx() * 10) / length, (my_line.dy() * 10) / length);
                m_StartPoint = pt1 + edgeOffset;
                m_EndPoint = pt2 - edgeOffset;
            }
            else {
                m_StartPoint = pt1;
                m_EndPoint = pt2;
            }
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
    double drawAngle, realAngle, Theta;

    realAngle = ::acos(aLine.dx() / aLine.length());
    if (m_Theta.axisOrientation == AXIS_HORIZ) {
        QPointF currCoordP1(aLine.p1().x(), aLine.p1().y());
        Theta = (::atan(aLine.dy() / aLine.dx()) * (180 / PhysConsts::PI));
        qDebug("Line (x, y): (%f, %f)", currCoordP1.x(), currCoordP1.y());

        // If we're in the Quad I (+x, +y) or Quad II (-x, +y)
        if ((currCoordP1.x() >= 0 && currCoordP1.y() >= 0) || (currCoordP1.x() < 0 && currCoordP1.y() >= 0)) {
            if (Theta < 0)
                Theta = -Theta;
        }

        // Quad III (-x, -y) or Quad IV (+x, -y)
        else if ((currCoordP1.x() < 0 && currCoordP1.y() < 0) || (currCoordP1.x() >= 0 && currCoordP1.y() < 0)) {
            if (Theta > 0)
                Theta = -Theta;
        }
    }
    m_Theta.degrees = Theta;

    drawAngle = (aLine.dy() >= 0) ? (PhysConsts::PI * 2) - realAngle : (PhysConsts::PI * 2) + realAngle;
    arrowP1 = aLine.p1() + QPointF(sin(drawAngle + PhysConsts::PI / 3) * m_arrowSize, cos(drawAngle + PhysConsts::PI / 3) * m_arrowSize);
    arrowP2 = aLine.p1() + QPointF(sin(drawAngle + PhysConsts::PI - PhysConsts::PI / 3) * m_arrowSize, cos(drawAngle + PhysConsts::PI - PhysConsts::PI / 3) * m_arrowSize);
    m_arrowHead.clear();
    m_arrowHead << line().p1() << arrowP1 << arrowP2;
    pPainter -> drawLine(aLine);
    pPainter -> drawPolygon(m_arrowHead);

    QString formattedLabel;
    m_pLabel -> setPlainText(formattedLabel.sprintf("%s: (%.6f, @=%3.2f)", m_Name.toStdString().c_str(), m_magnitude, Theta));
    QPainterPath tmpPath;
    QBrush brush(m_Color);
    tmpPath.addPolygon(m_arrowHead);
    pPainter -> fillPath(tmpPath, brush);
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
    event -> setAccepted(true);
    // qDebug("mousePressEvent m_dragIndex: '%d'", m_dragIndex);
    update();
    QGraphicsItem::mousePressEvent(event);
}

void PhysVector::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    qDebug("PhysVector::mouseReleaseEvent()");
    if (m_dragIndex == DI_VECTORLINE) {
        event -> pos();
    }
    else
        m_dragIndex = DI_VECTORLINE;

    // Now check to see if one of the end points collides with a particle. If so, attach to it
    QList<PhysParticle *> particles = m_pParent -> Particles();
    QPointF pt1 = line().p1();
    QPointF pt2 = line().p2();

    // Check to see if the currently assigned particles are still intersected
    if (m_pStartParticle || m_pEndParticle) {
        QRectF rcPart;
        if (m_pStartParticle) {
            if (!collidesWithItem(m_pStartParticle)) {
                rcPart = m_pStartParticle -> boundingRect();
                QPointF ptPart = m_pStartParticle ->pos();
                QRectF rcLocalPart(ptPart.x() + rcPart.topLeft().x(), ptPart.y() + rcPart.topLeft().y(),
                                   ptPart.x() + rcPart.bottomRight().x(), ptPart.y() + rcPart.bottomRight().y());

                if (!rcLocalPart.contains(pt1)) {
                    //  No longer intersecting the start point so disconnect from the particle
                    m_pStartParticle -> removeVector(this);
                    m_pStartParticle = NULL;
                }
            }
        }

        // Handle the end point particle
        else {
            if (!collidesWithItem(m_pEndParticle)) {
                rcPart = m_pEndParticle -> boundingRect();
                if (!rcPart.contains(pt2)) {
                        //  No longer intersecting the end point so disconnect from the particle
                        m_pEndParticle -> removeVector(this);
                        m_pEndParticle = NULL;
                    }
                }
        }
    }
    for (QList<PhysParticle *>::Iterator iter = particles.begin(); iter != particles.end(); iter++) {
        PhysParticle *pParticle = *iter;

        if (collidesWithItem(pParticle)) {

            // Verify that the end points are the only things intersecting
            QRectF rcPart = pParticle -> boundingRect();
            if (rcPart.contains(pt1)) {
                if (m_pStartParticle) {
                    m_pStartParticle -> removeVector(this);
                }
                m_pStartParticle = pParticle;
                pParticle -> addVector(this);
            }
            if (rcPart.contains(pt2)) {
                if (m_pEndParticle) {
                    m_pEndParticle -> removeVector(this);
                }
                m_pEndParticle = pParticle;
                pParticle -> addVector(this);
            }
        }
    }
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void PhysVector::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    qDebug("PhysVector::mouseMoveEvent(): m_dragIndex: '%d'", m_dragIndex);
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
