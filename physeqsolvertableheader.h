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
private:

};

#endif // PHYSEQSOLVERTABLEHEADER_H
