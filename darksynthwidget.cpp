#include "darksynthwidget.h"
#include "cartesiangraph.h"

#include <math.h>
#include <QKeyEvent>

DarkSynthWidget::DarkSynthWidget(QWidget *parent) : QGraphicsView(parent) {
}

void DarkSynthWidget::itemMoved() {
}

void DarkSynthWidget::keyPressEvent(QKeyEvent *event) {
    switch (event -> key()) {
        case Qt::Key_Up:
            m_pcartGraph -> moveBy(0, -20);
            break;
        case Qt::Key_Down:
            m_pcartGraph -> moveBy(0, 20);
            break;
        case Qt::Key_Left:
            m_pcartGraph -> moveBy(-20, 0);
            break;
        case Qt::Key_Right:
            m_pcartGraph -> moveBy(20, 0);
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

void DarkSynthWidget::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);
}

#ifndef QT_NO_WHEELEVENT
void DarkSynthWidget::wheelEvent(QWheelEvent *event) {
    scaleView(pow((double)2, -event -> delta() / 240.0));
}
#endif

void DarkSynthWidget::drawBackground(QPainter *painter, const QRectF &rect) {
    //Q_UNUSED(rect);

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
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter -> fillRect(rect.intersected(sceneRect), gradient);
    painter -> setBrush(Qt::NoBrush);
    painter -> drawRect(sceneRect);
}

void DarkSynthWidget::scaleView(qreal scaleFactor) {
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;
    scale(scaleFactor, scaleFactor);
}
