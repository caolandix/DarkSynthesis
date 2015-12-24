#ifndef PHYSEQSOLVER_H
#define PHYSEQSOLVER_H

#include <QtWidgets>

#include "physeqsolvertable.h"
#include "physeqrow.h"
#include "physcommon.h"

class PhysEqSolver : public QTableView, public PhysCommon {
    Q_OBJECT
public:
    typedef QList<PhysEqRow *> PhysEqRowList;


    PhysEqSolver(int rows = 0, int cols = 1, QWidget * = NULL);

    void createConnections();
    void createTable(const int, const int);

    void CartesianDataObj(CartesianGraphDataObj *pObj) { m_pTable -> CartesianDataObj(pObj); }
    QList<PhysParticle *> Particles() const { return m_pTable -> CartesianDataObj() ->Particles(); }
    QList<PhysVector *> Vectors() const { return m_pTable -> CartesianDataObj() ->Vectors(); }

private:
    void createParticleItems(int, PhysParticle *);
    void create1DKinematicItems(int, PhysParticle *);
    QTableWidgetItem *createRowItem(PhysVectorDataObj *);
    QTableWidgetItem *createRowItem(PhysParticleDataObj *);
public slots:
    void updateLineEdit(QTableWidgetItem *);
    void returnPressed();
    void actionSum();
    void onCartesianGraphCreated(CartesianGraphDataObj *pObj) { m_pTable ->CartesianDataObj(pObj); }
    void onAddPhysEqSolverRow(QList<PhysParticle *>);
    void Calculate();

signals:
protected:
    void setupContextMenu();
    void setupContents();
private:
    PhysEqSolverTable *m_pTable;
    QLineEdit *m_pFormulaInput;
    PhysEqRowList m_lstRows;
    QList<PhysParticle *> m_lstParticles;
    QTimer *m_pCalcTimer;
    unsigned int m_CalcInterval;
};

void decode_pos(const QString &, int *, int *);
QString encode_pos(int, int );

#endif // PHYSEQSOLVER_H
