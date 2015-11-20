#include "physparticledataobj.h"
#include "physscience.h"

PhysParticleDataObj::PhysParticleDataObj() {

    // Physical attributes
    m_mass = PhysConsts::DefaultMass; // 1kg is default
}

PhysParticleDataObj::PhysParticleDataObj(const PhysParticleDataObj &obj) {
}

PhysParticleDataObj::~PhysParticleDataObj() {
}

PhysParticleDataObj &PhysParticleDataObj::operator=(const PhysParticleDataObj &obj) {
    return *this;
}
