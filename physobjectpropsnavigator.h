#ifndef PHYSOBJECTPROPSNAVIGATOR_H
#define PHYSOBJECTPROPSNAVIGATOR_H

#include <QTableWidget>
#include <QTableView>
#include <QGraphicsItem>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QLineEdit>

#include "cartesiangraph.h"
#include "physparticle.h"
#include "physvector.h"
#include "physctrllineedit.h"
#include "physctrldoublespinbox.h"
#include "physobjectpropeditor.h"

class PhysObjectPropsNavigator : public QTableView {
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

    void createConnections();
signals:

public slots:
    void onChangeObj(QGraphicsItem *, QGraphicsItem *);
    void onUpdateObj(QGraphicsItem *);
private:

    // CartesianGraph
    PhysObjectPropEditor *m_pXaxisLabel;
    PhysObjectPropEditor *m_pYaxisLabel;
    PhysCtrlDoubleSpinBox *m_pAxisTickInc;
    PhysCtrlDoubleSpinBox *m_pXaxisExtent;
    PhysCtrlDoubleSpinBox *m_pYaxisExtent;
    PhysObjectPropEditor *m_pCartesianGraphName;

    // PhysVectors
    PhysCtrlDoubleSpinBox *m_pVectorMag;
    PhysCtrlDoubleSpinBox *m_pVectorThetaAngle;
    QComboBox *m_pVectorThetaAxisOrient;
    PhysObjectPropEditor *m_pVectorAssocParticle;
    PhysObjectPropEditor *m_pVectorName;

    // PhysParticles
    PhysObjectPropEditor *m_pParticleName;
    PhysObjectPropEditor *m_pParticleMass;

    // The QTableWidget
    QTableWidget *m_pTable;

};

#endif // PHYSOBJECTPROPSNAVIGATOR_H
