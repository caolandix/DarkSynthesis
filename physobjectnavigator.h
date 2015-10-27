#ifndef PHYSOBJECTNAVIGATOR_H
#define PHYSOBJECTNAVIGATOR_H

#include <QTreeView>
#include <QGraphicsItem>


class PhysObjectNavigator : public QTreeView {
    Q_OBJECT
public:
    PhysObjectNavigator(QWidget * = NULL);

public slots:
    void onCreateObj(QGraphicsItem *);
private:

};

#endif // PHYSOBJECTNAVIGATOR_H
