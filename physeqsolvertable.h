#ifndef PHYSEQSOLVERTABLE_H
#define PHYSEQSOLVERTABLE_H

#include <QtWidgets>


class PhysEqSolverTable : public QTableWidget {
public:
    PhysEqSolverTable(QWidget * = NULL);
    PhysEqSolverTable(const int, const int, QWidget *);

    ~PhysEqSolverTable();

private:

signals:

public slots:
};

#endif // PHYSEQSOLVERTABLE_H
