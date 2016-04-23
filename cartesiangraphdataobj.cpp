#include "cartesiangraphdataobj.h"

CartesianGraphDataObj::CartesianGraphDataObj(const QString Name) : PhysDataObj(Name, DT_CARTGRAPH) {
    init();
}

CartesianGraphDataObj::CartesianGraphDataObj(const QPointF origin, const double tickStep, const int tickLength, const double x_min,
                                             const double x_max, const double y_min, const double y_max,
                                             const QString Name) : PhysDataObj(Name, DT_CARTGRAPH) {
    m_origin = origin;
    m_tickStep = tickStep;
    m_tickLength = tickLength;
    m_x_min = x_min;
    m_x_max = x_max;
    m_y_min = y_min;
    m_y_max = y_max;
}

void CartesianGraphDataObj::copyData(const CartesianGraphDataObj &obj) {
    m_origin = obj.m_origin;
    m_tickStep = obj.m_tickStep;
    m_tickLength = obj.m_tickLength;
    m_x_min = obj.m_x_min;
    m_x_max = obj.m_x_max;
    m_y_min = obj.m_y_min;
    m_y_max = obj.m_y_max;
    m_Vectors.clear();
    foreach (PhysVector *pVec, obj.Vectors())
        m_Vectors.append(pVec);
    m_Particles.clear();
    foreach (PhysParticle *pPart, obj.Particles())
        m_Particles.append(pPart);
}

void CartesianGraphDataObj::copyData(const CartesianGraphDataObj *pObj) {
    m_origin = pObj -> origin();
    m_tickStep = pObj -> tickStep();
    m_tickLength = pObj -> tickLength();
    m_x_min = pObj -> xMin();
    m_x_max = pObj -> xMax();
    m_y_min = pObj -> yMin();
    m_y_max = pObj -> yMax();
    m_Vectors.clear();
    foreach (PhysVector *pVec, pObj -> Vectors())
        m_Vectors.append(pVec);
    m_Particles.clear();
    foreach (PhysParticle *pPart, pObj -> Particles())
        m_Particles.append(pPart);
}

CartesianGraphDataObj::CartesianGraphDataObj(const CartesianGraphDataObj *pObj) : PhysDataObj(pObj) {
    copyData(pObj);
}

CartesianGraphDataObj::CartesianGraphDataObj(const CartesianGraphDataObj &obj) : PhysDataObj(obj) {
    copyData(obj);
}

CartesianGraphDataObj::~CartesianGraphDataObj() {
    init();
}

void CartesianGraphDataObj::init() {
    m_Vectors.clear();
    m_Particles.clear();

    m_tickStep = 10.0;
    m_tickLength = 4;
    m_origin = QPointF(0.0, 0.0);
    m_x_min = -100;
    m_x_max = 100;
    m_y_min = -100;
    m_y_max = 100;
}

CartesianGraphDataObj &CartesianGraphDataObj::operator=(const CartesianGraphDataObj &obj) {
    if (&obj != this)
        copyData(obj);
    return *this;
}


QDataStream &operator<<(QDataStream &out, const CartesianGraphDataObj &obj) {
    return out;
}

QDataStream &operator>>(QDataStream &in, CartesianGraphDataObj &obj) {
    return in;
}
