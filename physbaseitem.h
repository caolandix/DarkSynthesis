#ifndef PHYSBASEITEM_H
#define PHYSBASEITEM_H

#include <QGraphicsItem>

class PhysBaseItem : public QGraphicsItem {
public:
    PhysBaseItem() : QGraphicsItem() {}

    enum { VectorType = UserType + 1, ParticleType };
signals:

public slots:
};

#endif // PHYSBASEITEM_H
