#ifndef CARTESIANGRAPH_H
#define CARTESIANGRAPH_H

#include <QGraphicsItem>

class GraphWidget;

class CartesianGraph : public QGraphicsItem {
public:
    CartesianGraph(GraphWidget *graphWidget);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
private:
    QPointF origin;
    GraphWidget *graph;
    double m_x_min, m_x_max;
    double m_y_min, m_y_max;
    QGraphicsTextItem *m_x_label;
    QGraphicsTextItem *m_y_label;

};

#endif // CARTESIANGRAPH_H
