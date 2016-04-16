#ifndef PHYSDATAOBJ_H
#define PHYSDATAOBJ_H

#include <QtWidgets>

class PhysDataObj {
public:
    typedef enum { DT_UNASSIGNED = 0, DT_CARTGRAPH, DT_PARTICLE, DT_VECTOR, DT_PROPERTY, DT_TIMESLICE } DataType;
    PhysDataObj(const QString str, DataType dt, const double x = 0.0, const double y = 0.0) : m_Name(str), m_Type(dt), m_xpos(x), m_ypos(y) {}
    PhysDataObj(const PhysDataObj &obj) : m_Name(obj.Name()) {}
    PhysDataObj(const PhysDataObj *pObj) : m_Name(pObj ->Name()) {}
    virtual ~PhysDataObj() {}

    QString Name() const { return m_Name; }
    void Name(const QString Name) { m_Name = Name; }
    DataType Type() const { return m_Type; }
    double xcoord() const { return m_xpos; }
    double ycoord() const { return m_ypos; }
    void xcoord(const double val) { m_xpos = val; }
    void ycoord(const double val) { m_ypos = val; }
    void updatePos(const double x, const double y) { m_xpos = x; m_ypos = y; }

protected:
    QString m_Name;
    DataType m_Type;
    double m_xpos, m_ypos;
};
QDataStream &operator<<(QDataStream &out, const PhysDataObj &obj);
QDataStream &operator>>(QDataStream &in, PhysDataObj &obj);
Q_DECLARE_METATYPE(const PhysDataObj *)
Q_DECLARE_METATYPE(PhysDataObj *)
#endif // PHYSDATAOBJ_H
