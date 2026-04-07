#include <math.h>
#include "physscience.h"


double coulomb(const double q1, const double q2, const double r) {
    return (1 / (4 * PhysConsts::PI * PhysConsts::epsilon_zero)) * ((abs(q1) * abs(q2)) / r * r);
}
