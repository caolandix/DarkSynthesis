#ifndef PHYSEQSOLVERTABLE_H
#define PHYSEQSOLVERTABLE_H

#include <QtWidgets>

#include "physeqsolvertableheader.h"
#include "cartesiangraphdataobj.h"

class PhysEqSolverTableHeader;

class PhysEqSolverTable : public QTableWidget {
    Q_OBJECT
public:
    PhysEqSolverTable(const int, const int, QWidget *);

    ~PhysEqSolverTable();

    void insertColumn();
    void removeColumn(const int);
    void rebuildColumnHeaders();
    void createTableHeader();
    void updateColor(QTableWidgetItem *);
    void createConnections();

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    void CartesianDataObj(CartesianGraphDataObj *pObj) { m_pDataObj = pObj; }
    CartesianGraphDataObj *CartesianDataObj() const { return m_pDataObj; }
signals:
     void addPhysEqSolverRow(QList<PhysParticle *>);
     void addTimeSliceCell(int, double);
     void removeTimeSliceCell(int);
public slots:
    void onSelectColor();
    void onSelectFont();
    void onClear();
    void onCustomContextMenu(const QPoint &);
    void onSelectVelVector();
    void onSelectAccelVector();
    void onSelectGravVector();
    void onSelectDisplacementVector();
    void onSelectParticle();
    void onUpdateTimeSlices(const int, const double);
private:
    PhysEqSolverTableHeader *m_pHeader;
    CartesianGraphDataObj *m_pDataObj;
    QAction *m_pActColor;
    QAction *m_pActFont;
    QAction *m_pActClear;
    QList<double> m_TimeSliceValues;
};

#endif // PHYSEQSOLVERTABLE_H
