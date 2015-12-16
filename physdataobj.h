#ifndef PHYSDATAOBJ_H
#define PHYSDATAOBJ_H

#include <QString>

class PhysDataObj {
public:
    PhysDataObj(const QString str) : m_Name(str) {}
    PhysDataObj(const PhysDataObj &obj) : m_Name(obj.Name()) {}
    PhysDataObj(const PhysDataObj *pObj) : m_Name(pObj ->Name()) {}
    virtual ~PhysDataObj() {}

    QString Name() const { return m_Name; }
    void Name(const QString Name) { m_Name = Name; }

protected:
    QString m_Name;
};

#endif // PHYSDATAOBJ_H
