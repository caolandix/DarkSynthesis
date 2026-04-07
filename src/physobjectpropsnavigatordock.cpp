#include "physobjectpropsnavigatordock.h"
#include "ui_physobjectpropsnavigatordock.h"

PhysObjectPropsNavigatorDock::PhysObjectPropsNavigatorDock(QWidget *parent) : QDockWidget(parent), ui(new Ui::PhysObjectPropsNavigatorDock) {
    ui ->setupUi(this);
}

PhysObjectPropsNavigatorDock::~PhysObjectPropsNavigatorDock() {
    delete ui;
}
