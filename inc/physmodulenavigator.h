#ifndef PHYSMODULENAVIGATOR_H
#define PHYSMODULENAVIGATOR_H

#include <QtWidgets>

#include "physmodule.h"
#include "physcommon.h"

class PhysModuleNavigator : public QListView, public PhysCommon {
    Q_OBJECT
public:
    PhysModuleNavigator(QWidget * = NULL);
    ~PhysModuleNavigator();
signals:
    void setModType(int);
public slots:

private:
};

#endif // PHYSMODULENAVIGATOR_H
