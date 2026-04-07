#include "physoutputnavigatordock.h"
#include "ui_physoutputnavigatordock.h"

PhysOutputNavigatorDock::PhysOutputNavigatorDock(QWidget *parent) : QDockWidget(parent),
    ui(new Ui::PhysOutputNavigatorDock) {
    ui->setupUi(this);
}

PhysOutputNavigatorDock::~PhysOutputNavigatorDock() {
    delete ui;
}
