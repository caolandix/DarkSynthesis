#include <QPoint>
#include "physparticledataobj.h"
#include "physscience.h"

PhysParticleDataObj::PhysParticleDataObj(const QString str) : PhysDataObj(str, DT_PARTICLE) {

    // Physical attributes
    m_mass = PhysConsts::DefaultMass; // 1kg is default
    m_position = QPoint(0, 0);
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
