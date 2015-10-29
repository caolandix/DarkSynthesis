#include <QTableWidget>
#include <QGraphicsItem>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QSpinBox>

#include "physobjectpropsnavigator.h"
#include "physbaseitem.h"

PhysObjectPropsNavigator::PhysObjectPropsNavigator(QWidget *pParent) : QTableWidget(pParent) {
    setShowGrid(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setColumnCount(2);
    QStringList tableHeader;

    tableHeader << "Property" << "Value";
    setHorizontalHeaderLabels(tableHeader);
    verticalHeader()->setVisible(false);

    m_pXaxisTickInc = NULL;
    m_pXaxisExtent = NULL;
    m_pYaxisExtent = NULL;
}

void PhysObjectPropsNavigator::onChangeObj(QGraphicsItem *pObj) {
    qDebug("PhysObjectPropsNavigator::onChangeObj()");

    switch (pObj -> type()) {
    case PhysBaseItem::VectorType:
        buildVectorTable(pObj);
        break;
    case PhysBaseItem::ParticleType:
        buildParticleTable(pObj);
        break;
    case PhysBaseItem::CartesianGraphType:
        buildCartesianGraphTable(pObj);
        break;
    default:
        qDebug("PhysObjectPropsNavigator::onChangeObj(): not a valid Object type");
        break;
    }
}

void PhysObjectPropsNavigator::buildCartesianGraphTable(QGraphicsItem *pObj) {
    qDebug("PhysObjectPropsNavigator::buildCartesianGraphTable()");


    // If there are rows in the table, clear them out and rebuild
    if (rowCount()) {
        for (int i = 0; i < rowCount(); i++)
            removeRow(i);
        delete m_pXaxisTickInc; m_pXaxisTickInc = NULL;
        delete m_pXaxisExtent; m_pXaxisExtent = NULL;
        delete m_pYaxisExtent; m_pYaxisExtent = NULL;
    }

    // X/Y axis labels (edit controls)
    // Axis tick increment (SpinboxDelegate)
    // Axis extents (SpinboxDelegates)

    // Column 0 - Property Names
    QTableWidgetItem *pItem = new QTableWidgetItem("X-Axis Label");
    insertRow(0);
    setItem(0, 0, pItem);

    pItem = new QTableWidgetItem("Y-Axis Label");
    insertRow(1);
    setItem(1, 0, pItem);

    pItem = new QTableWidgetItem("Axis Tick Increment");
    insertRow(2);
    setItem(2, 0, pItem);

    pItem = new QTableWidgetItem("X-Axis Extent");
    insertRow(3);
    setItem(3, 0, pItem);

    pItem = new QTableWidgetItem("Y-Axis Extent");
    insertRow(4);
    setItem(4, 0, pItem);

    setCellWidget(2, 1, m_pXaxisTickInc = new QSpinBox(this));
    setCellWidget(3, 1, m_pXaxisExtent = new QSpinBox(this));
    setCellWidget(4, 1, m_pYaxisExtent = new QSpinBox(this));
}

void PhysObjectPropsNavigator::buildVectorTable(QGraphicsItem *pObj) {
    qDebug("PhysObjectPropsNavigator::buildVectorTable()");

    // If there are rows in the table, clear them out and rebuild
    if (rowCount()) {
        for (int i = 0; i < rowCount(); i++)
            removeRow(i);
    }
}

void PhysObjectPropsNavigator::buildParticleTable(QGraphicsItem *pObj) {
    qDebug("PhysObjectPropsNavigator::buildParticleTable()");

    // If there are rows in the table, clear them out and rebuild
    if (rowCount()) {
        for (int i = 0; i < rowCount(); i++)
            removeRow(i);
    }
}


