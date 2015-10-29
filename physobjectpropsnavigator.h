#ifndef PHYSOBJECTPROPSNAVIGATOR_H
#define PHYSOBJECTPROPSNAVIGATOR_H

#include <QTableWidget>
#include <QGraphicsItem>
#include <QSpinBox>

class PhysObjectPropsNavigator : public QTableWidget {
    Q_OBJECT
public:
    PhysObjectPropsNavigator(QWidget * = NULL);

    void buildCartesianGraphTable(QGraphicsItem *);
    void buildVectorTable(QGraphicsItem *);
    void buildParticleTable(QGraphicsItem *);
signals:

public slots:
    void onChangeObj(QGraphicsItem *);

private:
    QSpinBox *m_pXaxisTickInc;
    QSpinBox *m_pXaxisExtent;
    QSpinBox *m_pYaxisExtent;
};

#endif // PHYSOBJECTPROPSNAVIGATOR_H
