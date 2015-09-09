#ifndef CARTESIANGRAPHDATAOBJ_H
#define CARTESIANGRAPHDATAOBJ_H

#include <QDataStream>
#include <QGraphicsTextItem>
#include <QPointF>
#include "physvector.h"
#include "physparticle.h"

class CartesianGraphDataObj {
public:
    CartesianGraphDataObj() {}
    virtual ~CartesianGraphDataObj();

    // copy ctor and assignment
    CartesianGraphDataObj(const CartesianGraphDataObj &);

    // operator overloads
    CartesianGraphDataObj &operator=(const CartesianGraphDataObj &);
    bool operator==(const CartesianGraphDataObj &);

    // Accessors -- get
    double tickStep() const { return m_tickStep; }
    double xMin() const { return m_x_min; }
    double yMin() const { return m_y_min; }
    double xMax() const { return m_x_max; }
    double yMax() const { return m_y_max; }
    QPointF origin() const { return m_origin; }
    QList<PhysVector *> Vectors() const { return m_Vectors; }
    QList<PhysParticle *> Particles() const { return m_Particles; }
    QString XAxisLabel() const { return m_x_label -> toPlainText(); }
    QString YAxisLabel() const { return m_y_label -> toPlainText(); }

    // Accessors -- set
    void tickStep(const double data) { m_tickStep = data; }
    void xMin(const double data) { m_x_min = data; }
    void yMin(const double data) { m_y_min = data; }
    void xMax(const double data) { m_x_max = data; }
    void yMax(const double data) { m_y_max = data; }
    void origin(const QPointF data) { m_origin = data; }
    void Vectors(const QList<PhysVector *> &data) { m_Vectors = data; }
    void Particles(QList<PhysParticle *> &data) { m_Particles = data; }
    void XAxisLabel(const QString data) { m_x_label -> setPlainText(data); }
    void YAxisLabel(const QString data) { m_y_label -> setPlainText(data); }
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

