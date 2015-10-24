#include <QWidget>
#include <QTabWidget>

#include "physoutputnavigator.h"

PhysOutputNavigator::PhysOutputNavigator(QWidget *pParent) : QTabWidget(pParent) {
}

void PhysOutputNavigator::onCreateObj(QGraphicsItem *) {
    qDebug("PhysOutputNavigator::onCreateObj signal");
}

