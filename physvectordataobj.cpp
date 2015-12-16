#include "physvectordataobj.h"

PhysVectorDataObj::PhysVectorDataObj(const PhysVectorDataObj &obj) : PhysDataObj(obj) {
}

PhysVectorDataObj::PhysVectorDataObj(const PhysVectorDataObj *pObj) : PhysDataObj(pObj) {
}

PhysVectorDataObj &PhysVectorDataObj::operator=(const PhysVectorDataObj &obj) {
    m_Name = obj.Name();
    return *this;
}

QDataStream &operator<<(QDataStream &out, const PhysVectorDataObj &obj) {
    return out;
}

QDataStream &operator>>(QDataStream &in, PhysVectorDataObj &obj) {
    return in;
}
