#ifndef PHYSPARTICLEDATAOBJ_H
#define PHYSPARTICLEDATAOBJ_H

#include <QtWidgets>

#include "physdataobj.h"

class PhysParticleDataObj : public PhysDataObj {
public:
    PhysParticleDataObj(const QString = "");
    PhysParticleDataObj(const PhysParticleDataObj &);
    ~PhysParticleDataObj();

    PhysParticleDataObj &operator=(const PhysParticleDataObj &);

    double mass() const { return m_mass; }
    void mass(const double val) { m_mass = val; }
    QPointF Position() const { return m_position; }
    void Position(const QPointF pos) { m_position = pos; }
private:
    double m_mass;
    QPointF m_position;
};
QDataStream &operator<<(QDataStream &out, const PhysParticleDataObj &obj);
QDataStream &operator>>(QDataStream &in, PhysParticleDataObj &obj);
#endif // PHYSPARTICLEDATAOBJ_H
