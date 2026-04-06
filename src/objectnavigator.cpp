#include "objectnavigator.h"
#include "ui_objectnavigator.h"

ObjectNavigator::ObjectNavigator(QWidget *parent) : QDockWidget(parent), ui(new Ui::ObjectNavigator) {
    ui ->setupUi(this);
}

ObjectNavigator::~ObjectNavigator() {
    delete ui;
}
