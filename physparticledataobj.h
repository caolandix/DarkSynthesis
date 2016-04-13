#ifndef PHYSPARTICLEDATAOBJ_H
#define PHYSPARTICLEDATAOBJ_H

#include <QtWidgets>

#include "physdataobj.h"

class PhysParticleDataObj : public PhysDataObj {
public:
    PhysParticleDataObj(const QString = "", const QPoint = QPoint(0, 0));
    PhysParticleDataObj(const PhysParticleDataObj &);
    ~PhysParticleDataObj();

    PhysParticleDataObj &operator=(const PhysParticleDataObj &);

    double mass() const { return m_mass; }
    void mass(const double val) { m_mass = val; }
    double xcoord() const { return m_xpos; }
    double ycoord() const { return m_ypos; }
    void xcoord(double val) const { m_xpos = val; }
    void ycoord(double val) const { m_ypos = val; }
private:
    double m_mass;
    double m_xpos, m_ypos;
};
QDataStream &operator<<(QDataStream &out, const PhysParticleDataObj &obj);
QDataStream &operator>>(QDataStream &in, PhysParticleDataObj &obj);

Q_DECLARE_METATYPE(const PhysParticleDataObj *)
Q_DECLARE_METATYPE(PhysParticleDataObj *)
#endif // PHYSPARTICLEDATAOBJ_H
