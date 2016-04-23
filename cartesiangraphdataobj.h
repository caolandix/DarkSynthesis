#ifndef CARTESIANGRAPHDATAOBJ_H
#define CARTESIANGRAPHDATAOBJ_H

#include <QtWidgets>

#include "physdataobj.h"
#include "physvector.h"
#include "physparticle.h"

class CartesianGraphDataObj : public PhysDataObj {
public:
    CartesianGraphDataObj(const QString Name = "");
    CartesianGraphDataObj(const QPointF origin, const double tickStep, const int tickLength, const double x_min, const double x_max, const double y_min, const double y_max, const QString Name = "");
    virtual ~CartesianGraphDataObj();

    // copy ctor and assignment
    CartesianGraphDataObj(const CartesianGraphDataObj &);
    CartesianGraphDataObj(const CartesianGraphDataObj *);
    void copyData(const CartesianGraphDataObj &);
    void copyData(const CartesianGraphDataObj *);


    // operator overloads
    CartesianGraphDataObj &operator=(const CartesianGraphDataObj &);
    bool operator==(const CartesianGraphDataObj &);

    // Accessors -- get
    double tickStep() const { return m_tickStep; }
    int tickLength() const { return m_tickLength; }
    double xMin() const { return m_x_min; }
    double yMin() const { return m_y_min; }
    double xMax() const { return m_x_max; }
    double yMax() const { return m_y_max; }
    QPointF origin() const { return m_origin; }
    QList<PhysVector *> Vectors() const { return m_Vectors; }
    QList<PhysParticle *> Particles() const { return m_Particles; }

    // Accessors -- set
    void tickStep(const double val) { m_tickStep = val; }
    void tickLength(const int val) { m_tickLength = val; }
    void xMin(const double val) { m_x_min = val; }
    void yMin(const double val) { m_y_min = val; }
    void xMax(const double val) { m_x_max = val; }
    void yMax(const double val) { m_y_max = val; }
    void origin(const QPointF val) { m_origin = val; }
    void Vectors(const QList<PhysVector *> &val) { m_Vectors = val; }
    void Particles(QList<PhysParticle *> &val) { m_Particles = val; }


    // methods
    void AddVector(PhysVector *pObj) { m_Vectors.push_back(pObj); }
    void AddParticle(PhysParticle *pObj) { m_Particles.push_back(pObj); }
    void init();
private:
    QPointF m_origin;
    double m_tickStep;
    double m_x_min, m_x_max, m_y_min, m_y_max;
    int m_tickLength;
    QList<PhysVector *> m_Vectors;
    QList<PhysParticle *> m_Particles;
};
QDataStream &operator<<(QDataStream &out, const CartesianGraphDataObj &obj);
QDataStream &operator>>(QDataStream &in, CartesianGraphDataObj &obj);

#endif // CARTESIANGRAPHDATAOBJ_H

