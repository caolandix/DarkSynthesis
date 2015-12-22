#ifndef PHYSEQSOLVER_H
#define PHYSEQSOLVER_H

#include <QtWidgets>

#include "physeqsolvertable.h"
#include "physeqgrid.h"
#include "physcommon.h"

class PhysEqSolver : public QTableView, PhysCommon {
    Q_OBJECT
public:
    PhysEqSolver(int rows = 0, int cols = 1, QWidget * = NULL);

    void createConnections();
    void createTable(const int, const int);

    void CartesianDataObj(CartesianGraphDataObj *pObj) { m_pTable -> CartesianDataObj(pObj); }
    QList<PhysParticle *> Particles() const { return m_pTable -> CartesianDataObj() ->Particles(); }
    QList<PhysVector *> Vectors() const { return m_pTable -> CartesianDataObj() ->Vectors(); }

private:
    void createParticleItems(const int, const PhysParticle *);
    void create1DKinematicItems(const int, const PhysParticle *);
    QTableWidgetItem *createRowItem(const QString &);
public slots:
    void updateLineEdit(QTableWidgetItem *);
    void returnPressed();
    void actionSum();
    void onCartesianGraphCreated(CartesianGraphDataObj *pObj) { m_pTable ->CartesianDataObj(pObj); }
    void onAddPhysEqSolverRow(QList<PhysParticle *>);
    void onSetModType(int val) { ModType((PhysModuleType)val); }

signals:
protected:
    void setupContextMenu();
    void setupContents();
private:
    PhysEqSolverTable *m_pTable;
    QLineEdit *m_pFormulaInput;
    PhysEqGrid m_Grid;
    QList<PhysParticle *> m_lstParticles;
};

void decode_pos(const QString &, int *, int *);
QString encode_pos(int, int );

#endif // PHYSEQSOLVER_H
