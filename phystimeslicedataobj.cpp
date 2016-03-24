#include <QtWidgets>
#include "physdataobj.h"
#include "phystimeslicedataobj.h"

PhysTimeSliceDataObj::PhysTimeSliceDataObj(const double val) : PhysDataObj(QString(""), DT_TIMESLICE) {
    m_time = val;
}

