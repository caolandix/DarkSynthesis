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
private:
};
QDataStream &operator<<(QDataStream &out, const PhysVectorDataObj &obj);
QDataStream &operator>>(QDataStream &in, PhysVectorDataObj &obj);
#endif // PHYSVECTORDATAOBJ_H
