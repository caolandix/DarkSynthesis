#include <QPoint>
#include "physparticledataobj.h"
#include "physscience.h"

PhysParticleDataObj::PhysParticleDataObj(const QString str, const QPoint pos) : PhysDataObj(str, DT_PARTICLE, pos) {

    // Physical attributes
    m_mass = PhysConsts::DefaultMass; // 1kg is default
}

PhysParticleDataObj::PhysParticleDataObj(const PhysParticleDataObj &obj) : PhysDataObj(obj) {
    m_mass = obj.mass();
    m_position = obj.Position();
}

PhysParticleDataObj::~PhysParticleDataObj() {
}

PhysParticleDataObj &PhysParticleDataObj::operator=(const PhysParticleDataObj &obj) {
    if (this != &obj) {
        m_mass = obj.mass();
        m_position = obj.Position();
    }
    return *this;
}

QDataStream &operator<<(QDataStream &out, const PhysParticleDataObj &obj) {
    return out;
}

QDataStream &operator>>(QDataStream &in, PhysParticleDataObj &obj) {
    return in;
}
