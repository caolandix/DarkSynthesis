#include <QTableWidget>
#include <QGraphicsItem>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QLineEdit>

#include "physobjectpropsnavigator.h"
#include "physbaseitem.h"
#include "cartesiangraph.h"
#include "physparticle.h"
#include "physvector.h"

PhysObjectPropsNavigator::PhysObjectPropsNavigator(QWidget *pParent) : QTableWidget(pParent) {
    m_pXaxisTickInc = NULL;
    m_pXaxisExtent = NULL;
    m_pYaxisExtent = NULL;
    m_pVectorMag = NULL;
    m_pVectorThetaAngle = NULL;
    m_pVectorThetaAxisOrient = NULL;
    m_pVectorAssocParticle = NULL;

    setShowGrid(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setColumnCount(2);
    verticalHeader() -> setVisible(false);


    QStringList tableHeader;
    tableHeader << "Property" << "Value";
    setHorizontalHeaderLabels(tableHeader);
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

void PhysObjectPropsNavigator::buildCartesianGraphTable(CartesianGraph *pObj) {
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

    // Column 1 specialties
    setCellWidget(2, 1, m_pXaxisTickInc = new QDoubleSpinBox(this));
    setCellWidget(3, 1, m_pXaxisExtent = new QDoubleSpinBox(this));
    setCellWidget(4, 1, m_pYaxisExtent = new QDoubleSpinBox(this));
}

void PhysObjectPropsNavigator::buildVectorTable(PhysVector *pObj) {
    qDebug("PhysObjectPropsNavigator::buildVectorTable()");

    // If there are rows in the table, clear them out and rebuild
    if (rowCount()) {
        for (int i = 0; i < rowCount(); i++)
            removeRow(i);
        delete m_pVectorMag; m_pVectorMag = NULL;
        delete m_pVectorThetaAngle; m_pVectorThetaAngle = NULL;
        delete m_pVectorThetaAxisOrient; m_pVectorThetaAxisOrient = NULL;
        delete m_pVectorAssocParticle; m_pVectorAssocParticle = NULL;

    }

    // Column 0
    QTableWidgetItem *pItem = new QTableWidgetItem("Magnitude");
    insertRow(0);
    setItem(0, 0, pItem);
    pItem = new QTableWidgetItem("Theta - Angle");
    insertRow(1);
    setItem(1, 0, pItem);
    pItem = new QTableWidgetItem("Theta - Axis Orientation");
    insertRow(2);
    setItem(2, 0, pItem);
    pItem = new QTableWidgetItem("Associated Particle");
    insertRow(2);
    setItem(2, 0, pItem);

    // Column 1
    setCellWidget(0, 1, m_pVectorMag = new QDoubleSpinBox(this));
    setCellWidget(1, 1, m_pVectorMag = new QDoubleSpinBox(this));
    setCellWidget(2, 1, m_pVectorThetaAngle = new QDoubleSpinBox(this));
    setCellWidget(3, 1, m_pVectorAssocParticle = new QLineEdit(this));
}

void PhysObjectPropsNavigator::buildParticleTable(PhysParticle *pObj) {
    qDebug("PhysObjectPropsNavigator::buildParticleTable()");

    // If there are rows in the table, clear them out and rebuild
    if (rowCount()) {
        for (int i = 0; i < rowCount(); i++)
            removeRow(i);
    }
}


