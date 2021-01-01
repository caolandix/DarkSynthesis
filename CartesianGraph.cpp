#include <QtWidgets>

#include "physbaseitem.h"
#include "cartesianlabel.h"
#include "cartesiangraph.h"
#include "cartesiangraphdataobj.h"
#include "physparticle.h"
#include "physvector.h"
#include "graphwidget.h"

std::map<int, QString> CartesianGraph::m_listEditableProps = {
    {0, QString("X-Axis Label")},
    {1, QString("Y-Axis Label")},
    {2, QString("Axis Tick Increment")},
    {3, QString("X-Axis Extent")},
    {4, QString("Y-Axis Extent")}
};

CartesianGraph::CartesianGraph(GraphWidget *pGraphWidget, const QString &Name, CartesianGraphDataObj *pDataObj)  : QGraphicsItem() {
    m_pGraphWidget = pGraphWidget;
    m_pDataObj = (pDataObj) ? pDataObj : new CartesianGraphDataObj(Name);
    m_borderWidth = 5;

    m_x_label = new CartesianLabel(QString("x: <Enter label>"), this);
    m_y_label = new CartesianLabel(QString("y: <Enter label>"), this);

    QRectF rcXLabel = m_x_label->boundingRect();
    QRectF rcYLabel = m_y_label->boundingRect();

    m_x_label -> setPos(QPointF(((m_pGraphWidget ->rect().width() / 2) + m_borderWidth) - rcXLabel.width(), 0));
    m_y_label -> setPos(QPointF(0, (m_pGraphWidget ->rect().height() / 2) + m_borderWidth));

    // Draw the text for the extents
    QRectF rc = boundingRect();
    m_pXMinLabel = new CartesianLabel(QString::number(m_pDataObj -> xMin()), this);
    m_pXMaxLabel = new CartesianLabel(QString::number(m_pDataObj -> xMax()), this);
    m_pYMinLabel = new CartesianLabel(QString::number(m_pDataObj -> yMin()), this);
    m_pYMaxLabel = new CartesianLabel(QString::number(m_pDataObj -> yMax()), this);
    m_pXMinLabel -> setPos(QPointF(rc.x() - (m_pXMinLabel -> boundingRect().width() / 2), -(m_pXMinLabel -> boundingRect().height() / 2)));

    QRect viewRect = m_pGraphWidget ->rect();

    m_pXMaxLabel -> setPos(QPointF((viewRect.width() / 2) - (m_pXMaxLabel -> boundingRect().width() / 2), -(m_pXMaxLabel -> boundingRect().height() / 2)));
    m_pYMinLabel -> setPos(QPointF(m_pYMinLabel -> boundingRect().width() / 2, rc.y() + (m_pYMinLabel -> boundingRect().height() / 2)));
    m_pYMaxLabel -> setPos(QPointF(m_pYMaxLabel -> boundingRect().width() / 2, (viewRect.height() / 2) + (m_pYMaxLabel -> boundingRect().height() / 2)));
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    createConnections();
}

CartesianGraph::CartesianGraph(const CartesianGraph &obj) : QGraphicsItem() {
    if (&obj != this) {
        if (m_pDataObj)
            delete m_pDataObj;
        m_pDataObj = new CartesianGraphDataObj(obj.DataObj());
        m_pGraphWidget = obj.graphWidget();
        delete m_x_label;
        delete m_y_label;
        m_x_label = new CartesianLabel(obj.XAxisLabel(), this);
        m_y_label = new CartesianLabel(obj.YAxisLabel(), this);

        m_x_label ->setPos(QPointF((m_pGraphWidget ->rect().width() / 2) + m_borderWidth, 0));
        m_y_label ->setPos(QPointF(0, -(m_pGraphWidget ->rect().height() / 2) - m_borderWidth));
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
        m_x_label ->setPos(QPointF((m_pGraphWidget ->rect().width() / 2) + m_borderWidth, 0));
        m_y_label ->setPos(QPointF(0, -(m_pGraphWidget ->rect().height() / 2) - m_borderWidth));
    }
    return *this;
}

void CartesianGraph::init() {
    m_pDataObj -> init();
}

void CartesianGraph::createConnections() {
    connect(this, SIGNAL(reorderObjNav(QGraphicsItem *)), m_pGraphWidget, SLOT(onReorderObjNav(QGraphicsItem *)));
    connect(this, SIGNAL(changeItemName(const QString &, const QString &)), m_pGraphWidget, SLOT(onChangeItemName(const QString &, const QString &)));
    connect(this, SIGNAL(repaint()), m_pGraphWidget, SLOT(onRepaint()));
}

void CartesianGraph::onChangeItemName(const QString &strOld, const QString &strNew) {
    emit changeItemName(strOld, strNew);
}

void CartesianGraph::onRepaint() {
    qDebug("CartesianGraph::onRepaint()");
    emit repaint();
}

void CartesianGraph::XExtent(const QString &str) {
    m_pDataObj -> xMax(str.toDouble());
    m_pDataObj -> xMin(-(str.toDouble()));
    m_pXMaxLabel ->setPlainText(QString::number(m_pDataObj -> xMax()));
    m_pXMinLabel ->setPlainText(QString::number(m_pDataObj -> xMin()));
}

void CartesianGraph::YExtent(const QString &str) {
    m_pDataObj -> yMax(str.toDouble());
    m_pDataObj -> yMin(-(str.toDouble()));

    m_pYMinLabel ->setPlainText(QString::number(m_pDataObj -> yMin()));
    m_pYMaxLabel ->setPlainText(QString::number(m_pDataObj -> yMax()));
}


CartesianGraph *CartesianGraph::copy() {
    CartesianGraph *pObj = NULL;

    return pObj;
}

void CartesianGraph::onReorderObjNav(QGraphicsItem *pObj) {
    qDebug("CartesianGraph::onReorderObjNav");
    emit reorderObjNav(pObj);
}

void CartesianGraph::onPropChange(const QString &str) {
    qDebug("CartesianGraph::onPropChange(): updating info");
    update();
}

QRectF CartesianGraph::boundingRect() const {
    return QRectF(
                -(m_pGraphWidget ->rect().width() / 2),
                -(m_pGraphWidget ->rect().height() / 2),
                m_pGraphWidget ->rect().width(),
                m_pGraphWidget ->rect().height());
}

QPainterPath CartesianGraph::shape() const {

    QPainterPath path;
    // path.addEllipse(-10, -10, 20, 20);
    return path;
}

void CartesianGraph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *pWidget) {
    QRectF rc = m_pGraphWidget ->rect();

    painter -> setPen(Qt::NoPen);
    painter -> setBrush(Qt::darkGray);
    painter -> setPen(QPen(Qt::black, 2));
    painter -> drawLine(QLine(0, rc.height() / 2, 0, -(rc.height() / 2)));    // vertical axis
    painter -> drawLine(QLine(-(rc.width() / 2), 0, rc.width() / 2, 0));    // horizontal axis

    // Draw the tickmarks
    int tickDrawLength = 5;
    double tickStep = m_pDataObj -> tickStep();

    // Figure out the number of ticks
    int numTicksX = (m_pDataObj -> xMax() / tickStep) * 2;    // *2 because of both sides +/- sides to axis
    int numTicksY = (m_pDataObj -> yMax() / tickStep) * 2;

    // The width of coordinate space between ticks - x-axis
    int pxPerTickX = rc.width() / numTicksX;

    // The width of coordinate space between ticks - y-axis
    int pxPerTickY = rc.height() / numTicksY;

    QLine arrEndLines[4];

    // Do vertical lines... Draw center to right, then center to left
    int i = 1, j = 1;
    while (1) {
        if (i >= numTicksX) {
            arrEndLines[0] = QLine((pxPerTickX * numTicksX) / 2, tickDrawLength, (pxPerTickX * numTicksX) / 2, -tickDrawLength);
            arrEndLines[1] = QLine(-((pxPerTickX * numTicksX) / 2), tickDrawLength, -((pxPerTickX * numTicksX) / 2), -tickDrawLength);
            break;
        }
        painter -> drawLine(QLine(pxPerTickX * i, tickDrawLength, pxPerTickX * i, -tickDrawLength));
        painter -> drawLine(QLine(-(pxPerTickX * i), tickDrawLength, -(pxPerTickX * i), -tickDrawLength));
        i++;
    }

    // Do Horizontal lines... Draw left to right
    while (1) {
        if (j >= numTicksY) {
            arrEndLines[2] = QLine(tickDrawLength, (pxPerTickY * numTicksY) / 2, -tickDrawLength, (pxPerTickY * numTicksY) / 2);
            arrEndLines[3] = QLine(tickDrawLength, -((pxPerTickY * numTicksY) / 2), -tickDrawLength, -((pxPerTickY * numTicksY) / 2));
            break;
        }
        painter -> drawLine(QLine(tickDrawLength, pxPerTickY * j, -tickDrawLength, pxPerTickY * j));
        painter -> drawLine(QLine(tickDrawLength, -(pxPerTickY * j), -tickDrawLength, -(pxPerTickY * j)));
        j++;
    }

    // Draw the end ticks of axis' along with the extent text
    painter -> setPen(QPen(Qt::red, 4));
    for (int i = 0; i < 4; i++)
        painter -> drawLine(arrEndLines[i]);
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
    qDebug() << "CartesianGraph::mousePressEvent";
    update();
    QGraphicsItem::mousePressEvent(event);
}

void CartesianGraph::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "CartesianGraph::mouseMoveEvent";
    if (!m_pCoordLabel) {
        m_pCoordLabel = new CartesianLabel(QString("Mouse move (%1,%2)").arg(event->pos().x()).arg(event->pos().y()), this);
    }

    update();
    QGraphicsItem::mouseMoveEvent(event);
}

void CartesianGraph::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "CartesianGraph::mouseReleaseEvent";
    if (m_pCoordLabel) {
        delete m_pCoordLabel;
        m_pCoordLabel = NULL;
    }

    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
