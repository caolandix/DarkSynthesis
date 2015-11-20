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
#include "physctrldoublespinbox.h"

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
    void deleteControls();
private:
    QTableWidgetItem *createRowItem(const QString &);
signals:

public slots:
    void onChangeObj(QGraphicsItem *, QGraphicsItem *);
    void onUpdateObj(QGraphicsItem *);
private:

    // CartesianGraph
    PhysCtrlLineEdit *m_pXaxisLabel;
    PhysCtrlLineEdit *m_pYaxisLabel;
    PhysCtrlDoubleSpinBox *m_pAxisTickInc;
    PhysCtrlDoubleSpinBox *m_pXaxisExtent;
    PhysCtrlDoubleSpinBox *m_pYaxisExtent;
    PhysCtrlLineEdit *m_pCartesianGraphName;

    // PhysVectors
    PhysCtrlDoubleSpinBox *m_pVectorMag;
    PhysCtrlDoubleSpinBox *m_pVectorThetaAngle;
    QComboBox *m_pVectorThetaAxisOrient;
    PhysCtrlLineEdit *m_pVectorAssocParticle;
    PhysCtrlLineEdit *m_pVectorName;

    // PhysParticles
    PhysCtrlLineEdit *m_pParticleName;
    PhysCtrlLineEdit *m_pParticleMass;

};

#endif // PHYSOBJECTPROPSNAVIGATOR_H
