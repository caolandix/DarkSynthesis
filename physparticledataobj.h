#ifndef PHYSPARTICLEDATAOBJ_H
#define PHYSPARTICLEDATAOBJ_H

#include <QtWidgets>

class PhysParticleDataObj {
public:
    PhysParticleDataObj();
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

#endif // PHYSPARTICLEDATAOBJ_H
