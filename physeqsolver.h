#ifndef PHYSEQSOLVER_H
#define PHYSEQSOLVER_H

#include <map>

#include <QtWidgets>

#include "jumpdrive/ValueSet.h"
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
    QList<PhysEqRow *> Rows() const { return m_lstRows; }

private:
    void createParticleItems(int, PhysParticle *);
    void create1DKinematicItems(int, PhysParticle *);
    QTableWidgetItem *createRowItem(PhysDataObj *);
    QTableWidgetItem *createTableItem(PhysDataObj *, bool = false);
    void setGridTextAtRowColumn(const int, const int, const double);

    void createConnections();
    void createTable(const int, const int);
    void setupTableLookAndFeel();
    void setupContextMenu();

    bool resolveEquation(ValueSet &vs, const string equation);
    QString calculateRows(QList<PhysEqRow *>::Iterator &iter, QString, const double dt = -1, bool bStripConsts = false);
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
    QList<PhysParticle *> m_lstParticles;
    PhysCalculateTimer *m_pCalcTimer;
    QString m_eqJumpDrive, m_strVarAssignments;
    map<string, bool> m_eqTokensMap;
    QList<PhysEqRow *>::Iterator m_iterCurrRow;

};

#endif // PHYSEQSOLVER_H
