#ifndef PHYSOBJECTPROPSNAVIGATOR_H
#define PHYSOBJECTPROPSNAVIGATOR_H

#include <QTableWidget>
#include <QGraphicsItem>
#include <QDoubleSpinBox>
#include <QComboBox>

#include "cartesiangraph.h"
#include "physparticle.h"
#include "physvector.h"

class PhysObjectPropsNavigator : public QTableWidget {
    Q_OBJECT
public:
    PhysObjectPropsNavigator(QWidget * = NULL);

    void buildCartesianGraphTable(CartesianGraph *);
    void buildVectorTable(PhysVector *);
    void buildParticleTable(PhysParticle *);
signals:

public slots:
    void onChangeObj(QGraphicsItem *);

private:

    // CartesianPlane
    QDoubleSpinBox *m_pXaxisTickInc;
    QDoubleSpinBox *m_pXaxisExtent;
    QDoubleSpinBox *m_pYaxisExtent;

    // Vectors
    QDoubleSpinBox *m_pVectorMag;
    QDoubleSpinBox *m_pVectorThetaAngle;
    QComboBox *m_pVectorThetaAxisOrient;

    // Particles

};

#endif // PHYSOBJECTPROPSNAVIGATOR_H
