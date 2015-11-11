#ifndef PHYSOBJECTNAVIGATOR_H
#define PHYSOBJECTNAVIGATOR_H

#include <QTreeWidget>
#include <QGraphicsItem>
#include <QTreeWidgetItem>
#include <QItemSelection>
#include <QDropEvent>

#include "cartesiangraph.h"
#include "physvector.h"
#include "physparticle.h"

class PhysObjectNavigator : public QTreeWidget {
    Q_OBJECT
public:
    PhysObjectNavigator(QWidget * = NULL);

    QGraphicsItem *currObj() const { return m_pCurrObj; }
    QGraphicsItem *prevObj() const { return m_pPrevObj; }
protected:
    void currentChanged(const QModelIndex &, const QModelIndex &);
    void selectionChanged(const QItemSelection &, const QItemSelection &);
    void dropEvent(QDropEvent *);
private:
    void insertCartesianGraph(CartesianGraph *);
    void insertVector(PhysVector *);
    void insertParticle(PhysParticle *);

signals:
    void changeObj(QGraphicsItem *, QGraphicsItem *);
    void updateObj(QGraphicsItem *);
public slots:
    void onCreateObj(QGraphicsItem *);
private:

    QGraphicsItem *m_pCurrObj, *m_pPrevObj;

};

#endif // PHYSOBJECTNAVIGATOR_H
