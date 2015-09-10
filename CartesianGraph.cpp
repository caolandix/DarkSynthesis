#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QPainter>
#include <QPen>
#include <QStyleOption>

#include "cartesianlabel.h"
#include "cartesiangraph.h"
#include "cartesiangraphdataobj.h"
#include "physparticle.h"
#include "physvector.h"
#include "graphwidget.h"

CartesianGraph::CartesianGraph() {
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    m_borderWidth = 5;
    m_x_label = new CartesianLabel(QString("x: t(s)"), this);
    m_y_label = new CartesianLabel(QString("y: v(m/s)"), this);
    m_x_label ->setPos(QPointF(200 + m_borderWidth, 0));
    m_y_label ->setPos(QPointF(0, -200 - m_borderWidth));

}


//CartesianGraph::CartesianGraph(const CartesianGraph &obj) {
//}

CartesianGraph::CartesianGraph(GraphWidget *pGraphWidget, CartesianGraphDataObj *pDataObj) : CartesianGraph() {
    m_pGraphWidget = pGraphWidget;

    if (pDataObj)
        m_pDataObj = pDataObj;
    else
        m_pDataObj = new CartesianGraphDataObj();
}

CartesianGraph::~CartesianGraph() {
    delete m_pDataObj;
    m_pDataObj = NULL;
    m_pGraphWidget = NULL;
    delete m_x_label; m_x_label = NULL;
    delete m_y_label; m_y_label = NULL;
}


// operator overloads
CartesianGraph &CartesianGraph::operator=(const CartesianGraph &obj) {
    // check to see if we're assigning this to itself
    if (&obj != this) {
        if (m_pDataObj)
            delete m_pDataObj;
        m_pDataObj = new CartesianGraphDataObj(obj.DataObj());
        m_pGraphWidget = obj.graphWidget();
        delete m_x_label;
        delete m_y_label;
        m_x_label = new CartesianLabel(obj.XAxisLabel(), this);
        m_y_label = new CartesianLabel(obj.YAxisLabel(), this);
        m_x_label ->setPos(QPointF(200 + m_borderWidth, 0));
        m_y_label ->setPos(QPointF(0, -200 - m_borderWidth));
    }
    return *this;
}

void CartesianGraph::createVector() {
    m_pDataObj -> AddVector(new PhysVector(this));
}

void CartesianGraph::createParticle() {
    m_pDataObj -> AddParticle(new PhysParticle(this));
}

QRectF CartesianGraph::boundingRect() const {
    return QRectF(-200, -200, 400, 400);
}

QPainterPath CartesianGraph::shape() const {
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void CartesianGraph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter -> setPen(Qt::NoPen);
    painter -> setBrush(Qt::darkGray);
    painter -> setPen(QPen(Qt::black, 2));

    painter -> drawLine(QLine(0, 200, 0, -200));
    painter -> drawLine(QLine(-200, 0, 200, 0));
}

QVariant CartesianGraph::itemChange(GraphicsItemChange change, const QVariant &value) {
    switch (change) {
        case ItemPositionHasChanged:
            /*
             foreach (Edge *edge, edgeList)
                edge -> adjust();
            m_pgraphWidget -> itemMoved();
            */
            break;
        default:
            break;
    };
    return QGraphicsItem::itemChange(change, value);
}

void CartesianGraph::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mousePressEvent(event);
}

void CartesianGraph::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
