#ifndef PHYSMODULE_H
#define PHYSMODULE_H

#include <QString>

class PhysModule {
public:
    PhysModule(const QString &);
    PhysModule(const PhysModule &);
    virtual ~PhysModule();

    PhysModule& operator=(const PhysModule &);
    QString Name() const { return m_Name; }

private:
    QString m_Name;
};

#endif // PHYSMODULE_H
