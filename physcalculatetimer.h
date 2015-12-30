#ifndef PHYSCALCULATETIMER_H
#define PHYSCALCULATETIMER_H

#include <QtWidgets>

class PhysCalculateTimer {
public:
    PhysCalculateTimer(QObject * = NULL, int interval = 1000);
    ~PhysCalculateTimer() { delete m_pTimer; }

    QTimer *Timer() const { return m_pTimer; }
    int Interval() const { return m_Interval; }
    void Interval(int val) { m_Interval = val; }
    void start() { m_pTimer ->start(m_Interval); }
    void stop() { m_pTimer ->stop(); }
private:
    int m_Interval;
    QTimer *m_pTimer;
};

#endif // PHYSCALCULATETIMER_H
