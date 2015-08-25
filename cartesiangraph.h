#ifndef CARTESIANGRAPH_H
#define CARTESIANGRAPH_H

#include <QGraphicsItem>

class GraphWidget;
class PhysVector;
class PhysParticle;

class CartesianGraph : public QGraphicsItem {
public:
    CartesianGraph(GraphWidget *);
    CartesianGraph(GraphWidget *, QPointF *, QPointF *);
    ~CartesianGraph();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

    // accessors
    double tickStep() const { return m_tickStep; }
    double xMin() const { return m_x_min; }
    double yMin() const { return m_y_min; }
    double xMax() const { return m_x_max; }
    double yMax() const { return m_y_max; }
    QPointF origin() const { return m_origin; }

    void createVector();
    void createParticle();
protected:
    QVariant itemChange(GraphicsItemChange, const QVariant &) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
private:


    QPointF m_origin;
    GraphWidget *m_pgraphWidget;
    double m_tickStep;
    double m_x_min, m_x_max, m_y_min, m_y_max;
    QGraphicsTextItem *m_x_label, *m_y_label;
    QList<PhysVector *> m_Vectors;
    QList<PhysParticle *> m_Particles;
};

#endif // CARTESIANGRAPH_H
