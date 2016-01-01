#ifndef PHYSEQSOLVER_H
#define PHYSEQSOLVER_H

#include <QtWidgets>

#include "physeqsolvertable.h"
#include "physeqrow.h"
#include "physeqgrid.h"
#include "physcommon.h"
#include "physdataobj.h"
#include "physcalculatetimer.h"

class PhysEqSolver : public QTableView, public PhysCommon {
    Q_OBJECT
public:
    PhysEqSolver(int rows = 0, int cols = 1, QWidget * = NULL);

    void CartesianDataObj(CartesianGraphDataObj *pObj) { m_pTable -> CartesianDataObj(pObj); }
    QList<PhysParticle *> Particles() const { return m_pTable -> CartesianDataObj() ->Particles(); }
    QList<PhysVector *> Vectors() const { return m_pTable -> CartesianDataObj() ->Vectors(); }

    PhysEqSolverTable *Table() const { return m_pTable; }

private:
    void createParticleItems(int, PhysParticle *);
    void create1DKinematicItems(int, PhysParticle *);
    QTableWidgetItem *createRowItem(PhysDataObj *);
    QTableWidgetItem *createTableItem(PhysDataObj *, bool = false);

    void createConnections();
    void createTable(const int, const int);
    void setupTableLookAndFeel();
    void createGrid();
    void setupContextMenu();

    void DecodeAddy(const QString, int *, int * = NULL);
    QString EncodeAddy(const int, const int = -1);
    void createTimeSliceRow(QList<double>);
    void addPhysDataObjCell(const int row, const int col, const QString, const double val);

    void createPhysDataObjRow(PhysDataObj *);
public slots:
    void updateLineEdit(QTableWidgetItem *);
    void returnPressed();
    void onAddPhysEqSolverRow(QList<PhysParticle *>);
    void onCalculate();
    void onUpdateParticleName(const QString, const QString);
    void onAddTimeSliceCell(int, double);
    void onRemoveTimeSliceCell(int);
    void onCartesianGraphCreated(CartesianGraphDataObj *pObj) { m_pTable ->CartesianDataObj(pObj); }
    void onSetModType(int modType) {}
signals:
private:
    PhysEqSolverTable *m_pTable;
    QLineEdit *m_pFormulaInput;
    QList<PhysEqRow *> m_lstRows;
    PhysEqGrid *m_pGrid;
    QList<PhysParticle *> m_lstParticles;
    PhysCalculateTimer *m_pCalcTimer;
};

#endif // PHYSEQSOLVER_H
