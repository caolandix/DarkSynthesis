#include "modulenavigator.h"
#include "ui_modulenavigator.h"

ModuleNavigator::ModuleNavigator(QWidget *parent) : QDockWidget(parent), ui(new Ui::ModuleNavigator) {
    ui -> setupUi(this);

}

ModuleNavigator::~ModuleNavigator() {
    delete ui;
}
