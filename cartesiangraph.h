#ifndef CARTESIANGRAPH_H
#define CARTESIANGRAPH_H

#include <QGraphicsItem>

class GraphWidget;
class PhysVector;
class PhysParticle;
class CartesianGraphDataObj;

class CartesianGraph : public QGraphicsItem {
public:
    CartesianGraph(GraphWidget *);
    CartesianGraph(GraphWidget *, QPointF * = NULL, QPointF * = NULL);
    ~CartesianGraph();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

    // accessors
    double tickStep() const { return m_pDataObj -> tickStep(); }
    double xMin() const { return m_pDataObj ->  xmin(); }
    double yMin() const { return m_pDataObj -> ymin(); }
    double xMax() const { return m_pDataObj -> xmax(); }
    double yMax() const { return m_pDataObj -> ymax(); }
    QPointF origin() const { return m_pDataObj -> origin(); }
    QList<PhysVector *> &Vectors() const { return m_pDataObj -> Vectors(); }
    QList<PhysParticle *> &Particles() const { return m_pDataObj -> Particles(); }
    CartesianGraphDataObj &DataObj() const { return *m_pDataObj; }

    QString &XAxisLabel() const { return m_x_label -> toPlainText(); }
    QString &YAxisLabel() const { return m_y_label -> toPlainText(); }

    void createVector();
    void createParticle();
protected:
    QVariant itemChange(GraphicsItemChange, const QVariant &) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
private:
    GraphWidget *m_pgraphWidget;
    CartesianGraphDataObj *m_pDataObj;
};

#endif // CARTESIANGRAPH_H
