#ifndef PHYSVECTORDATAOBJ_H
#define PHYSVECTORDATAOBJ_H

#include <QString>

#include "physdataobj.h"

class PhysVectorDataObj : public PhysDataObj {
public:
    PhysVectorDataObj(const QString str = "") : PhysDataObj(str) {}
    PhysVectorDataObj(const PhysVectorDataObj &);
    PhysVectorDataObj(const PhysVectorDataObj *);
    ~PhysVectorDataObj() {}
    PhysVectorDataObj &operator=(const PhysVectorDataObj &);


    void Magnitude(const double val) { m_magnitude = val; }
    void Magnitude(const QString &str) { m_magnitude = str.toDouble(); }
    double Magnitude() const { return m_magnitude; }
private:

    double m_magnitude;
};
QDataStream &operator<<(QDataStream &out, const PhysVectorDataObj &obj);
QDataStream &operator>>(QDataStream &in, PhysVectorDataObj &obj);
#endif // PHYSVECTORDATAOBJ_H
