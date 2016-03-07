#ifndef OBJECTNAVIGATOR_H
#define OBJECTNAVIGATOR_H

#include <QDockWidget>

namespace Ui {
class ObjectNavigator;
}

class ObjectNavigator : public QDockWidget
{
    Q_OBJECT

public:
    explicit ObjectNavigator(QWidget *parent = 0);
    ~ObjectNavigator();

private:
    Ui::ObjectNavigator *ui;
};

#endif // OBJECTNAVIGATOR_H
