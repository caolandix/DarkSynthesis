#ifndef MTHEQVAL_H
#define MTHEQVAL_H

#include <QtWidgets>

class MthEqVal {
public:
    MthEqVal() : m_currNestingLevel(0) {}

    int NestingLvl() const { return m_currNestingLevel; }
    void IncNestingLvl() { m_currNestingLevel++; }
    void DecNestingLvl() { if (m_currNestingLevel > 0) m_currNestingLevel--; else m_currNestingLevel = 0; }

private:
    int m_currNestingLevel;
};

#endif // MTHEQVAL_H
