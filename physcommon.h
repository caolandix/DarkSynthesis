#ifndef PHYSCOMMON_H
#define PHYSCOMMON_H


class PhysCommon {
public:
    PhysCommon() {}

public:
    typedef enum { SINGLEDIM_KINEMATICS = 0 } PhysModuleType;

    PhysModuleType ModType() { return m_ModType; }
    void ModType(PhysModuleType mod) { m_ModType = mod; }

    PhysModuleType m_ModType;
};

#endif // PHYSCOMMON_H
