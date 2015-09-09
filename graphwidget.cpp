#include <math.h>
#include <QKeyEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QContextMenuEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMenu>
#include <QLabel>

#include "graphwidget.h"
#include "cartesiangraph.h"

GraphWidget::GraphWidget(QWidget *parent) : QGraphicsView(parent) {
    setContextMenuPolicy(Qt::DefaultContextMenu);
    QGraphicsScene *pScene = new QGraphicsScene(this);
    pScene -> setItemIndexMethod(QGraphicsScene::NoIndex);
    pScene -> setSceneRect(-200, -200, 400, 400);
    setScene(pScene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);
    setWindowTitle(tr("Cartesian Graph"));

    // Creation of the cartesian graph sitting in the center of the GraphWidget. It is used to
    // show where the vector drawing occurs and the scales defined.
    m_pCartGraph = new CartesianGraph(this);
    pScene -> addItem(m_pCartGraph);
    m_pCartGraph -> setPos(0, 0);

    m_pInfoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to invoke a context menu</i>"));

    // Create the actions used in the context menus
    createActions();
}

void GraphWidget::createVector() {
    m_pInfoLabel -> setText(tr("Created a new Vector"));
    m_pCartGraph -> createVector();
}

void GraphWidget::createActions() {
    m_actNewVector = new QAction(tr("New &Vector"), this);
    m_actNewVector -> setShortcut(tr("Ctrl+V"));
    m_actNewVector -> setStatusTip(tr("Create a new Vector object"));
    connect(m_actNewVector, SIGNAL(triggered()), this, SLOT(createVector()));
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

void GraphWidget::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    menu.addAction(m_actNewVector);
    menu.exec(event -> globalPos());

    QGraphicsScene *scene = this -> scene();
    QGraphicsItem *pItem = scene -> focusItem();
    if (event) {
        ;
    }
}
