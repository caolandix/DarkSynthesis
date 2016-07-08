#include <QtWidgets>
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
    {4, QString("Associated Particle")},
    {5, QString("X-Coord")},
    {6, QString("Y-Coord")}
};

PhysVector::PhysVector(
        CartesianGraph *pParent, PhysParticle *pParticle,
        const QString variable, const QString equation, const QString name, const double magnitude, const bool bDraw, const double angle) :
    QGraphicsLineItem(pParent), PhysBaseItem() {
    m_pDataObj = new PhysVectorDataObj(variable, equation, name, magnitude);

    m_pLabel = new CartesianLabel(name, this, true, bDraw);
    m_pParent = pParent;
    m_Color = Qt::black;
    m_dragIndex = DI_VECTORLINE;
    m_bUseNewThetaAngle = false;
    m_Theta.bAboveAxis = true;
    m_Theta.degrees = angle;
    m_Theta.axisOrientation = AXIS_HORIZ;
    m_pEndParticle = NULL;
    m_bDraw = bDraw;

    if (pParticle)
        StartParticle(pParticle);
    init();
    createConnections();
}

PhysVector::PhysVector(CartesianGraph *pParent, const QString Name, PhysParticle *pStart, PhysParticle *pEnd) :
    QGraphicsLineItem(pParent), PhysBaseItem() {
    m_pLabel = NULL;
    m_pParent = pParent;
    m_pDataObj = new PhysVectorDataObj(Name);
    m_Color = Qt::black;
    m_dragIndex = DI_VECTORLINE;
    m_pDataObj ->Magnitude(50.0);
    m_bUseNewThetaAngle = false;
    m_Theta.bAboveAxis = true;
    m_Theta.degrees = 135.0;
    m_Theta.axisOrientation = AXIS_HORIZ;
    m_pStartParticle = NULL;
    m_pEndParticle = NULL;
    m_pLabel = new CartesianLabel(Name, this);
    m_bDraw = true;

    if (pStart)
        StartParticle(pStart);
    if (pEnd)
        EndParticle(pEnd);
    m_pParent = pParent;
    init();
    createConnections();
}

PhysVector::~PhysVector() {
    if (m_pLabel) {
        delete m_pLabel;
        m_pLabel = NULL;
    }
    if (m_pCoordDisplay) {
        delete m_pCoordDisplay;
        m_pCoordDisplay = NULL;
    }
    m_pStartParticle = NULL;
    m_pEndParticle = NULL;
}

void PhysVector::init() {
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemSendsScenePositionChanges);
    setFlag(ItemIsFocusable);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    double length = sqrt(pow(Magnitude(), 2) + pow(Magnitude(), 2));
    setLine(0 + length, 0 + length, 0, 0);
    m_pCoordDisplay = NULL;
}

void PhysVector::createConnections() {
    connect(this, SIGNAL(reorderObjNav(QGraphicsItem *)), m_pParent, SLOT(onReorderObjNav(QGraphicsItem *)));
    connect(this, SIGNAL(changeItemName(const QString &, const QString &)), m_pParent, SLOT(onChangeItemName(const QString &, const QString &)));
    connect(this, SIGNAL(repaint()), m_pParent, SLOT(onRepaint()));
}

void PhysVector::clearParticle(PhysParticle *pObj) {
    //qDebug("PhysVector::clearParticle()");
    if (m_pStartParticle == pObj)
        m_pStartParticle = NULL;
    if (m_pEndParticle == pObj)
        m_pEndParticle = NULL;
}

PhysVector *PhysVector::copy() {
    PhysVector *pObj = NULL;
    pObj = new PhysVector(static_cast<CartesianGraph *>(parentItem()), Name());
    pObj -> theta(theta());
    pObj -> Magnitude(Magnitude());
    pObj -> StartPoint(m_StartPoint);
    pObj -> EndPoint(m_EndPoint);
    pObj -> currPos(QPointF(m_pDataObj ->xcoord(), m_pDataObj ->ycoord()));
    pObj -> StartParticle(m_pStartParticle);
    pObj -> EndParticle(m_pEndParticle);
    return pObj;
}

void PhysVector::Name(const QString &str) {
    //qDebug("PhysVector::Name()");
    emit changeItemName(m_pDataObj ->Name(), str);
    m_pDataObj ->Name(str);
    m_pLabel ->setPlainText(m_pDataObj ->Name());
}

void PhysVector::StartParticle(PhysParticle *pObj) {
    //qDebug("PhysVector::StartParticle()");
    if (pObj) {
        m_pStartParticle = pObj;
        m_pStartParticle -> addVector(this);
    }
}
void PhysVector::EndParticle(PhysParticle *pObj) {
    //qDebug("PhysVector::EndParticle()");
    if (pObj) {
        m_pEndParticle = pObj;
        m_pEndParticle -> addVector(this);
    }
}

void PhysVector::ThetaAngle(const double val) {
    m_Theta.degrees = val;
    m_bUseNewThetaAngle = true;
    emit repaint();
}

void PhysVector::ThetaAngle(const QString &str) {
    ThetaAngle(str.toDouble());
}

void PhysVector::removeFromParticles() {
    //qDebug("PhysVector::removeFromParticles()");
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
    //qDebug("PhysVector::itemChange()");
    switch (change) {
        case ItemPositionHasChanged:
            break;
        default:
            break;
    };
    return QGraphicsItem::itemChange(change, value);
}

void PhysVector::updatePosition() {
    if (m_pStartParticle && m_pEndParticle) {
        QLineF line(mapFromItem(m_pStartParticle, 0, 0), mapFromItem(m_pEndParticle, 0, 0));
        setLine(line);
    }
    else {
    }
}

void PhysVector::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    /*
    m_StartPoint = event ->scenePos();
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
        m_pDataObj ->updatePos(event -> pos().x(), event -> pos().y());
    }
    event -> setAccepted(true);
    // qDebug("mousePressEvent m_dragIndex: '%d'", m_dragIndex);
    */
    QLineF newLine(m_pLine ->line().p1(), mouseEvent->scenePos());
    m_pLine ->setLine(newLine);

    QGraphicsItem::mousePressEvent(event);
    update();
}

void PhysVector::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    delete m_pCoordDisplay; m_pCoordDisplay = NULL;

    m_EndPoint = event ->scenePos();
    //qDebug("PhysVector::mouseReleaseEvent()");
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
                m_pEndParticle -> removeVector(this);
                m_pEndParticle = NULL;
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
        emit reorderObjNav(static_cast<QGraphicsItem *>(this));
    }
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void PhysVector::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    //qDebug("PhysVector::mouseMoveEvent(): m_dragIndex: '%d'", m_dragIndex);
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
        qreal dx = event -> pos().x() - currPos().x();
        qreal dy = event -> pos().y() - currPos().y();
        pt1.setX(pt1.x() + dx);
        pt1.setY(pt1.y() + dy);
        pt2.setX(pt2.x() + dx);
        pt2.setY(pt2.y() + dy);
        setLine(QLineF(pt1, pt2));
        currPos(event -> pos());
        QGraphicsItem::mouseMoveEvent(event);

        if (event ->buttons() == Qt::LeftButton) {
            QPointF scenePos = line().p2();
            QPointF localPos = event ->pos();
            /*
            qDebug() << QString("Coordinates: (") << QString::number(pos.x()) <<
                        QString(", ") << QString::number(pos.y()) << QString(")");
            */
            QString str = QString("(%1, %2)").arg(QString::number(scenePos.x()), QString::number(scenePos.y()));
            if (!m_pCoordDisplay) {
                m_pCoordDisplay = new CartesianLabel(str, this);
                m_pCoordDisplay ->setPos(localPos.x() + 10, localPos.y() + 10);
            }
            else
                m_pCoordDisplay ->setPlainText(str);
        }
        QGraphicsItem::mouseMoveEvent(event);

    }
    update();
}

QRectF PhysVector::boundingRect() const {
    qreal extra = (pen().width() + 20) / 2.0;
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(), line().p2().y() - line().p1().y())).normalized().adjusted(-extra, -extra, extra, extra);
}

void PhysVector::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    if (!m_bDraw)
        return;
    QPen myPen = pen();
    myPen.setColor(m_Color);
    painter ->setPen(myPen);
    painter ->setBrush(m_Color);

    if (m_pStartParticle && m_pEndParticle) {
        if (m_pStartParticle ->collidesWithItem(m_pEndParticle))
            return;
        QLineF centerLine(m_pStartParticle ->pos(), m_pEndParticle ->pos());
        QPolygonF endPolygon = m_pEndParticle ->polygon();
        QPointF p1 = endPolygon.first() + m_pEndParticle ->pos();
        QPointF p2;
        QPointF intersectPoint;
        QLineF polyLine;
        for (int i = 1; i < endPolygon.count(); ++i) {
            p2 = endPolygon.at(i) + m_pEndParticle ->pos();
            polyLine = QLineF(p1, p2);
            QLineF::IntersectType intersectType = polyLine.intersect(centerLine, &intersectPoint);
            if (intersectType == QLineF::BoundedIntersection)
                break;
            p1 = p2;
        }
        setLine(QLineF(intersectPoint, m_pStartParticle ->pos()));
    }
    if (m_bUseNewThetaAngle) {
        QLineF aLine = line();
        aLine.setAngle(m_Theta.degrees);
        setLine(aLine);
        m_bUseNewThetaAngle = false;
    }
    else {
        double angle = ::acos(line().dx() / line().length());

        if (line().dy() >= 0)
            angle = (PhysConsts::PI * 2) - angle;

        QPointF pt1 = line().p1();
        QPointF pt2 = line().p2();
        QLineF angleLine1(pt2, pt1);
        QLineF angleLine2(pt2, pt1);

        double arrowLen = angleLine1.length() * 0.33;

        // Determine arrow lengths -- no more than 10, no less than 5
        if (arrowLen > 10.0)
            arrowLen = 10.0;
        else if (arrowLen < 5.0)
            arrowLen = 5.0;

        QPointF arrow1P1 = line().p1() + QPointF(sin(angle + PhysConsts::PI / 3) * arrowLen, cos(angle + PhysConsts::PI / 3) * arrowLen);
        QPointF arrow2P1 = line().p1() + QPointF(sin(angle + PhysConsts::PI - PhysConsts::PI / 3) * arrowLen, cos(angle + PhysConsts::PI - PhysConsts::PI / 3) * arrowLen);
        angleLine1.setP1(arrow1P1);
        angleLine2.setP1(arrow2P1);
        angleLine1.setLength(arrowLen);
        angleLine2.setLength(arrowLen);
        painter -> drawLine(angleLine1);
        painter -> drawLine(angleLine2);
        painter -> drawLine(line());

    }
    if (isSelected()) {
        QLineF myLine = line();
        painter ->setPen(QPen(m_Color, 1, Qt::DashLine));
        myLine.translate(0, 4.0);
        painter ->drawLine(myLine);
        myLine.translate(0, -8.0);
        painter ->drawLine(myLine);
    }
}
