#ifndef PHYSSCIENCE_H
#define PHYSSCIENCE_H

#include <numbers>
using namespace std;

namespace PhysConsts {
    static const double PI =            std::numbers::pi;
    static const double DefaultMass =   1.0;                                        // 1kg
    static const double epsilon_zero =  8.85e-12;                                   // permittivity constant (electromagnetics)
    static const double e =             std::numbers::e;                                   // Measured in Coulombs
    static const double K =             8.99e9;                                     // Electrostatic Konstant
    static const double earth_g =       9.8;                                        // force of gravity constant on earth


    double coulomb(const double q1, const double q2, const double r);
}

#endif // PHYSSCIENCE_H
