#ifndef PHYSEQSOLVERTABLE_H
#define PHYSEQSOLVERTABLE_H

#include <QtWidgets>

#include "physeqsolvertableheader.h"

class PhysEqSolverTableHeader;

class PhysEqSolverTable : public QTableWidget {
    Q_OBJECT
public:
    PhysEqSolverTable(const int, const int, QWidget *);

    ~PhysEqSolverTable();

    void insertColumn();
    void removeColumn(const int);
    void rebuildColumnHeaders();
    void createTableHeader();
    void updateColor(QTableWidgetItem *);
signals:
public slots:
    void onSelectColor();
    void onSelectFont();
    void onClear();
    void onCustomContextMenu(const QPoint &);
    void onSelectVelVector();
    void onSelectAccelVector();
    void onSelectGravVector();
    void onSelectDisplacementVector();
    void onSelectParticle();
private:
    PhysEqSolverTableHeader *m_pHeader;
    QAction *m_pActColor;
    QAction *m_pActFont;
    QAction *m_pActClear;
};

#endif // PHYSEQSOLVERTABLE_H
