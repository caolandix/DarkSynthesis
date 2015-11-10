#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QPainter>
#include <QPen>
#include <QStyleOption>
#include <QTextStream>

#include "physbaseitem.h"
#include "cartesianlabel.h"
#include "cartesiangraph.h"
#include "cartesiangraphdataobj.h"
#include "physparticle.h"
#include "physvector.h"
#include "graphwidget.h"

CartesianGraph::CartesianGraph(GraphWidget *pGraphWidget, const QString &Name, CartesianGraphDataObj *pDataObj) {
    m_pGraphWidget = pGraphWidget;
    m_pDataObj = (pDataObj) ? pDataObj : new CartesianGraphDataObj();
    m_borderWidth = 5;
    m_Name = Name;
    m_x_label = new CartesianLabel(QString("x: t(s)"), this);
    m_y_label = new CartesianLabel(QString("y: v(m/s)"), this);
    m_x_label -> setPos(QPointF(200 + m_borderWidth, 0));
    m_y_label -> setPos(QPointF(0, 200 + m_borderWidth));

    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

CartesianGraph::CartesianGraph(const CartesianGraph &obj) {
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
        // m_pDataObj = new CartesianGraphDataObj(obj.DataObj());
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
    painter -> drawLine(QLine(0, 200, 0, -200));    // vertical axis
    painter -> drawLine(QLine(-200, 0, 200, 0));    // horizontal axis

    CartesianGraphDataObj *pDataObj = DataObj();
    QRectF rc = boundingRect();
    int tickDrawLength = 5;

    // Figure out the number of ticks
    int numTicksX = (pDataObj -> xMax() / tickStep) * 2;    // *2 because of both sides +/- sides to axis
    int numTicksY = (pDataObj -> yMax() / tickStep) * 2;

    // The width of coordinate space between ticks - x-axis
    int pxPerTickX = rc.width() / numTicksX;

    // The width of coordinate space between ticks - y-axis
    int pxPerTickY = rc.width() / numTicksY;

    // Do vertical lines... Draw left to right
    int axisStartPoint = rc.x();
    for (int i = 1; i < numTicksX; i++) {
        if (axisStartPoint + pxPerTickX * i == 0)
            continue;
        painter -> drawLine(QLine(axisStartPoint + pxPerTickX * i, tickDrawLength, axisStartPoint + pxPerTickX * i, -tickDrawLength));
    }

    // Do Horizontal lines... Draw left to right
    axisStartPoint = rc.y();
    for (int j = 1; j < numTicksY; j++) {
        if (axisStartPoint + pxPerTickY * j == 0)
            continue;
        painter -> drawLine(QLine(tickDrawLength, axisStartPoint + pxPerTickY * j, -tickDrawLength, axisStartPoint + pxPerTickY * j));
    }

    // Draw the end ticks of axis' along with the extent text
    painter -> setPen(QPen(Qt::black, 4));

    // x-axis
    painter ->drawLine(QLine(rc.x(), tickDrawLength + 5, rc.x(), -tickDrawLength - 5));
    painter ->drawLine(QLine(rc.width(), tickDrawLength + 5, rc.width(), -tickDrawLength - 5));

    // y-axis
    painter -> drawLine(QLine(tickDrawLength + 5, rc.y(), -tickDrawLength - 5, rc.y()));
    painter -> drawLine(QLine(tickDrawLength + 5, rc.height(), -tickDrawLength - 5, rc.height()));
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
