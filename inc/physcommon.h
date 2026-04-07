#ifndef PHYSCOMMON_H
#define PHYSCOMMON_H


class PhysCommon {
public:
    typedef enum { SINGLEDIM_KINEMATICS = 0 } PhysModuleType;

    PhysCommon() {}
    PhysModuleType ModType() { return m_ModType; }
    void ModType(PhysModuleType mod) { m_ModType = mod; }

private:
    PhysModuleType m_ModType;
};

#endif // PHYSCOMMON_H
