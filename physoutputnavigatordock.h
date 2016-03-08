#ifndef PHYSOUTPUTNAVIGATORDOCK_H
#define PHYSOUTPUTNAVIGATORDOCK_H

#include <QDockWidget>

namespace Ui {
class PhysOutputNavigatorDock;
}

class PhysOutputNavigatorDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit PhysOutputNavigatorDock(QWidget *parent = 0);
    ~PhysOutputNavigatorDock();

private:
    Ui::PhysOutputNavigatorDock *ui;
};

#endif // PHYSOUTPUTNAVIGATORDOCK_H
