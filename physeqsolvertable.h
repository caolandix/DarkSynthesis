#ifndef PHYSEQSOLVERTABLE_H
#define PHYSEQSOLVERTABLE_H

#include <QtWidgets>

#include "physeqsolvertableheader.h"
#include "cartesiangraphdataobj.h"
#include "physcommon.h"
#include "physeqrow.h"
#include "physcalculatetimer.h"
#include "jumpdrive/ValueSet.h"
#include "physeqgrid.h"
#include "physdataobj.h"

class PhysEqSolverTableHeader;

class PhysEqSolverTable : public QTableWidget, public PhysCommon {
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
    void setupTableLookAndFeel();

    static void DecodeAddy(const QString, int *, int * = NULL);
    static QString EncodeAddy(const int, const int = -1);

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    QList<PhysParticle *> Particles() const { return CartesianDataObj() ->Particles(); }
    QList<PhysVector *> Vectors() const { return CartesianDataObj() ->Vectors(); }
    QList<PhysEqRow *> Rows() const { return m_lstRows; }


    void CartesianDataObj(CartesianGraphDataObj *pObj) { m_pDataObj = pObj; }
    CartesianGraphDataObj *CartesianDataObj() const { return m_pDataObj; }
    QList<double> TimeSliceValues() const { return m_TimeSliceValues; }
    double TimeSlice(const  int idx) const { return m_TimeSliceValues.at(idx); }

private:
    void printRow(PhysEqRow *, int i);
    void createParticleItems(int, PhysParticle *);
    void create1DKinematicItems(int, PhysParticle *);
    QTableWidgetItem *createRowItem(PhysDataObj *);
    QTableWidgetItem *createTableItem(PhysEqRow *, bool = false);
    void setGridTextAtRowColumn(const int, const int, const double);

    void createTable(const int, const int);

    bool resolveEquation(ValueSet &vs, const string equation);
    QString calculateRows(QList<PhysEqRow *>::Iterator &iter, QString, const double dt = -1, bool bStripConsts = false);
    void createTimeSliceRow(QList<double>);
    void addPhysDataObjCell(const int row, const int col, const QString, const double val);
    PhysEqRow *createPhysDataObjRow(PhysDataObj *);
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
    void updateLineEdit(QTableWidgetItem *);
    void returnPressed();
    void onAddPhysEqSolverRow(QList<PhysParticle *>);
    void onCalculate();
    void onUpdateParticleName(const QString, const QString);
    void onAddTimeSliceCell(int, double);
    void onRemoveTimeSliceCell(int);
    void onCartesianGraphCreated(CartesianGraphDataObj *pObj) { CartesianDataObj(pObj); }
    void onSetModType(int modType) {}
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

    QLineEdit *m_pFormulaInput;
    QList<PhysEqRow *> m_lstRows;
    QList<PhysParticle *> m_lstParticles;
    PhysCalculateTimer *m_pCalcTimer;
    QString m_eqJumpDrive, m_strVarAssignments;
    map<string, bool> m_eqTokensMap;
    QList<PhysEqRow *>::Iterator m_iterCurrRow;

};

#endif // PHYSEQSOLVERTABLE_H
