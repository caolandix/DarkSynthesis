#ifndef PHYSBASEITEM_H
#define PHYSBASEITEM_H

#include <map>

using namespace std;

class PhysBaseItem {
public:
    PhysBaseItem();
    ~PhysBaseItem() {}

    enum { VectorType = 65536 + 1, ParticleType, CartesianGraphType } ;

    QString TypeName(int Type) const;

private:
    map<int, QString> m_Types;
};
#endif // PHYSBASEITEM_H
