#ifndef PHYSVECTORDATAOBJ_H
#define PHYSVECTORDATAOBJ_H

#include <QtWidgets>

#include "physdataobj.h"

class PhysVectorDataObj : public PhysDataObj {
public:
    PhysVectorDataObj();
    PhysVectorDataObj(const QString str) : PhysDataObj(str, DT_VECTOR) {}
    PhysVectorDataObj(const QString, const QString, const QString = "", double = 0.0);
    PhysVectorDataObj(const QString, const QStringList, const QString = "", double = 0.0);
    PhysVectorDataObj(const PhysVectorDataObj &);
    PhysVectorDataObj(const PhysVectorDataObj *);
    ~PhysVectorDataObj() {}
    PhysVectorDataObj &operator=(const PhysVectorDataObj &);
    bool operator==(const PhysVectorDataObj &);

    void Magnitude(const double val) { m_magnitude = val; }
    void Magnitude(const QString &str) { m_magnitude = str.toDouble(); }
    double Magnitude() const { return m_magnitude; }
    QString Variable() const { return m_variable; }
    QString Equation() const { return m_equation; }
    void Equation(const QString str);
    void Variable(const QString str) { m_variable = str; }
    QStringList EquationList() const { return m_eqList; }
    void EquationList(QStringList eqList) { m_eqList = eqList; }
private:
    QString m_variable;
    QString m_equation;
    QStringList m_eqList;
    double m_magnitude;
};
QDataStream &operator<<(QDataStream &out, const PhysVectorDataObj &obj);
QDataStream &operator>>(QDataStream &in, PhysVectorDataObj &obj);
Q_DECLARE_METATYPE(const PhysVectorDataObj *)
Q_DECLARE_METATYPE(PhysVectorDataObj *)
#endif // PHYSVECTORDATAOBJ_H
