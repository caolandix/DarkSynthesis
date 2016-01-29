#ifndef PHYSELECTROSTATICWIDGET_H
#define PHYSELECTROSTATICWIDGET_H

#include <QtWidgets>

#include "physelectrostatic.h"
#include "../qcustomplot-1.3.2/qcustomplot.h"

namespace Ui {
    class xesWindow;
}

class PhysElectroStaticView : public QGraphicsView {
    Q_OBJECT
public:
    explicit PhysElectroStaticView(QWidget * = NULL);

private slots:
  void titleDoubleClick(QMouseEvent *event, QCPPlotTitle *title);
  void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
  void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
  void selectionChanged();
  void mousePress();
  void mouseWheel();
  void addRandomGraph();
  void removeSelectedGraph();
  void removeAllGraphs();
  void contextMenuRequest(QPoint pos);
  void moveLegend();
  void graphClicked(QCPAbstractPlottable *plottable);

private:
    PhysElectroStatic m_Esx;
    Ui::xesWindow *m_pUI;
};

#endif // PHYSELECTROSTATICWIDGET_H
