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
public slots:
    void updateColor(QTableWidgetItem *);
    void updateLineEdit(QTableWidgetItem *);
    void returnPressed();
    void selectColor();
    void selectFont();
    void clear();
    void actionSum();
    void onAppendTimeColumn();
    void onInsertTimeColumn();
    void onRemoveTimeColumn();
protected:
    void setupContextMenu();
    void setupContents();
    void createActions();
    void actionMath_helper(const QString &, const QString &);
    bool runInputDialog(const QString &, const QString &, const QString &, const QString &,
                        const QString &, QString *, QString *, QString *);
private:
    QAction *m_pActColor;
    QAction *m_pActFont;
    QAction *m_pActClear;
    QAction *m_pActAppendTimeColumn;
    QAction *m_pActInsertTimeColumn;
    QAction *m_pActRemoveTimeColumn;
    PhysEqSolverTable *m_pTable;
    QLineEdit *m_pFormulaInput;
    PhysEqGrid m_Grid;
};

void decode_pos(const QString &, int *, int *);
QString encode_pos(int, int );

#endif // PHYSEQSOLVER_H
