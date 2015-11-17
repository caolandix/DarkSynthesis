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
    void selectionChanged(const QItemSelection &, const QItemSelection &);
    void dropEvent(QDropEvent *);
private:
    void insertCartesianGraph(CartesianGraph *);
    void insertVector(PhysVector *);
    void insertParticle(PhysParticle *);
    void createContextMenu();
signals:
    void changeObj(QGraphicsItem *, QGraphicsItem *);
    void updateObj(QGraphicsItem *);
public slots:
    void onCreateObj(QGraphicsItem *);
    void onCustomContextMenu(const QPoint &);

    void createObject();
    void cloneObject();
    void deleteObject();
    void resetObject();
private:
    QGraphicsItem *m_pCurrObj, *m_pPrevObj;
    QAction *m_pActNewItem, *m_pActCloneItem, *m_pActDeleteItem, *m_pActResetItem;

};

#endif // PHYSOBJECTNAVIGATOR_H
