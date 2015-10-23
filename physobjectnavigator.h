#ifndef PHYSOBJECTNAVIGATOR_H
#define PHYSOBJECTNAVIGATOR_H

#include <QTreeView>
#include <QGraphicsItem>


class PhysObjectNavigator : public QTreeView {
public:
    PhysObjectNavigator(QWidget * = NULL);

signals:
public slots:
    void newPhysObj(QGraphicsItem *);
private:

};

#endif // PHYSOBJECTNAVIGATOR_H
