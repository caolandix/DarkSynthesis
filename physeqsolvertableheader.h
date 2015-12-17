#ifndef PHYSEQSOLVERTABLEHEADER_H
#define PHYSEQSOLVERTABLEHEADER_H


#include <QtWidgets>
#include "physeqsolvertable.h"
class PhysEqSolverTable;

class PhysEqSolverTableHeader : public QHeaderView {
    Q_OBJECT
public:
    PhysEqSolverTableHeader(QWidget *);

signals:
public slots:
    void onShowContextMenu(const QPoint &);
    void insertColumn();
    void removeColumn();
    void onSectionDoubleClicked(int);

private:
    PhysEqSolverTable *m_pTable;
    QAction *m_pActionInsertColumn;
    QAction *m_pActionRemoveColumn;
    int m_hdrIdx;
};

#endif // PHYSEQSOLVERTABLEHEADER_H
