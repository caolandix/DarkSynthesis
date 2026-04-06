#include "physdataobj.h"

QDataStream &operator<<(QDataStream &out, const PhysDataObj &obj) {
    return out;
}

QDataStream &operator>>(QDataStream &in, PhysDataObj &obj) {
    return in;
}
