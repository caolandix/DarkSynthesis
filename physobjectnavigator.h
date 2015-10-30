#ifndef PHYSOBJECTNAVIGATOR_H
#define PHYSOBJECTNAVIGATOR_H

#include <QTreeWidget>
#include <QGraphicsItem>
#include <QTreeWidgetItem>
#include <QItemSelection>

#include "cartesiangraph.h"
#include "physvector.h"
#include "physparticle.h"

class PhysObjectNavigator : public QTreeWidget {
    Q_OBJECT
public:
    PhysObjectNavigator(QWidget * = NULL);
protected:
    virtual void currentChanged(const QModelIndex &current, const QModelIndex &previous);
private:
    void insertCartesianGraph(CartesianGraph *);
    void insertVector(PhysVector *);
    void insertParticle(PhysParticle *);

signals:
    void changeObj(QGraphicsItem *);
public slots:
    void onCreateObj(QGraphicsItem *);
private:

};

#endif // PHYSOBJECTNAVIGATOR_H
