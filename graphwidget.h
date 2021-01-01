#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtWidgets>
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
    void createCartesianGraph();

    CartesianGraph *cartesianGraph() const { return m_pCartGraph; }
signals:
    void createObj(QGraphicsItem *);
    void removeObj(QGraphicsItem *);
    void modifyObj(QGraphicsItem *);
    void reorderObjNav(QGraphicsItem *);
    void changeItemName(const QString &, const QString &);
    void cartesianGraphCreated(CartesianGraphDataObj *);
public slots:
    void zoomIn() { scaleView(qreal(1.2)); }
    void zoomOut() { scaleView(1 / qreal(1.2)); }
    void onClonePhysObj(QGraphicsItem *);
    void onRemovePhysObj(QGraphicsItem *);
    void onRepaint();
    void onReorderObjNav(QGraphicsItem *);
    void onChangeItemName(const QString &, const QString &);
    void onUpdateWidgetCoordinates(const QPointF &, PhysParticle *);
private slots:
    void createVector();
    void createParticle();
    PhysVector *createVector(const QPointF &);
    PhysParticle *createParticle(const QPointF &);

    void particleProps();
    void vectorProps();
    void onCustomContextMenuRequested(const QPoint& pos);
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void scaleView(qreal scaleFactor);\


private:
    void createActions();
    void showPhysObjContextMenu(QGraphicsItem *, const QPoint &);
    void showWidgetContextMenu(const QPoint &);

    QRectF visibleRect();

private:
    CartesianGraph *m_pCartGraph;
    QAction *m_actNewVector, *m_actNewParticle;
    QAction *m_actVectorProps, *m_actParticleProps;
    QLabel *m_pInfoLabel;
    QGraphicsScene *m_pScene;
    QPointF m_currClickPos;

    CartesianLabel *m_pCoordLabel;
    PhysParticle *m_pParticle;
};

#endif // GRAPHWIDGET_H
