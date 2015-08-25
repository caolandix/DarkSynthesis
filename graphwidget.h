#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

class Node;
class CartesianGraph;
class QAction;
class QGraphicsScene;
class QLabel;
class PhysVector;
class PhysParticle;

class GraphWidget : public QGraphicsView {
    Q_OBJECT
public:
    GraphWidget(QWidget *parent = NULL);
    void itemMoved();

public slots:
    void zoomIn() { scaleView(qreal(1.2)); }
    void zoomOut() { scaleView(1 / qreal(1.2)); }
private slots:
    void createVector();
protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void scaleView(qreal scaleFactor);

private:
    void createActions();

private:
    CartesianGraph *m_pcartGraph;
    QAction *m_actNewVector;
    QLabel *m_pInfoLabel;
};

#endif // GRAPHWIDGET_H
