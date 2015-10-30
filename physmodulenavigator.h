#ifndef PHYSMODULENAVIGATOR_H
#define PHYSMODULENAVIGATOR_H

#include <QListWidget>
#include <QList>

#include "physmodule.h"

class PhysModuleNavigator : public QListWidget {
    Q_OBJECT
public:
    PhysModuleNavigator(QWidget * = NULL);
signals:

public slots:

private:
    QList<PhysModule *> m_ModuleList;
};

#endif // PHYSMODULENAVIGATOR_H
