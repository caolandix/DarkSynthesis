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
    void onSectionClicked(int);
    void onShowContextMenu(const QPoint &);
    void insertColumn();
    void removeColumn();

private:
    PhysEqSolverTable *m_pTable;
    QAction *m_pActionInsertColumn;
    QAction *m_pActionRemoveColumn;
};

#endif // PHYSEQSOLVERTABLEHEADER_H
