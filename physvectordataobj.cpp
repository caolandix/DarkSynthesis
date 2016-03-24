#include "physvectordataobj.h"

PhysVectorDataObj::PhysVectorDataObj() : PhysDataObj(QString(""), DT_VECTOR, QPoint(0, 0)) {
    m_variable = QString("");
    m_equation = QString("");
    m_magnitude = 0.0;
}


PhysVectorDataObj::PhysVectorDataObj(const QString variable, const QString equation, const QString name, double magnitude, const QPoint pos) : PhysDataObj(name, DT_VECTOR, pos) {
    m_variable = variable;
    Equation(equation);
    m_equation = m_eqList.at(0);
    m_magnitude = magnitude;
}

PhysVectorDataObj::PhysVectorDataObj(const QString variable, const QStringList equations, const QString name, double magnitude, const QPoint pos) : PhysDataObj(name, DT_VECTOR, pos) {
    m_variable = variable;
    foreach (QString eq, equations)
        Equation(eq);
    m_equation = m_eqList.at(0);
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

void PhysVectorDataObj::Equation(const QString eq) {

    QString str = eq;

    // strip out whitespaces
    str = str.simplified();
    str.replace(" ", "");

    m_equation = str;

    // if list is empty, just add it
    if (m_eqList.count() < 1)
        m_eqList.push_back(m_equation);
    else {

        // check to see if the equation being added is already in the list
        if (m_eqList.indexOf(str) == -1)
            m_eqList.push_back(m_equation);
    }
}


QDataStream &operator<<(QDataStream &out, const PhysVectorDataObj &obj) {
    return out;
}

QDataStream &operator>>(QDataStream &in, PhysVectorDataObj &obj) {
    return in;
}
