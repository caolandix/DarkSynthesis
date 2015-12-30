#ifndef PHYSDATAOBJ_H
#define PHYSDATAOBJ_H

#include <QtWidgets>

class PhysDataObj {
public:
    typedef enum { DT_CARTGRAPH = 0, DT_PARTICLE, DT_VECTOR, DT_PROPERTY, DT_TIMESLICE } DataType;
    PhysDataObj(const QString str, DataType Type) : m_Name(str), m_Type(Type) {}
    PhysDataObj(const PhysDataObj &obj) : m_Name(obj.Name()) {}
    PhysDataObj(const PhysDataObj *pObj) : m_Name(pObj ->Name()) {}
    virtual ~PhysDataObj() {}

    QString Name() const { return m_Name; }
    void Name(const QString Name) { m_Name = Name; }
    DataType Type() const { return m_Type; }

protected:
    QString m_Name;
    DataType m_Type;
};
QDataStream &operator<<(QDataStream &out, const PhysDataObj &obj);
QDataStream &operator>>(QDataStream &in, PhysDataObj &obj);
Q_DECLARE_METATYPE(const PhysDataObj *)
Q_DECLARE_METATYPE(PhysDataObj *)
#endif // PHYSDATAOBJ_H
