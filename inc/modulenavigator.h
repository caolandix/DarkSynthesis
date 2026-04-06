#ifndef MODULENAVIGATOR_H
#define MODULENAVIGATOR_H

#include <QDockWidget>

namespace Ui {
    class ModuleNavigator;
}

class ModuleNavigator : public QDockWidget {
    Q_OBJECT
public:
    explicit ModuleNavigator(QWidget *parent = nullptr);
    ~ModuleNavigator();

private:
    Ui::ModuleNavigator *ui = nullptr;
};

#endif // MODULENAVIGATOR_H
