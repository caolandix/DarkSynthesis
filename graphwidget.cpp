#include <math.h>
#include <QtWidgets>

#include "graphwidget.h"
#include "cartesiangraph.h"
#include "physbaseitem.h"

GraphWidget::GraphWidget(PhysGraphicsScene *pScene, QWidget *pParent) : QGraphicsView(pParent) {
    m_pCartGraph = NULL;
    m_actNewVector = NULL;
    m_actNewParticle = NULL;
    m_actVectorProps = NULL;
    m_actParticleProps = NULL;
    m_pInfoLabel = NULL;
    m_pScene = NULL;

    setContextMenuPolicy(Qt::CustomContextMenu);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(FullViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);
    setWindowTitle(tr("Cartesian Graph"));
    // Setting the matrix rotates the drawing area to be a normal cartesian plane. Unfortunately
    // it also means that the original drawing has to be tweaked
    QTransform trfrm;
    trfrm.scale(1.0, -1.0);
    setTransform(trfrm);

    // Creation of the cartesian graph sitting in the center of the GraphWidget. It is used to
    // show where the vector drawing occurs and the scales defined.
    // m_pScene -> setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(m_pScene = pScene);

    // Create the actions used in the context menus
    createActions();

    m_pInfoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to invoke a context menu</i>"));
}

void GraphWidget::onChangeItemName(const QString &strOld, const QString &strNew) {
    emit changeItemName(strOld, strNew);
}

void GraphWidget::onRepaint() {
    // qDebug("GraphWidget::onRepaint()");
    repaint();
}

void GraphWidget::onReorderObjNav(QGraphicsItem *pObj) {
    // qDebug("GraphWidget::onReorderObjNav");
    emit reorderObjNav(pObj);
}

void GraphWidget::createCartesianGraph() {

    // Create the object
    m_pCartGraph = new CartesianGraph(this);
    m_pCartGraph -> setPos(0, 0);
    m_pScene -> addItem(m_pCartGraph);
    emit createObj(m_pCartGraph);
    emit cartesianGraphCreated(m_pCartGraph ->DataObj());
}

PhysVector *GraphWidget::createVector(const QPointF &startPos) {
    //qDebug("GraphWidget::createVector()");
    QGraphicsScene *pScene = scene();
    PhysVector *pObj = new PhysVector(m_pCartGraph, QString("Vector-%1").arg(m_pCartGraph -> DataObj() -> Vectors().length()));

    m_pCartGraph -> DataObj() -> AddVector(pObj);
    pScene -> addItem(pObj);
    emit createObj(pObj);
    return pObj;
}

PhysParticle *GraphWidget::createParticle(const QPointF &startPos) {
    //qDebug("GraphWidget::createParticle");
    QGraphicsScene *pScene = scene();
    PhysParticle *pObj = new PhysParticle(m_pCartGraph, startPos, QString("Particle-%1").arg(m_pCartGraph ->Particles().length()));

    m_pCartGraph -> AddParticle(pObj);
    pScene -> addItem(pObj);
    emit createObj(pObj);
    return pObj;
}

void GraphWidget::createVector() {
    //qDebug("GraphWidget::createVector");
    m_pInfoLabel -> setText(tr("Created a new Vector"));
    createVector(m_currClickPos);
}

void GraphWidget::createParticle() {
    //qDebug("GraphWidget::createParticle");
    m_pInfoLabel -> setText(tr("Created a new Particle"));
    createParticle(m_currClickPos);
}

void GraphWidget::onClonePhysObj(QGraphicsItem *pNewObj) {
    //qDebug("GraphWidget::onClonePhysObj()");
    if (!pNewObj)
        qDebug("GraphWidget::onClonePhysObj(): pNewObj is NULL");
    else {
        switch (pNewObj ->type()) {
        case PhysBaseItem::VectorType:
            m_pCartGraph -> DataObj() -> AddVector(static_cast<PhysVector *>(pNewObj));
            break;
        case PhysBaseItem::ParticleType:
            m_pCartGraph -> DataObj() -> AddParticle(static_cast<PhysParticle *>(pNewObj));
            break;
        case PhysBaseItem::CartesianGraphType:
            break;
        default:
            qDebug("PhysObjectNavigator::onClonePhysObj: not a supported object type: %d", pNewObj -> type());
            break;
        }

        pNewObj -> setParentItem(m_pCartGraph);
        scene() -> addItem(pNewObj);
        emit createObj(pNewObj);
    }
}

void GraphWidget::onRemovePhysObj(QGraphicsItem *pObj) {
    //qDebug("GraphWidget::onRemovePhysObj()");
    if (!pObj)
        qDebug("GraphWidget::onRemovePhysObj(): pNewObj is NULL");
    else {
        switch (pObj ->type()) {
        case PhysBaseItem::VectorType:
            //m_pCartGraph -> DataObj() -> removeVector(static_cast<PhysVector *>(pObj));
            break;
        case PhysBaseItem::ParticleType:
            //m_pCartGraph -> DataObj() -> removeParticle(static_cast<PhysParticle *>(pObj));
            break;
        case PhysBaseItem::CartesianGraphType:
            break;
        default:
            qDebug("PhysObjectNavigator::onRemovePhysObj: not a supported object type: %d", pObj -> type());
            break;
        }
        scene() ->removeItem(pObj);
    }
}

void GraphWidget::particleProps() {
}

void GraphWidget::vectorProps() {
}

void GraphWidget::createActions() {
    m_actNewVector = new QAction(tr("New &Vector"), this);
    m_actNewVector -> setShortcut(tr("Ctrl+V"));
    m_actNewVector -> setStatusTip(tr("Create a new Vector object"));
    connect(m_actNewVector, SIGNAL(triggered()), this, SLOT(createVector()));

    m_actNewParticle = new QAction(tr("New &Particle"), this);
    m_actNewParticle -> setShortcut(tr("Ctrl+P"));
    m_actNewParticle -> setStatusTip(tr("Create a new Particle object"));
    connect(m_actNewParticle, SIGNAL(triggered()), this, SLOT(createParticle()));

    m_actVectorProps = new QAction(tr("Vector Properties"), this);
    m_actVectorProps -> setStatusTip(tr("Adjust the Default properties of a vector"));
    connect(m_actVectorProps, SIGNAL(triggered()), this, SLOT(vectorProps()));

    m_actParticleProps = new QAction(tr("Particle Properties"), this);
    m_actParticleProps -> setStatusTip(tr("Adjust the Default properties of a particle"));
    connect(m_actParticleProps, SIGNAL(triggered()), this, SLOT(particleProps()));

    // Hook up the custom Context menu handler
    connect(this,
            SIGNAL(customContextMenuRequested(const QPoint &)),
            SLOT(onCustomContextMenuRequested(const QPoint &)));
}

void GraphWidget::onCustomContextMenuRequested(const QPoint &pos) {
    QGraphicsItem *pItem = itemAt(pos);

    if (pItem) {
        // Note: We must map the point to global from the viewport to
        // account for the header.
        showPhysObjContextMenu(pItem, viewport() -> mapToGlobal(pos));
    }
    else {
        showWidgetContextMenu(pos);
    }
}

void GraphWidget::showWidgetContextMenu(const QPoint& globalPos) {
    QMenu menu(this);
    menu.addAction(m_actNewVector);
    menu.addAction(m_actNewParticle);
    menu.exec(mapToGlobal(globalPos));
}

void GraphWidget::showPhysObjContextMenu(QGraphicsItem *pItem, const QPoint& globalPos) {
    QMenu menu;
    switch (pItem -> type()) {
        case PhysBaseItem::VectorType:
            menu.addAction(m_actVectorProps);
            break;

        case PhysBaseItem::ParticleType:
            menu.addAction(m_actParticleProps);
            break;
    }
    QAction *pAction = menu.exec(globalPos);
    if (pAction) {

    }
}

void GraphWidget::contextMenuEvent(QContextMenuEvent *event) {
    //qDebug("GraphWidget::contextMenuEvent");
    if (event) {
        QMenu menu(this);
        m_currClickPos = event -> pos();
        menu.addAction(m_actNewVector);
        menu.addAction(m_actNewParticle);
        menu.exec(event -> globalPos());
    }
}


void GraphWidget::itemMoved() {
}

void GraphWidget::keyPressEvent(QKeyEvent *event) {
    switch (event -> key()) {
    case Qt::Key_Up:
        m_pCartGraph -> moveBy(0, -20);
        break;
    case Qt::Key_Down:
        m_pCartGraph -> moveBy(0, 20);
        break;
    case Qt::Key_Left:
        m_pCartGraph -> moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        m_pCartGraph -> moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);
}

#ifndef QT_NO_WHEELEVENT
void GraphWidget::wheelEvent(QWheelEvent *event) {
    scaleView(pow((double)2, -event -> delta() / 240.0));
}
#endif

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this -> sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter -> fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter -> fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(1, Qt::lightGray);
    painter -> fillRect(rect.intersected(sceneRect), gradient);
    painter -> setBrush(Qt::NoBrush);
    painter -> drawRect(sceneRect);
}

void GraphWidget::scaleView(qreal scaleFactor) {
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;
    scale(scaleFactor, scaleFactor);
}
