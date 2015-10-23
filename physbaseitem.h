#ifndef PHYSBASEITEM_H
#define PHYSBASEITEM_H

class PhysBaseItem {
public:
    PhysBaseItem() {}
    ~PhysBaseItem() {}

    enum { VectorType = 65536 + 1, ParticleType, CartesianGraphType } ;
};

#endif // PHYSBASEITEM_H
