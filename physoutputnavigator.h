#ifndef PHYSOUTPUTNAVIGATOR_H
#define PHYSOUTPUTNAVIGATOR_H

#include <QWidget>
#include <QTabWidget>
#include <QGraphicsItem>

class PhysOutputNavigator : public QTabWidget {
    Q_OBJECT
public:
    PhysOutputNavigator(QWidget * = NULL);

signals:

public slots:
    void onCreateObj(QGraphicsItem *);
};

#endif // PHYSOUTPUTNAVIGATOR_H
