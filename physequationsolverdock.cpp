#include "physequationsolverdock.h"
#include "ui_physequationsolverdock.h"

PhysEquationSolverDock::PhysEquationSolverDock(QWidget *parent) : QDockWidget(parent), ui(new Ui::PhysEquationSolverDock) {
    ui ->setupUi(this);
}

PhysEquationSolverDock::~PhysEquationSolverDock() {
    delete ui;
}
