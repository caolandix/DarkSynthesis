#include <QtWidgets>
#include "physdataobj.h"
#include "phystimeslicedataobj.h"

PhysTimeSliceDataObj::PhysTimeSliceDataObj(const double val) : PhysDataObj(QString(""), DT_TIMESLICE, QPoint(0, 0)) {
    m_time = val;
}

