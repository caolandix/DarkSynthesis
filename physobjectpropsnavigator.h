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
#include "physobjectpropeditor.h"

class PhysObjectPropsNavigator : public QTableWidget {
    Q_OBJECT
public:
    PhysObjectPropsNavigator(QWidget * = NULL, int = 0, int = 2);

    void buildCartesianGraphTable(CartesianGraph *, QGraphicsItem *);
    void buildVectorTable(PhysVector *, QGraphicsItem *);
    void buildParticleTable(PhysParticle *, QGraphicsItem *);

    void updateVectorTable(PhysVector *);
    void updateParticleTable(PhysParticle *);
    void updateCartesianGraphTable(CartesianGraph *);

    void destroyPrevTable(QGraphicsItem *);
private:
    QTableWidgetItem *createRowItem(const QString &);
    void createTable(const int, const int);
signals:
    void repaint();
    void updateParticleName(const QString, const QString);
public slots:
    void onChangeObj(QGraphicsItem *, QGraphicsItem *);
    void onUpdateObj(QGraphicsItem *);
    void onUpdateControl();
private:

    // CartesianGraph
    PhysObjectPropEditor *m_pXaxisLabel;
    PhysObjectPropEditor *m_pYaxisLabel;
    PhysObjectPropEditor *m_pAxisTickInc;
    PhysObjectPropEditor *m_pXaxisExtent;
    PhysObjectPropEditor *m_pYaxisExtent;
    PhysObjectPropEditor *m_pCartesianGraphName;

    // PhysVectors
    PhysObjectPropEditor *m_pVectorMag;
    PhysObjectPropEditor *m_pVectorThetaAngle;
    QComboBox *m_pVectorThetaAxisOrient;
    PhysObjectPropEditor *m_pVectorAssocParticle;
    PhysObjectPropEditor *m_pVectorName;
    PhysObjectPropEditor *m_pVectorXPos;
    PhysObjectPropEditor *m_pVectorYPos;

    // PhysParticles
    PhysObjectPropEditor *m_pParticleName;
    PhysObjectPropEditor *m_pParticleMass;
    QComboBox *m_pLockXAxis;
    QComboBox *m_pLockYAxis;
    PhysObjectPropEditor *m_pPosition;

    QGraphicsItem *m_pGraphicsItem;
};

#endif // PHYSOBJECTPROPSNAVIGATOR_H
