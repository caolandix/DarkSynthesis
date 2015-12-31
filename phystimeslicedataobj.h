#ifndef PHYSTIMESLICEDATAOBJ_H
#define PHYSTIMESLICEDATAOBJ_H

#include "physdataobj.h"

class PhysTimeSliceDataObj : public PhysDataObj {
public:
    PhysTimeSliceDataObj(double val);

    double Time() const { return m_time; }
    void Time(double val) { m_time = val; }

private:
    double m_time;
};

#endif // PHYSTIMESLICEDATAOBJ_H
