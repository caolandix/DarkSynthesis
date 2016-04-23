#ifndef PHYSPARTICLEDATAOBJ_H
#define PHYSPARTICLEDATAOBJ_H

#include <QtWidgets>

#include "physdataobj.h"

class PhysParticleDataObj : public PhysDataObj {
public:
    PhysParticleDataObj(const QString = "", const double = 0.0, const double = 0.0);
    PhysParticleDataObj(const PhysParticleDataObj &);
    ~PhysParticleDataObj();

    PhysParticleDataObj &operator=(const PhysParticleDataObj &);

    QPointF Position() const { return QPoint(xcoord(), ycoord()); }

    double mass() const { return m_mass; }
    void mass(const double val) { m_mass = val; }
private:
    double m_mass;
};
QDataStream &operator<<(QDataStream &out, const PhysParticleDataObj &obj);
QDataStream &operator>>(QDataStream &in, PhysParticleDataObj &obj);

Q_DECLARE_METATYPE(const PhysParticleDataObj *)
Q_DECLARE_METATYPE(PhysParticleDataObj *)
#endif // PHYSPARTICLEDATAOBJ_H
