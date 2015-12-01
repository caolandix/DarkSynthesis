#ifndef PHYSBASEITEM_H
#define PHYSBASEITEM_H

#include <map>
#include <QObject>

using namespace std;

class PhysBaseItem : public QObject {
    Q_OBJECT
public:
    PhysBaseItem();
    ~PhysBaseItem() {}

    enum { VectorType = 65536 + 1, ParticleType, CartesianGraphType } ;

    QString TypeName(int Type) const;

    virtual PhysBaseItem *copy() = 0;
    virtual void init() = 0;

private:
    map<int, QString> m_Types;
};
#endif // PHYSBASEITEM_H
