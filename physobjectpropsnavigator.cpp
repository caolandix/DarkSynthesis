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
    m_pCartesianGraphName = NULL;
    m_pVectorName = NULL;
    m_pParticleName = NULL;

    setShowGrid(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setColumnCount(2);
    verticalHeader() -> setVisible(false);

    QStringList tableHeader;
    tableHeader << "Property" << "Value";
    setHorizontalHeaderLabels(tableHeader);
}

void PhysObjectPropsNavigator::onChangeObj(QGraphicsItem *pObj, QGraphicsItem *pPrevious) {
    qDebug("PhysObjectPropsNavigator::onChangeObj()");
    if (pObj) {
        switch (pObj -> type()) {
        case PhysBaseItem::VectorType:
            buildVectorTable(static_cast<PhysVector *>(pObj), pPrevious);
            break;
        case PhysBaseItem::ParticleType:
            buildParticleTable(static_cast<PhysParticle *>(pObj), pPrevious);
            break;
        case PhysBaseItem::CartesianGraphType:
            buildCartesianGraphTable(static_cast<CartesianGraph *>(pObj), pPrevious);
            break;
        default:
            qDebug("PhysObjectPropsNavigator::onChangeObj(): not a valid Object type");
            break;
        }
    }
}

void PhysObjectPropsNavigator::onUpdateObj(QGraphicsItem *pObj) {
    qDebug("PhysObjectPropsNavigator::onChangeObj()");
    if (pObj) {
        switch (pObj -> type()) {
        case PhysBaseItem::VectorType:
            updateVectorTable(static_cast<PhysVector *>(pObj));
            break;
        case PhysBaseItem::ParticleType:
            updateParticleTable(static_cast<PhysParticle *>(pObj));
            break;
        case PhysBaseItem::CartesianGraphType:
            updateCartesianGraphTable(static_cast<CartesianGraph *>(pObj));
            break;
        default:
            qDebug("PhysObjectPropsNavigator::onUpdateObj(): not a valid Object type");
            break;
        }
    }
}

void PhysObjectPropsNavigator::updateVectorTable(PhysVector *pObj) {
    if (pObj) {

    }

}
void PhysObjectPropsNavigator::updateParticleTable(PhysParticle *pObj) {
    if (pObj) {

    }

}
void PhysObjectPropsNavigator::updateCartesianGraphTable(CartesianGraph *pObj) {
    if (pObj) {

    }

}

void PhysObjectPropsNavigator::buildCartesianGraphTable(CartesianGraph *pObj, QGraphicsItem *pPrev) {
    qDebug("PhysObjectPropsNavigator::buildCartesianGraphTable()");

    if (pObj) {
        destroyPrevTable(pPrev);

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
        setCellWidget(4, 1, m_pYaxisExtent = new QDoubleSpinBox(this));\
    }
}

void PhysObjectPropsNavigator::buildVectorTable(PhysVector *pObj, QGraphicsItem *pPrev) {
    qDebug("PhysObjectPropsNavigator::buildVectorTable()");

    if (pObj) {
        destroyPrevTable(pPrev);

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
}

void PhysObjectPropsNavigator::buildParticleTable(PhysParticle *pObj, QGraphicsItem *pPrevious) {
    qDebug("PhysObjectPropsNavigator::buildParticleTable()");

    if (pObj) {
        destroyPrevTable(pPrevious);

        // Column 0
        QTableWidgetItem *pItem = new QTableWidgetItem("Name");
        insertRow(0);
        setItem(0, 0, pItem);
        pItem = new QTableWidgetItem("Mass");
        insertRow(1);
        setItem(1, 0, pItem);
    }
}

void PhysObjectPropsNavigator::destroyPrevTable(QGraphicsItem *pObj) {
    if (!pObj) {
        qDebug("PhysObjectPropsNavigator::destroyPrevTable() -- The pObj is NULL");
        return;
    }

    // If there are rows in the table, clear them out
    if (rowCount()) {
        for (int i = 0; i < rowCount(); i++)
            removeRow(i);
        switch (pObj -> type()) {
        case PhysBaseItem::VectorType:
            if (m_pVectorMag) {
                delete m_pVectorMag; m_pVectorMag = NULL;
            }
            if (m_pVectorThetaAngle) {
                delete m_pVectorThetaAngle; m_pVectorThetaAngle = NULL;
            }
            if (m_pVectorThetaAxisOrient) {
                delete m_pVectorThetaAxisOrient; m_pVectorThetaAxisOrient = NULL;
            }
            if (m_pVectorAssocParticle) {
                delete m_pVectorAssocParticle; m_pVectorAssocParticle = NULL;
            }
            break;
        case PhysBaseItem::ParticleType:
            break;
        case PhysBaseItem::CartesianGraphType:
            if (m_pXaxisTickInc) {
                delete m_pXaxisTickInc; m_pXaxisTickInc = NULL;
            }
            if (m_pXaxisExtent) {
                delete m_pXaxisExtent; m_pXaxisExtent = NULL;
            }
            if (m_pYaxisExtent) {
                delete m_pYaxisExtent; m_pYaxisExtent = NULL;
            }
            break;
        default:
            qDebug("PhysObjectPropsNavigator::destroyPrevTable(): not a valid Object type");
            break;
        }
    }
}
