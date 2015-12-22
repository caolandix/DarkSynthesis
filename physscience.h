#ifndef PHYSSCIENCE_H
#define PHYSSCIENCE_H

namespace PhysConsts {
    static const double PI = 3.14159265358979323846264338327950288419717;
    static const double DefaultMass = 1.0;  // 1kg
    static const double epsilon_zero = 8.85e-12;   // permittivity constant (electromagnetics)
    static const double e = 1.60e-19;       // Measured in Coulombs
    static const double K = 8.99e9;         // Electrostatic Konstant


    double coulomb(const double q1, const double q2, const double r);
}

#endif // PHYSSCIENCE_H
