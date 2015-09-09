#ifndef CARTESIANGRAPH_H
#define CARTESIANGRAPH_H

#include <QGraphicsItem>
#include "CartesianGraphDataObj.h"

class GraphWidget;
class PhysVector;
class PhysParticle;

class CartesianGraph : public QGraphicsItem {
public:

    // basic ctor
    CartesianGraph() {}

    // copy ctor
    CartesianGraph(const CartesianGraph &);

    // othger ctors
    CartesianGraph(CartesianGraphDataObj *, GraphWidget *, QPointF * = NULL, QPointF * = NULL);

    // dtor
    ~CartesianGraph();

    // operator overloads
    CartesianGraph &operator=(const )

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

    // accessors
    double tickStep() const { return m_pDataObj -> tickStep(); }
    double xMin() const { return m_pDataObj ->  xMin(); }
    double yMin() const { return m_pDataObj -> yMin(); }
    double xMax() const { return m_pDataObj -> xMax(); }
    double yMax() const { return m_pDataObj -> yMax(); }
    QPointF origin() const { return m_pDataObj -> origin(); }
    QList<PhysVector *> Vectors() const { return m_pDataObj -> Vectors(); }
    QList<PhysParticle *> Particles() const { return m_pDataObj -> Particles(); }
    CartesianGraphDataObj *DataObj() const { return m_pDataObj; }

    QString XAxisLabel() const { return m_pDataObj -> XAxisLabel(); }
    QString YAxisLabel() const { return m_pDataObj -> YAxisLabel(); }

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
