#ifndef PHYSEQSOLVERTABLE_H
#define PHYSEQSOLVERTABLE_H

#include <QtWidgets>

#include "physeqsolvertableheader.h"
#include "cartesiangraphdataobj.h"

class PhysEqSolverTableHeader;

class PhysEqSolverTable : public QTableWidget {
    Q_OBJECT
public:
    typedef struct _ctxmnuCurrItem {
        int row, column;
    } CurrItemStruct;

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
    QList<double> TimeSliceValues() const { return m_TimeSliceValues; }
    double TimeSlice(const  int idx) const { return m_TimeSliceValues.at(idx); }
signals:
     void addPhysEqSolverRow(QList<PhysParticle *>);
     void addTimeSliceCell(int, double);
     void removeTimeSliceCell(int);
public slots:
    void onSelectColor();
    void onSelectFont();
    void onClear();
    void onCustomContextMenu(const QPoint &);
    void onRowProperties();
    void onSelectVelVector();
    void onSelectAccelVector();
    void onSelectGravVector();
    void onSelectDisplacementVector();
    void onSelectParticle();
    void onUpdateTimeSlices(const int, const double);
private:
    QWidget *m_pParent;
    PhysEqSolverTableHeader *m_pHeader;
    CartesianGraphDataObj *m_pDataObj;
    QAction *m_pActColor;
    QAction *m_pActFont;
    QAction *m_pActClear;
    QAction *m_pRowProperties;
    QList<double> m_TimeSliceValues;
    CurrItemStruct m_currItem;
};

#endif // PHYSEQSOLVERTABLE_H
