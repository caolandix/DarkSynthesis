#include "physcalculatetimer.h"

PhysCalculateTimer::PhysCalculateTimer(QObject *pParent, const int Interval) {
    m_pTimer = new QTimer(pParent);
    m_Interval = Interval;
}

