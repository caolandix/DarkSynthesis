#ifndef PHYSEQSOLVERTABLE_H
#define PHYSEQSOLVERTABLE_H

#include <QtWidgets>

#include "physeqsolvertableheader.h"

class PhysEqSolverTableHeader;

class PhysEqSolverTable : public QTableWidget {
public:
    PhysEqSolverTable(QWidget * = NULL);
    PhysEqSolverTable(const int, const int, QWidget *);

    ~PhysEqSolverTable();

    void insertColumn();
    void removeColumn();
signals:
public slots:
private:
    PhysEqSolverTableHeader *m_pHeader;
};

#endif // PHYSEQSOLVERTABLE_H
