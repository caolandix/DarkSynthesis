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
    PhysObjectPropsNavigator(QWidget * = nullptr, int = 0, int = 2);

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
    PhysObjectPropEditor *m_pXaxisLabel = nullptr;
    PhysObjectPropEditor *m_pYaxisLabel = nullptr;
    PhysObjectPropEditor *m_pAxisTickInc = nullptr;
    PhysObjectPropEditor *m_pXaxisExtent = nullptr;
    PhysObjectPropEditor *m_pYaxisExten = nullptrt;
    PhysObjectPropEditor *m_pCartesianGraphName = nullptr;

    // PhysVectors
    PhysObjectPropEditor *m_pVectorMag = nullptr;
    PhysObjectPropEditor *m_pVectorThetaAngle = nullptr;
    QComboBox *m_pVectorThetaAxisOrient = nullptr;
    PhysObjectPropEditor *m_pVectorAssocParticle = nullptr;
    PhysObjectPropEditor *m_pVectorName = nullptr;

    // PhysParticles
    PhysObjectPropEditor *m_pParticleName = nullptr;
    PhysObjectPropEditor *m_pParticleMass = nullptr;
    QComboBox *m_pLockXAxis = nullptr;
    QComboBox *m_pLockYAxis = nullptr;
    PhysObjectPropEditor *m_pPosition = nullptr;

    QGraphicsItem *m_pGraphicsItem = nullptr;
};

#endif // PHYSOBJECTPROPSNAVIGATOR_H
