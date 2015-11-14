#ifndef PHYSOBJECTPROPSNAVIGATOR_H
#define PHYSOBJECTPROPSNAVIGATOR_H

#include <QTableWidget>
#include <QGraphicsItem>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QLineEdit>

#include "cartesiangraph.h"
#include "physparticle.h"
#include "physvector.h"
#include "physctrllineedit.h"

class PhysObjectPropsNavigator : public QTableWidget {
    Q_OBJECT
public:
    PhysObjectPropsNavigator(QWidget * = NULL);

    void buildCartesianGraphTable(CartesianGraph *, QGraphicsItem *);
    void buildVectorTable(PhysVector *, QGraphicsItem *);
    void buildParticleTable(PhysParticle *, QGraphicsItem *);

    void updateVectorTable(PhysVector *);
    void updateParticleTable(PhysParticle *);
    void updateCartesianGraphTable(CartesianGraph *);

    void destroyPrevTable(QGraphicsItem *);
private:
    QTableWidgetItem *createRowItem(const QString &);
signals:

public slots:
    void onChangeObj(QGraphicsItem *, QGraphicsItem *);
    void onUpdateObj(QGraphicsItem *);
private:

    // CartesianGraph
    QDoubleSpinBox *m_pXaxisTickInc;
    QDoubleSpinBox *m_pXaxisExtent;
    QDoubleSpinBox *m_pYaxisExtent;
    PhysCtrlLineEdit *m_pCartesianGraphName;

    // PhysVectors
    QDoubleSpinBox *m_pVectorMag;
    QDoubleSpinBox *m_pVectorThetaAngle;
    QComboBox *m_pVectorThetaAxisOrient;
    PhysCtrlLineEdit *m_pVectorAssocParticle;
    PhysCtrlLineEdit *m_pVectorName;

    // PhysParticles
    PhysCtrlLineEdit *m_pParticleName;
    PhysCtrlLineEdit *m_pParticleMass;

};

#endif // PHYSOBJECTPROPSNAVIGATOR_H
