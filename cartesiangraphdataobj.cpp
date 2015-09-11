#include "cartesiangraphdataobj.h"

CartesianGraphDataObj::CartesianGraphDataObj() {
    m_tickStep = 10.0;
}

CartesianGraphDataObj::CartesianGraphDataObj(const CartesianGraphDataObj *pObj) {
    if (pObj != this) {
    }
}

CartesianGraphDataObj::CartesianGraphDataObj(
        QPointF origin,
        double tickStep,
        double x_min,
        double x_max,
        double y_min,
        double y_max) {
    m_origin = origin;
    m_tickStep = tickStep;
    m_x_min = x_min;
    m_x_max = x_max;
    m_y_min = y_min;
    m_y_max = y_max;
}

CartesianGraphDataObj::~CartesianGraphDataObj() {
    m_Vectors.clear();
    m_Particles.clear();
}

CartesianGraphDataObj &CartesianGraphDataObj::operator=(const CartesianGraphDataObj &obj) {
    if (&obj != this) {
    }
    return *this;
}


QDataStream &operator<<(QDataStream &out, const CartesianGraphDataObj &obj) {
    return out;
}

QDataStream &operator>>(QDataStream &in, CartesianGraphDataObj &obj) {\
    return in;
}
