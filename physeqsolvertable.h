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

    void CartesianDataObj(CartesianGraphDataObj *pObj) { m_pDataObj = pObj; }
    CartesianGraphDataObj *CartesianDataObj() const { return m_pDataObj; }
signals:
     void addPhysEqSolverRow(QString);
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
private:
    PhysEqSolverTableHeader *m_pHeader;
    CartesianGraphDataObj *m_pDataObj;
    QAction *m_pActColor;
    QAction *m_pActFont;
    QAction *m_pActClear;
};

#endif // PHYSEQSOLVERTABLE_H
