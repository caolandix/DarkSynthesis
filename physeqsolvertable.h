#ifndef PHYSEQSOLVERTABLE_H
#define PHYSEQSOLVERTABLE_H

#include <QtWidgets>

#include "physeqsolvertableheader.h"

class PhysEqSolverTableHeader;

class PhysEqSolverTable : public QTableWidget {
public:
    PhysEqSolverTable(const int, const int, QWidget *);

    ~PhysEqSolverTable();

    void insertColumn();
    void removeColumn(const int);
    void rebuildColumnHeaders();
    void createActions();
    void setupContextMenu();
signals:
public slots:
    void selectColor();
    void selectFont();
    void clear();
    void updateColor(QTableWidgetItem *);
private:
    PhysEqSolverTableHeader *m_pHeader;
    QAction *m_pActColor;
    QAction *m_pActFont;
    QAction *m_pActClear;
};

#endif // PHYSEQSOLVERTABLE_H
