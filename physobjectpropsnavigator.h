#ifndef PHYSOBJECTPROPSNAVIGATOR_H
#define PHYSOBJECTPROPSNAVIGATOR_H

#include <QTableWidget>
#include <QGraphicsItem>

class PhysObjectPropsNavigator : public QTableWidget {
    Q_OBJECT
public:
    PhysObjectPropsNavigator(QWidget * = NULL);

    void buildPropertyTable(QGraphicsItem *);
signals:

public slots:
    void onChangeObj(QGraphicsItem *);
};

#endif // PHYSOBJECTPROPSNAVIGATOR_H
