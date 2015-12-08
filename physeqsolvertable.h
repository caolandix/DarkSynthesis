#ifndef PHYSEQSOLVERTABLE_H
#define PHYSEQSOLVERTABLE_H

#include <QtWidgets>

#include "physeqsolvertableheader.h"

class PhysEqSolverTable : public QTableWidget {
public:
    PhysEqSolverTable(QWidget * = NULL);
    PhysEqSolverTable(const int, const int, QWidget *);

    ~PhysEqSolverTable();

signals:
    //void customContextMenuRequested(const QPoint &);
public slots:
    void ShowContextMenu(const QPoint &);
    void insertColumn();
    void removeColumn();

private:
    PhysEqSolverTableHeader *m_pHeader;
    QAction *m_pActionInsertColumn;
    QAction *m_pActionRemoveColumn;
};

#endif // PHYSEQSOLVERTABLE_H
