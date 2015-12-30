#ifndef PHYSMODULENAVIGATOR_H
#define PHYSMODULENAVIGATOR_H

#include <QtWidgets>

#include "physmodule.h"
#include "physcommon.h"

class PhysModuleNavigator : public QListWidget, public PhysCommon {
    Q_OBJECT
public:
    PhysModuleNavigator(QWidget * = NULL);
signals:
    void setModType(int);
public slots:

private:
    QList<PhysModule *> m_ModuleList;
};

#endif // PHYSMODULENAVIGATOR_H
