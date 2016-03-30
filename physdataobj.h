#ifndef PHYSDATAOBJ_H
#define PHYSDATAOBJ_H

#include <QtWidgets>

class PhysDataObj {
public:
    typedef enum { DT_UNASSIGNED = 0, DT_CARTGRAPH, DT_PARTICLE, DT_VECTOR, DT_PROPERTY, DT_TIMESLICE } DataType;
    PhysDataObj(const QString str, DataType dt, const QPointF pos) : m_Name(str), m_Type(dt), m_position(pos) {}
    PhysDataObj(const PhysDataObj &obj) : m_Name(obj.Name()) {}
    PhysDataObj(const PhysDataObj *pObj) : m_Name(pObj ->Name()) {}
    virtual ~PhysDataObj() {}

    QString Name() const { return m_Name; }
    void Name(const QString Name) { m_Name = Name; }
    DataType Type() const { return m_Type; }
    QPointF Position() const { return m_position; }
    void Position(const QPointF pos) { m_position = pos; }

protected:
    QString m_Name;
    DataType m_Type;
    QPointF m_position;
};
QDataStream &operator<<(QDataStream &out, const PhysDataObj &obj);
QDataStream &operator>>(QDataStream &in, PhysDataObj &obj);
Q_DECLARE_METATYPE(const PhysDataObj *)
Q_DECLARE_METATYPE(PhysDataObj *)
#endif // PHYSDATAOBJ_H
