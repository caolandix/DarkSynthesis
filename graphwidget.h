#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include "cartesiangraph.h"

class Node;
class QAction;
class QGraphicsScene;
class QLabel;
class PhysVector;
class PhysParticle;
class CartesianGraph;

class GraphWidget : public QGraphicsView {
    Q_OBJECT
public:
    GraphWidget(QWidget *parent = NULL);
    void itemMoved();

    CartesianGraph *cartesianGraph() const { return m_pCartGraph; }

public slots:
    void zoomIn() { scaleView(qreal(1.2)); }
    void zoomOut() { scaleView(1 / qreal(1.2)); }
private slots:
    void createVector();
    void createParticle();
    void vectorPropsDlg();
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
    CartesianGraph *m_pCartGraph;
    QAction *m_actNewVector, *m_actNewParticle;
    QLabel *m_pInfoLabel;
    QGraphicsScene *m_pScene;
    QPointF m_currClickPos;
};

#endif // GRAPHWIDGET_H
