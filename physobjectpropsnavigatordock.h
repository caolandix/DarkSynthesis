#ifndef PHYSOBJECTPROPSNAVIGATORDOCK_H
#define PHYSOBJECTPROPSNAVIGATORDOCK_H

#include <QDockWidget>

namespace Ui {
class PhysObjectPropsNavigatorDock;
}

class PhysObjectPropsNavigatorDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit PhysObjectPropsNavigatorDock(QWidget *parent = 0);
    ~PhysObjectPropsNavigatorDock();

private:
    Ui::PhysObjectPropsNavigatorDock *ui;
};

#endif // PHYSOBJECTPROPSNAVIGATORDOCK_H
