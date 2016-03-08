#ifndef PHYSEQUATIONSOLVERDOCK_H
#define PHYSEQUATIONSOLVERDOCK_H

#include <QDockWidget>

namespace Ui {
class PhysEquationSolverDock;
}

class PhysEquationSolverDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit PhysEquationSolverDock(QWidget *parent = 0);
    ~PhysEquationSolverDock();

private:
    Ui::PhysEquationSolverDock *ui;
};

#endif // PHYSEQUATIONSOLVERDOCK_H
