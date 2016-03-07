#ifndef MODULENAVIGATOR_H
#define MODULENAVIGATOR_H

#include <QDockWidget>

namespace Ui {
    class ModuleNavigator;
}

class ModuleNavigator : public QDockWidget {
    Q_OBJECT
public:
    explicit ModuleNavigator(QWidget *parent = 0);
    ~ModuleNavigator();

private:
    Ui::ModuleNavigator *ui;
};

#endif // MODULENAVIGATOR_H
