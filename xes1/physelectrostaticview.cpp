#include "../qcustomplot-1.3.2/qcustomplot.h"
#include "physelectrostaticview.h"
#include "ui_xes1.h"

PhysElectroStaticView::PhysElectroStaticView(QWidget *pParent) : QGraphicsView(pParent) {
/*
    m_pUI -> setupUi(this);

    srand(QDateTime::currentDateTime().toTime_t());
    m_pUI -> customPlot = new QCustomPlot(this);
    m_pUI -> customPlot -> setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    m_pUI -> customPlot -> xAxis->setRange(-8, 8);
    m_pUI -> customPlot -> yAxis->setRange(-5, 5);
    m_pUI -> customPlot -> axisRect()->setupFullAxesBox();
    m_pUI -> customPlot -> plotLayout()->insertRow(0);
    m_pUI -> customPlot -> plotLayout()->addElement(0, 0, new QCPPlotTitle(m_pUI -> customPlot, "Interaction Example"));
    m_pUI -> customPlot -> xAxis->setLabel("x Axis");
    m_pUI -> customPlot -> yAxis->setLabel("y Axis");
    m_pUI -> customPlot -> legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    m_pUI -> customPlot->legend->setFont(legendFont);
    m_pUI -> customPlot->legend->setSelectedFont(legendFont);
    m_pUI -> customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

    addRandomGraph();
    addRandomGraph();
    addRandomGraph();
    addRandomGraph();

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(m_pUI -> customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(m_pUI -> customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(m_pUI -> customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(m_pUI -> customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_pUI -> customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_pUI -> customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_pUI -> customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(m_pUI -> customPlot, SIGNAL(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)), this, SLOT(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)));
    connect(m_pUI -> customPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
    connect(m_pUI -> customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(m_pUI -> customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));

    // setup policy and connect slot for context menu popup:
    m_pUI -> customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_pUI -> customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
    */
}

void PhysElectroStaticView::titleDoubleClick(QMouseEvent* event, QCPPlotTitle* title) {
    Q_UNUSED(event)

    // Set the plot title by double clicking on it
    bool bOK;
    QString newTitle = QInputDialog::getText(this, "QCustomPlot example", "New plot title:", QLineEdit::Normal, title->text(), &bOK);
    if (bOK) {
        title->setText(newTitle);
        m_pUI -> customPlot->replot();
    }
}

void PhysElectroStaticView::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart selectablePart) {

    // Set an axis label by double clicking on it
    if (selectablePart == QCPAxis::spAxisLabel) {

        // only react when the actual axis label is clicked, not tick label or axis backbone
        bool ok;
        QString newLabel = QInputDialog::getText(this, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
        if (ok) {
            axis ->setLabel(newLabel);
            m_pUI -> customPlot->replot();
        }
    }
}

void PhysElectroStaticView::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item) {

    // Rename a graph by double clicking on its legend item
    Q_UNUSED(legend)

    // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
    if (item) {
        QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
        bool ok;
        QString newName = QInputDialog::getText(this, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
        if (ok) {
            plItem->plottable()->setName(newName);
            m_pUI -> customPlot->replot();
        }
    }
}

void PhysElectroStaticView::selectionChanged() {
    /*
    normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
    the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
    and the axis base line together. However, the axis label shall be selectable individually.

    The selection state of the left and right axes shall be synchronized as well as the state of the
    bottom and top axes.

    Further, we want to synchronize the selection of the graphs with the selection state of the respective
    legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
    or on its legend item.
    */

    // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (m_pUI -> customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || m_pUI -> customPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        m_pUI -> customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || m_pUI -> customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels)) {
        m_pUI -> customPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        m_pUI -> customPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (m_pUI -> customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || m_pUI -> customPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        m_pUI -> customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || m_pUI -> customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels)) {
        m_pUI -> customPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        m_pUI -> customPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // synchronize selection of graphs with selection of corresponding legend items:
    for (int i = 0; i < m_pUI -> customPlot ->graphCount(); ++i) {
        QCPGraph *graph = m_pUI -> customPlot ->graph(i);
        QCPPlottableLegendItem *item = m_pUI -> customPlot->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected()) {
            item->setSelected(true);
            graph->setSelected(true);
        }
    }
}

void PhysElectroStaticView::mousePress() {
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged

    if (m_pUI -> customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        m_pUI -> customPlot->axisRect()->setRangeDrag(m_pUI -> customPlot->xAxis->orientation());
    else if (m_pUI -> customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        m_pUI -> customPlot->axisRect()->setRangeDrag(m_pUI -> customPlot->yAxis->orientation());
    else
        m_pUI -> customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void PhysElectroStaticView::mouseWheel() {
    // if an axis is selected, only allow the direction of that axis to be zoomed
    // if no axis is selected, both directions may be zoomed

    if (m_pUI -> customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        m_pUI -> customPlot->axisRect()->setRangeZoom(m_pUI -> customPlot->xAxis->orientation());
    else if (m_pUI -> customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        m_pUI -> customPlot->axisRect()->setRangeZoom(m_pUI -> customPlot->yAxis->orientation());
    else
        m_pUI -> customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void PhysElectroStaticView::addRandomGraph() {

    // number of points in graph
    int n = 50;
    double xScale = (rand() / (double)RAND_MAX + 0.5) * 2;
    double yScale = (rand() / (double)RAND_MAX + 0.5) * 2;
    double xOffset = (rand() / (double)RAND_MAX - 0.5) * 4;
    double yOffset = (rand() / (double)RAND_MAX - 0.5) * 5;
    double r1 = (rand() / (double)RAND_MAX - 0.5) * 2;
    double r2 = (rand() / (double)RAND_MAX - 0.5) * 2;
    double r3 = (rand() / (double)RAND_MAX - 0.5) * 2;
    double r4 = (rand() / (double)RAND_MAX - 0.5) * 2;
    QVector<double> x(n), y(n);
    for (int i=0; i<n; i++) {
        x[i] = (i / (double)n - 0.5) * 10.0 * xScale + xOffset;
        y[i] = (qSin(x[i] * r1 * 5) * qSin(qCos(x[i] * r2) * r4 * 3) + r3 * qCos(qSin(x[i]) * r4 * 2)) * yScale + yOffset;
    }
    m_pUI -> customPlot->addGraph();
    m_pUI -> customPlot->graph()->setName(QString("New graph %1").arg(m_pUI -> customPlot->graphCount()-1));
    m_pUI -> customPlot->graph()->setData(x, y);
    m_pUI -> customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
    if (rand()%100 > 50)
        m_pUI -> customPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));
    QPen graphPen;
    graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
    graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
    m_pUI -> customPlot->graph()->setPen(graphPen);
    m_pUI -> customPlot->replot();
}

void PhysElectroStaticView::removeSelectedGraph() {
    if (m_pUI -> customPlot->selectedGraphs().size() > 0) {
        m_pUI -> customPlot->removeGraph(m_pUI -> customPlot->selectedGraphs().first());
        m_pUI -> customPlot->replot();
    }
}

void PhysElectroStaticView::removeAllGraphs() {
    m_pUI -> customPlot->clearGraphs();
    m_pUI -> customPlot->replot();
}

void PhysElectroStaticView::contextMenuRequest(QPoint pos) {
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    // context menu on legend requested
    if (m_pUI -> customPlot->legend->selectTest(pos, false) >= 0) {
        menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
        menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
        menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
        menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
        menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
    }

    // general context menu on graphs requested
    else {
        menu->addAction("Add random graph", this, SLOT(addRandomGraph()));
        if (m_pUI -> customPlot->selectedGraphs().size() > 0)
            menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph()));
        if (m_pUI -> customPlot->graphCount() > 0)
            menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));
    }
    menu->popup(m_pUI -> customPlot->mapToGlobal(pos));
}

void PhysElectroStaticView::moveLegend() {

    // make sure this slot is really called by a context menu action, so it carries the data we need
    if (QAction* contextAction = qobject_cast<QAction*>(sender())) {
        bool ok;
        int dataInt = contextAction->data().toInt(&ok);
        if (ok) {
            m_pUI -> customPlot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
            m_pUI -> customPlot->replot();
        }
    }
}

void PhysElectroStaticView::graphClicked(QCPAbstractPlottable *plottable) {
    // statusBar->showMessage(QString("Clicked on graph '%1'.").arg(plottable->name()), 1000);
}
