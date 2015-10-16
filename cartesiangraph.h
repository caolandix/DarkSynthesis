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
    CartesianGraph(const QString & = "Cartesian Plane");

    // copy ctor
    CartesianGraph(const CartesianGraph &);

    // other ctors
    CartesianGraph(GraphWidget *, const QString & = "Cartesian Plane", CartesianGraphDataObj * = NULL);

    // dtor
    ~CartesianGraph();

    // operator overloads
    CartesianGraph &operator=(const CartesianGraph &);

    // overloaded inherited methods
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

    // accessors -- get
    double tickStep() const { return m_pDataObj -> tickStep(); }
    double xMin() const { return m_pDataObj ->  xMin(); }
    double yMin() const { return m_pDataObj -> yMin(); }
    double xMax() const { return m_pDataObj -> xMax(); }
    double yMax() const { return m_pDataObj -> yMax(); }
    QPointF origin() const { return m_pDataObj -> origin(); }
    QList<PhysVector *> Vectors() const { return m_pDataObj -> Vectors(); }
    QList<PhysParticle *> Particles() const { return m_pDataObj -> Particles(); }
    CartesianGraphDataObj *DataObj() const { return m_pDataObj; }
    GraphWidget *graphWidget() const { return m_pGraphWidget; }
    QString XAxisLabel() const { return m_x_label -> toPlainText(); }
    QString YAxisLabel() const { return m_y_label -> toPlainText(); }
    QString Name() const { return m_Name; }

    // accessors -- set
    void XAxisLabel(const QString &data) { m_x_label -> setPlainText(data); }
    void YAxisLabel(const QString &data) { m_y_label -> setPlainText(data); }
    void Name(const QString &obj) { m_Name = obj; }

    // Member methods
    void createVector(const QPointF startPos);
    void createParticle(const QPointF startPos);

protected:
    QVariant itemChange(GraphicsItemChange, const QVariant &) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
private:
    GraphWidget *m_pGraphWidget;
    QGraphicsTextItem *m_x_label, *m_y_label;
    CartesianGraphDataObj *m_pDataObj;
    int m_borderWidth;
    QString m_Name;
};

#endif // CARTESIANGRAPH_H
