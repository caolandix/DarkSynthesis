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

#endif // PHYSVECTORDATAOBJ_H
