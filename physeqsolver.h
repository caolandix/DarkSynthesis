#ifndef PHYSEQSOLVER_H
#define PHYSEQSOLVER_H

#include <QtWidgets>

#include "physeqsolvertable.h"
#include "physeqgrid.h"

class PhysEqSolver : public QTableView {
    Q_OBJECT
public:
    PhysEqSolver(int rows = 0, int cols = 1, QWidget * = NULL);

    void createConnections();
    void createTable(const int, const int);

    void CartesianDataObj(CartesianGraphDataObj *pObj) { m_pTable -> CartesianDataObj(pObj); }
    QList<PhysParticle *> Particles() const { return m_pTable -> CartesianDataObj() ->Particles(); }
    QList<PhysVector *> Vectors() const { return m_pTable -> CartesianDataObj() ->Vectors(); }
public slots:
    void updateLineEdit(QTableWidgetItem *);
    void returnPressed();
    void actionSum();
    void onCartesianGraphCreated(CartesianGraphDataObj *pObj) { m_pTable ->CartesianDataObj(pObj); }
    void onAddPhysEqSolverRow(QString);
    void onRecvParticle(PhysParticle *);

signals:
     void addPhysEqSolverRow(QString);
     void requestParticle();
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
