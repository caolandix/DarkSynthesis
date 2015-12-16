#include "cartesiangraphdataobj.h"

CartesianGraphDataObj::CartesianGraphDataObj(const QString Name) : PhysDataObj(Name) {
    init();
}

CartesianGraphDataObj::CartesianGraphDataObj(QPointF origin, double tickStep, double x_min,
                                             double x_max, double y_min, double y_max,
                                             const QString Name) : PhysDataObj(Name) {
    m_origin = origin;
    m_tickStep = tickStep;
    m_x_min = x_min;
    m_x_max = x_max;
    m_y_min = y_min;
    m_y_max = y_max;
}

CartesianGraphDataObj::CartesianGraphDataObj(const CartesianGraphDataObj *pObj) : PhysDataObj(pObj) {
    m_origin = pObj -> origin();
    m_tickStep = pObj -> tickStep();
    m_x_min = pObj -> xMin();
    m_x_max = pObj -> xMax();
    m_y_min = pObj -> yMin();
    m_y_max = pObj -> yMax();
}

CartesianGraphDataObj::CartesianGraphDataObj(const CartesianGraphDataObj &Obj) : PhysDataObj(Obj) {
    m_origin = Obj.m_origin;
    m_tickStep = Obj.m_tickStep;
    m_x_min = Obj.m_x_min;
    m_x_max = Obj.m_x_max;
    m_y_min = Obj.m_y_min;
    m_y_max = Obj.m_y_max;
}

CartesianGraphDataObj::~CartesianGraphDataObj() {
    init();
}

void CartesianGraphDataObj::init() {
    m_Vectors.clear();
    m_Particles.clear();

    m_tickStep = 10.0;
    m_origin = QPointF(0.0, 0.0);
    m_x_min = -100;
    m_x_max = 100;
    m_y_min = -100;
    m_y_max = 100;
}

CartesianGraphDataObj &CartesianGraphDataObj::operator=(const CartesianGraphDataObj &obj) {
    if (&obj != this) {
    }
    return *this;
}


QDataStream &operator<<(QDataStream &out, const CartesianGraphDataObj &obj) {
    return out;
}

QDataStream &operator>>(QDataStream &in, CartesianGraphDataObj &obj) {
    return in;
}
