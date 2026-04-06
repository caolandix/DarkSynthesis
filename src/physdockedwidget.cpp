#include <QtWidgets>
#include "physdockedwidget.h"

PhysDockedWidget::PhysDockedWidget(const QString &title, QWidget *parent, Qt::WindowFlags flags) :
    QDockWidget(title, parent, flags) {
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

PhysDockedWidget::PhysDockedWidget(QWidget *parent, Qt::WindowFlags flags) : QDockWidget(parent, flags) {
}

QSize PhysDockedWidget::sizeHint() const {
    return PhysDockedWidget::sizeHint();
}
