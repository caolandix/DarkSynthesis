#include "physeqrow.h"
#include "physeqrowprops.h"

PhysEqRow::PhysEqRow(const QString &equation, const QString &variableName) {
    m_pRowProps = new PhysEqRowProps(equation, &variableName);
}

PhysEqRow::PhysEqRow(const PhysEqRow &obj) {
    delete m_pRowProps;
    m_pRowProps = new PhysEqRowProps(obj.RowProps());
}

PhysEqRow &PhysEqRow::operator=(const PhysEqRow &obj) {
    if (*this != obj) {
        delete m_pRowProps;
        m_pRowProps = new PhysEqRowProps
    }
    return *this;
}

PhysEqRow::~PhysEqRow() {
    delete m_pRowProps; m_pRowProps = NULL;
}


