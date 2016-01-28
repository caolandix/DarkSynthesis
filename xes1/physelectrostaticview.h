#ifndef PHYSELECTROSTATICWIDGET_H
#define PHYSELECTROSTATICWIDGET_H

#include <QtWidgets>
#include "physelectrostatic.h"

class PhysElectroStaticView : public QGraphicsView {
public:
    PhysElectroStaticView(QWidget * = NULL);

private:
    PhysElectroStatic m_Esx;
};

#endif // PHYSELECTROSTATICWIDGET_H
