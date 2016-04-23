#include <QtWidgets>

#include "physbaseitem.h"
#include "cartesianlabel.h"
#include "cartesiangraph.h"
#include "cartesiangraphdataobj.h"
#include "physparticle.h"
#include "physvector.h"
#include "graphwidget.h"
#include "physobjectpropsnavigator.h"

std::map<int, QString> CartesianGraph::m_listEditableProps = {
    {0, QString("X-Axis Label")},
    {1, QString("Y-Axis Label")},
    {2, QString("Axis Tick Increment")},
    {3, QString("X-Axis Extent")},
    {4, QString("Y-Axis Extent")}
};

CartesianGraph::CartesianGraph(GraphWidget *pGraphWidget, const QString &Name, CartesianGraphDataObj *pDataObj, const double x_extent, const double y_extent)  : QGraphicsItem() {
    m_pGraphWidget = pGraphWidget;
    m_pDataObj = (pDataObj) ? pDataObj : new CartesianGraphDataObj(Name);
    m_penWidth = 1;
    m_x_label = new CartesianLabel(QString("x: <Enter label>"), this);
    m_y_label = new CartesianLabel(QString("y: <Enter label>"), this);
    QRectF rcX = m_x_label ->boundingRect();
    QRectF rcY = m_y_label ->boundingRect();
    m_x_label -> setPos(QPointF(m_pDataObj ->xMax(), rcX.height() + 10));
    m_y_label -> setPos(QPointF(-(rcY.width() / 2), m_pDataObj -> yMax() + rcY.height() + 15));

    // Draw the text for the extents -- x-axis
    m_pXMin = new CartesianLabel(QString::number(m_pDataObj -> xMin()), this);
    m_pXMin -> setPos(QPointF(m_pDataObj ->xMin() - 25, -(m_pDataObj ->tickLength())));
    m_pXMax = new CartesianLabel(QString::number(m_pDataObj -> xMax()), this);
    m_pXMax -> setPos(QPointF(m_pDataObj ->xMax(), -(m_pDataObj ->tickLength())));

    // Draw the text for the extents -- y-axis
    m_pYMin = new CartesianLabel(QString::number(m_pDataObj -> yMin()), this);
    m_pYMax = new CartesianLabel(QString::number(m_pDataObj -> yMax()), this);
    m_pYMin -> setPos(QPointF(m_pDataObj ->tickLength() * 2, m_pDataObj ->yMin()));
    m_pYMax -> setPos(QPointF(m_pDataObj ->tickLength() * 2, m_pDataObj ->yMax() + 25));

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
        /*
        m_x_label ->setPos(QPointF(m_pDataObj ->xMax() + m_borderWidth, 0));
        m_y_label ->setPos(QPointF(0, m_pDataObj ->yMax() - m_borderWidth));
        */
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
        /*
        m_x_label ->setPos(QPointF(m_pDataObj ->xMax() + m_borderWidth, 0));
        m_y_label ->setPos(QPointF(0, m_pDataObj ->yMax() - m_borderWidth));
        */
    }
    return *this;
}

void CartesianGraph::init() {
    m_pDataObj -> init();
}

void CartesianGraph::createConnections() {
    connect(this, SIGNAL(reorderObjNav(QGraphicsItem *)),
        m_pGraphWidget, SLOT(onReorderObjNav(QGraphicsItem *)));

    connect(this, SIGNAL(changeItemName(const QString &, const QString &)),
        m_pGraphWidget, SLOT(onChangeItemName(const QString &, const QString &)));

    connect(this, SIGNAL(repaint()),
        m_pGraphWidget, SLOT(onRepaint()));


    PhysObjectPropsNavigator *pView = m_pGraphWidget ->MainWindow() -> getPhysObjPropsNavigator();
    connect(this, SIGNAL(changeItemPos(QGraphicsItem *, const QPointF &)),
        pView, SLOT(onChangeItemPos(QGraphicsItem *, const QPointF &)));
}

void CartesianGraph::updateItemPos(QGraphicsItem *pObj, const QPointF &pos) {
    emit changeItemPos(pObj, pos);
}


void CartesianGraph::onChangeItemName(const QString &strOld, const QString &strNew) {
    emit changeItemName(strOld, strNew);
}

void CartesianGraph::onRepaint() {
    qDebug("CartesianGraph::onRepaint()");
    emit repaint();
}

void CartesianGraph::changeLabelPositions() {
    m_x_label -> setPos(QPointF(m_pDataObj ->xMax(), m_x_label ->boundingRect().height() + 10));
    m_y_label -> setPos(QPointF(-(m_y_label ->boundingRect().width() / 2), m_pDataObj -> yMax() + m_y_label ->boundingRect().height() + 15));

    // Draw the text for the extents -- x-axis
    m_pXMin -> setPos(QPointF(m_pDataObj ->xMin() - 25, -(m_pDataObj ->tickLength())));
    m_pXMax -> setPos(QPointF(m_pDataObj ->xMax(), -(m_pDataObj ->tickLength())));

    // Draw the text for the extents -- y-axis
    m_pYMin -> setPos(QPointF(m_pDataObj ->tickLength() * 2, m_pDataObj ->yMin()));
    m_pYMax -> setPos(QPointF(m_pDataObj ->tickLength() * 2, m_pDataObj ->yMax() + 25));
}


void CartesianGraph::XExtent(const QString &str) {
    m_pDataObj -> xMax(str.toDouble());
    m_pDataObj -> xMin(-(str.toDouble()));
    m_pXMax ->setPlainText(QString::number(m_pDataObj -> xMax()));
    m_pXMin ->setPlainText(QString::number(m_pDataObj -> xMin()));
    changeLabelPositions();
    prepareGeometryChange();
}

void CartesianGraph::YExtent(const QString &str) {
    m_pDataObj -> yMax(str.toDouble());
    m_pDataObj -> yMin(-(str.toDouble()));

    m_pYMin ->setPlainText(QString::number(m_pDataObj -> yMin()));
    m_pYMax ->setPlainText(QString::number(m_pDataObj -> yMax()));
    changeLabelPositions();
    prepareGeometryChange();
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
    qreal extra = (m_penWidth + 20) / 2.0;
    return QRectF(QPointF(m_pDataObj ->xMax(), m_pDataObj ->yMax()), QPointF(m_pDataObj ->xMin(), m_pDataObj ->yMin())).normalized().adjusted(-extra, -extra, extra, extra);
}

void CartesianGraph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter -> setBrush(Qt::darkGray);
    painter -> setPen(QPen(Qt::black, m_penWidth));

    QRectF rc = boundingRect();
    QPointF pty1(0, rc.top());
    QPointF pty2(0, rc.bottom());
    QPointF ptx1(rc.right(), 0);
    QPointF ptx2(rc.left(), 0);
    painter ->drawLine(pty1, pty2);   // vertical axis
    painter ->drawLine(ptx1, ptx2);   // horiz axis

    // Draw the tickmarks
    int tickDrawLength = m_pDataObj -> tickLength();
    double tickStep = m_pDataObj -> tickStep();

    double width = abs(m_pDataObj ->xMax()) + abs(m_pDataObj ->xMin());
    double height = abs(m_pDataObj ->yMax()) + abs(m_pDataObj ->yMin());

    // Figure out the number of ticks -- Not based on rectangle, but based on the wanted extents
    int numTicksX = width / tickStep;
    int numTicksY = height / tickStep;

    // draw horizontal tick marks
    QPointF currPosPositive(0, 0), currPosNegative(0, 0);
    double roundedTickDrawLength = round(tickDrawLength / 2);
    for (int i = 1; i < numTicksX; i++) {
        currPosPositive.setX(tickStep * i);
        currPosNegative.setX(-tickStep * i);
        painter -> drawLine(QLineF(QPointF(currPosPositive.x(), roundedTickDrawLength), QPointF(currPosPositive.x(), -roundedTickDrawLength)));
        painter -> drawLine(QLineF(QPointF(currPosNegative.x(), roundedTickDrawLength), QPointF(currPosNegative.x(), -roundedTickDrawLength)));
    }

    for (int i = 1; i < numTicksY; i++) {
        currPosPositive.setY(tickStep * i);
        currPosNegative.setY(-tickStep * i);
        painter -> drawLine(QLineF(QPointF(-roundedTickDrawLength, currPosPositive.y()), QPointF(roundedTickDrawLength, currPosPositive.y())));
        painter -> drawLine(QLineF(QPointF(-roundedTickDrawLength, currPosNegative.y()), QPointF(roundedTickDrawLength, currPosNegative.y())));
    }
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
