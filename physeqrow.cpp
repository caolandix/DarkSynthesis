#include "physeqrow.h"
#include "physeqrowprops.h"

PhysEqRow::PhysEqRow(const QString &equation, const QString &variableName) {
    m_pRowProps = new PhysEqRowProps(equation, variableName);
}

PhysEqRow::PhysEqRow(const PhysEqRow &obj) {
    m_pRowProps = new PhysEqRowProps(obj.RowProps() ->Equation(), obj.RowProps() ->VariableName());
    m_CellList = obj.cellList();
}

PhysEqRow &PhysEqRow::operator=(const PhysEqRow &obj) {
    if (this != &obj) {
        delete m_pRowProps;
        m_pRowProps = new PhysEqRowProps(obj.RowProps() ->Equation(), obj.RowProps() ->VariableName());
        m_CellList = obj.cellList();
    }
    return *this;
}

PhysEqRow::~PhysEqRow() {
    delete m_pRowProps; m_pRowProps = NULL;
    m_CellList.clear();
}


