#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QPainter>
#include <QPen>
#include <QStyleOption>

#include "cartesianlabel.h"
#include "cartesiangraph.h"
#include "physparticle.h"
#include "physvector.h"
#include "graphwidget.h"

CartesianGraph::CartesianGraph(GraphWidget *graphWidget) : m_pgraphWidget(graphWidget) {
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    int borderWidth = 5;
    m_tickStep = 10;

    m_x_label = new CartesianLabel(QString("x: t(s)"), this);
    m_y_label = new CartesianLabel(QString("y: v(m/s)"), this);
    m_x_label -> setPos(200 + borderWidth, 0);
    m_y_label -> setPos(0, -200 - borderWidth);
}

CartesianGraph::~CartesianGraph() {
    delete m_x_label;
    m_x_label = NULL;
    delete m_y_label;
    m_y_label = NULL;

    m_Vectors.clear();
    m_Particles.clear();
}

void CartesianGraph::createVector() {
    m_Vectors.push_back(new PhysVector(this));
}

void CartesianGraph::createParticle() {
    m_Particles.push_back(new PhysParticle(this));
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
