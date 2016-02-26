#include "physmodule.h"

PhysModule::PhysModule(const QString &str, QObject *pParent) : QObject(pParent) {
    m_Name = str;
}

PhysModule::PhysModule(const PhysModule &obj) : QObject() {
    m_Name = obj.Name();
}

PhysModule::~PhysModule() {
}

PhysModule& PhysModule::operator=(const PhysModule &obj) {
    if (&obj != this) {
        m_Name = obj.Name();
    }
    return *this;
}
