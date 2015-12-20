#ifndef PHYSEQSOLVERTABLEHEADER_H
#define PHYSEQSOLVERTABLEHEADER_H


#include <QtWidgets>
#include "physeqsolvertable.h"
class PhysEqSolverTable;

class PhysEqSolverTableHeader : public QHeaderView {
    Q_OBJECT
public:
    PhysEqSolverTableHeader(QList<int>, QWidget *);

    void timeSliceList(const QList<int> lstTimeSlices) { m_lstTimeSlices = lstTimeSlices; }
    QList<int> timeSliceList() const { return m_lstTimeSlices; }
signals:
    void updateTimeSlices(const int, const int);
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
    QList<int> m_lstTimeSlices;
};

#endif // PHYSEQSOLVERTABLEHEADER_H
