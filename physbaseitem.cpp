#include <QGraphicsItem>
#include "physbaseitem.h"

PhysBaseItem::PhysBaseItem() {
    m_Types[VectorType] = QString("VectorType");
    m_Types[ParticleType] = QString("ParticleType");
    m_Types[CartesianGraphType] = QString("CartesianGraphType");
}

QString &PhysBaseItem::TypeName(int Type) const {
    map<int, QString>::const_iterator iter = m_Types.find(Type);
    QString value;
    if (iter == m_Types.end()) {
        // handle the error
    }
    else {
        value = iter -> second;
    }
    return value;
}
