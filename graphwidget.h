#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

class Node;

class GraphWidget : public QGraphicsView {
    Q_OBJECT
public:
    GraphWidget(QWidget *parent = NULL);
    void itemMoved();

public slots:
    void shuffle();
    void zoomIn() { scaleView(qreal(1.2)); };
    void zoomOut() { scaleView(1 / qreal(1.2)); };

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void scaleView(qreal scaleFactor);
private:
    int m_timerId;
    Node *m_pcenterNode;
};

#endif // GRAPHWIDGET_H
