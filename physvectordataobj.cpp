#include "physvectordataobj.h"

PhysVectorDataObj::PhysVectorDataObj() : PhysDataObj(QString(""), DT_VECTOR) {
    m_variable = QString("");
    m_equation = QString("");
    m_magnitude = 0.0;
}


PhysVectorDataObj::PhysVectorDataObj(const QString variable, const QString equation, const QString name, double magnitude) : PhysDataObj(name, DT_VECTOR) {
    m_variable = variable;
    m_equation = equation;
    m_magnitude = magnitude;
}

PhysVectorDataObj::PhysVectorDataObj(const PhysVectorDataObj &obj) : PhysDataObj(obj) {
    m_variable = obj.Variable();
    m_equation = obj.Equation();
    m_magnitude = obj.Magnitude();
}

PhysVectorDataObj::PhysVectorDataObj(const PhysVectorDataObj *pObj) : PhysDataObj(pObj) {
    m_variable = pObj ->Variable();
    m_equation = pObj ->Equation();
    m_magnitude = pObj ->Magnitude();
}

PhysVectorDataObj &PhysVectorDataObj::operator=(const PhysVectorDataObj &obj) {
    if (this != &obj) {
        m_Name = obj.Name();
        m_variable = obj.Variable();
        m_equation = obj.Equation();
        m_magnitude = obj.Magnitude();
    }
    return *this;
}

bool PhysVectorDataObj::operator==(const PhysVectorDataObj &obj) {
    if (this != &obj) {
        if (m_Name.compare(obj.Name()) != 0)
            return false;
        if (m_variable.compare(obj.Variable()) != 0)
            return false;
        if (m_equation.compare(obj.Equation()) != 0)
            return false;
        if (m_magnitude != obj.Magnitude())
            return false;
    }
    return true;
}

QDataStream &operator<<(QDataStream &out, const PhysVectorDataObj &obj) {
    return out;
}

QDataStream &operator>>(QDataStream &in, PhysVectorDataObj &obj) {
    return in;
}
