#ifndef PHYSEQSOLVERTABLEHEADER_H
#define PHYSEQSOLVERTABLEHEADER_H


#include <QtWidgets>

class PhysEqSolverTableHeader : public QHeaderView {
    Q_OBJECT
public:
    PhysEqSolverTableHeader(QWidget *);

signals:

public slots:
    void onSectionClicked(int);
    //void ShowContextMenu(const QPoint &);
    //void insertColumn();
    //void removeColumn();

private:

    //QAction *m_pActionInsertColumn;
    // QAction *m_pActionRemoveColumn;
};

#endif // PHYSEQSOLVERTABLEHEADER_H
