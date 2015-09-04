#ifndef CARTESIANGRAPHDATAOBJ_H
#define CARTESIANGRAPHDATAOBJ_H

#include <QDataStream>

class CartesianGraphDataObj {
public:
    CartesianGraphDataObj() {}
    virtual ~CartesianGraphDataObj();

    // copy ctor and assignment
    CartesianGraphDataObj(const CartesianGraphDataObj &);

    // operator overloads
    CartesianGraphDataObj &operator=(const CartesianGraphDataObj &);
    bool operator==(const CartesianGraphDataObj &);

    double tickStep() const { return m_pDataObj -> tickStep(); }
    double xMin() const { return m_pDataObj ->  xmin(); }
    double yMin() const { return m_pDataObj -> ymin(); }
    double xMax() const { return m_pDataObj -> xmax(); }
    double yMax() const { return m_pDataObj -> ymax(); }
    QPointF origin() const { return m_pDataObj -> origin(); }
    QList<PhysVector *> &Vectors() const { return m_pDataObj -> Vectors(); }
    QList<PhysParticle *> &Particles() const { return m_pDataObj -> Particles(); }
    QString &XAxisLabel() const { return m_x_label -> toPlainText(); }
    QString &YAxisLabel() const { return m_y_label -> toPlainText(); }

private:
    QPointF m_origin;
    double m_tickStep;
    double m_x_min, m_x_max, m_y_min, m_y_max;
    QList<PhysVector *> m_Vectors;
    QList<PhysParticle *> m_Particles;
    QGraphicsTextItem *m_x_label, *m_y_label;
};
QDataStream &operator<<(QDataStream &out, const CartesianGraphDataObj &obj);
QDataStream &operator>>(QDataStream &in, CartesianGraphDataObj &obj);

#endif // CARTESIANGRAPHDATAOBJ_H

