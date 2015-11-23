#include <QTableWidget>
#include <QTableView>
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
#include "physctrldoublespinbox.h"
#include "physobjectpropdelegate.h"
#include "physobjectpropeditor.h"

PhysObjectPropsNavigator::PhysObjectPropsNavigator(QWidget *pParent) : QTableView(pParent) {
    m_pXaxisLabel = NULL;
    m_pYaxisLabel = NULL;
    m_pAxisTickInc = NULL;
    m_pXaxisExtent = NULL;
    m_pYaxisExtent = NULL;
    m_pVectorMag = NULL;
    m_pVectorThetaAngle = NULL;
    m_pVectorThetaAxisOrient = NULL;
    m_pVectorAssocParticle = NULL;
    m_pCartesianGraphName = NULL;
    m_pVectorName = NULL;
    m_pParticleName = NULL;


    int rows = 0, cols = 2;
    m_pTable = new QTableWidget(rows, cols, this);

    setShowGrid(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    m_pTable ->setColumnCount(2);
    verticalHeader() -> setVisible(false);

    QStringList tableHeader;
    tableHeader << "Property" << "Value";
    m_pTable ->setHorizontalHeaderLabels(tableHeader);
    m_pTable -> setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    m_pTable -> setItemPrototype(m_pTable -> item(rows - 1, cols - 1));
    m_pTable -> setItemDelegate(new PhysObjectPropDelegate());
    createConnections();
}

void PhysObjectPropsNavigator::createConnections() {

    // Create connections between controls and the View so that modifications will update PhysObject the view is assocviated with
    /*
    connect(m_pXaxisLabel, SIGNAL(), this, SLOT(updateControl()));
    connect(m_pYaxisLabel, SIGNAL(), this, SLOT(updateControl()));
    connect(m_pAxisTickInc, SIGNAL(), this, SLOT(updateControl()));
    connect(m_pXaxisExtent, SIGNAL(), this, SLOT(updateControl()));
    connect(m_pYaxisExtent, SIGNAL(), this, SLOT(updateControl()));
    connect(m_pVectorMag, SIGNAL(), this, SLOT(updateControl()));
    connect(m_pVectorThetaAngle, SIGNAL(), this, SLOT(updateControl()));
    connect(m_pVectorThetaAxisOrient, SIGNAL(), this, SLOT(updateControl()));
    connect(m_pVectorAssocParticle, SIGNAL(), this, SLOT(updateControl()));
    connect(m_pCartesianGraphName, SIGNAL(), this, SLOT(updateControl()));
    connect(m_pVectorName, SIGNAL(), this, SLOT(updateControl()));
    connect(m_pParticleName, SIGNAL(), this, SLOT(updateControl()));
    */
}

void PhysObjectPropsNavigator::deleteControls() {
    if (m_pXaxisLabel) { delete m_pXaxisLabel; m_pXaxisLabel = NULL; };
    if (m_pYaxisLabel) { delete m_pYaxisLabel; m_pYaxisLabel = NULL; };
    if (m_pAxisTickInc) { delete m_pAxisTickInc; m_pAxisTickInc = NULL; };
    if (m_pXaxisExtent) { delete m_pXaxisExtent; m_pXaxisExtent = NULL; };
    if (m_pYaxisExtent) { delete m_pYaxisExtent; m_pYaxisExtent = NULL; };
    if (m_pVectorMag) { delete m_pVectorMag; m_pVectorMag = NULL; };
    if (m_pVectorThetaAngle) { delete m_pVectorThetaAngle; m_pVectorThetaAngle = NULL; };
    if (m_pVectorThetaAxisOrient) { delete m_pVectorThetaAxisOrient; m_pVectorThetaAxisOrient = NULL; };
    if (m_pVectorAssocParticle) { delete m_pVectorAssocParticle; m_pVectorAssocParticle = NULL; };
    if (m_pCartesianGraphName) { delete m_pCartesianGraphName; m_pCartesianGraphName = NULL; };
    if (m_pVectorName) { delete m_pVectorName; m_pVectorName = NULL; };
    if (m_pParticleName) { delete m_pParticleName; m_pParticleName = NULL; };
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
        if (pPrev)
            destroyPrevTable(pPrev);

        // X/Y axis labels (edit controls)
        // Axis tick increment (SpinboxDelegate)
        // Axis extents (SpinboxDelegates)

        // Column 0 - Property Names
        m_pTable ->insertRow(0);
        m_pTable ->setItem(0, 0, createRowItem(QString("X-Axis Label")));
        m_pTable ->insertRow(1);
        m_pTable ->setItem(1, 0, createRowItem(QString("Y-Axis Label")));
        m_pTable ->insertRow(2);
        m_pTable ->setItem(2, 0, createRowItem(QString("Axis Tick Increment")));
        m_pTable ->insertRow(3);
        m_pTable ->setItem(3, 0, createRowItem(QString("X-Axis Extent")));
        m_pTable ->insertRow(4);
        m_pTable ->setItem(4, 0, createRowItem(QString("Y-Axis Extent")));

        // Column 1 specialties
        m_pTable ->setItem(0, 1, m_pXaxisLabel = new PhysObjectPropEditor());
        m_pTable ->setItem(1, 1, m_pYaxisLabel = new PhysObjectPropEditor());
        m_pTable ->setCellWidget(2, 1, m_pAxisTickInc = new PhysCtrlDoubleSpinBox(6, this));
        m_pTable ->setCellWidget(3, 1, m_pXaxisExtent = new PhysCtrlDoubleSpinBox(6, this));
        m_pTable ->setCellWidget(4, 1, m_pYaxisExtent = new PhysCtrlDoubleSpinBox(6, this));

        // set data
        m_pXaxisLabel ->setText(pObj -> XAxisLabel());
        m_pYaxisLabel ->setText(pObj -> YAxisLabel());
        m_pAxisTickInc ->setValue(pObj ->tickStep());

        m_pXaxisExtent ->setRange(-pObj ->xMax(), pObj ->xMax());
        m_pXaxisExtent ->setValue(pObj ->xMax());
        m_pYaxisExtent ->setValue(pObj ->yMax());
    }
}

void PhysObjectPropsNavigator::buildVectorTable(PhysVector *pObj, QGraphicsItem *pPrev) {
    qDebug("PhysObjectPropsNavigator::buildVectorTable()");

    if (pObj) {
        if (pPrev)
            destroyPrevTable(pPrev);

        // Column 0, row 0
        m_pTable ->insertRow(0);
        m_pTable ->setItem(0, 0, createRowItem(QString("Magnitude")));
        // Column 0, row 1
        m_pTable ->insertRow(1);
        m_pTable ->setItem(1, 0, createRowItem(QString("Theta - Angle")));
        // Column 0, row 2
        m_pTable ->insertRow(2);
        m_pTable ->setItem(2, 0, createRowItem(QString("Theta - Axis Orientation")));
        // Column 0, row 3
        m_pTable ->insertRow(3);
        m_pTable ->setItem(3, 0, createRowItem(QString("Associated Particle")));

        // Column 1
        m_pTable ->setCellWidget(0, 1, m_pVectorMag = new PhysCtrlDoubleSpinBox(6, this));
        m_pTable ->setCellWidget(1, 1, m_pVectorThetaAngle = new PhysCtrlDoubleSpinBox(6, this));
        m_pTable ->setCellWidget(2, 1, m_pVectorThetaAxisOrient = new QComboBox(this));
        m_pTable ->setItem(3, 1, m_pVectorAssocParticle = new PhysObjectPropEditor());

        // set data
        m_pVectorMag ->setValue(pObj ->Magnitude());
        m_pVectorThetaAngle ->setValue(pObj ->theta().degrees);

        // Populate the combobox control with possible values...
        QStringList items;
        items << pObj -> OrientationLabelMap().at(PhysVector::AXIS_HORIZ) << pObj ->OrientationLabelMap().at(PhysVector::AXIS_VERT);
        m_pVectorThetaAxisOrient -> addItems(items);

        // ... now set the value to what the vector object is assigned to.
        m_pVectorThetaAxisOrient ->setCurrentIndex(pObj ->theta().axisOrientation);

        if (pObj ->StartParticle())
            m_pVectorAssocParticle ->setText(QString(pObj -> StartParticle() -> Name()));
        else
            m_pVectorAssocParticle ->setText(QString("None"));
    }
}

void PhysObjectPropsNavigator::buildParticleTable(PhysParticle *pObj, QGraphicsItem *pPrev) {
    qDebug("PhysObjectPropsNavigator::buildParticleTable()");

    if (pObj) {
        if (pPrev)
            destroyPrevTable(pPrev);
        QTableWidgetItem *pItem = NULL;
        // Column 0
        m_pTable ->insertRow(0);
        m_pTable ->setItem(0, 0, pItem = createRowItem(QString("Name")));
        m_pTable ->insertRow(1);
        m_pTable ->setItem(1, 0, pItem = createRowItem(QString("Mass")));

        // column 1
        m_pTable ->setItem(0, 1, m_pParticleName = new PhysObjectPropEditor());
        m_pTable ->setItem(1, 1, m_pParticleMass = new PhysObjectPropEditor());
        m_pParticleName -> setText(pObj ->Name());
        m_pParticleMass -> setText(QString("%1").arg(pObj -> mass(), 0, 'f', 6));
    }
}

void PhysObjectPropsNavigator::destroyPrevTable(QGraphicsItem *pObj) {
    if (!pObj) {
        qDebug("PhysObjectPropsNavigator::destroyPrevTable() -- The pObj is NULL");
        return;
    }

    // If there are rows in the table, clear them out
    if (m_pTable ->rowCount()) {
        while (m_pTable ->rowCount())
            m_pTable ->removeRow(0);
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
            if (m_pParticleName) { delete m_pParticleName; m_pParticleName = NULL; }
            break;
        case PhysBaseItem::CartesianGraphType:
            if (m_pAxisTickInc) {
                delete m_pAxisTickInc; m_pAxisTickInc = NULL;
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

QTableWidgetItem *PhysObjectPropsNavigator::createRowItem(const QString &strLabel) {
    QTableWidgetItem *pItem = new QTableWidgetItem(strLabel);
    pItem ->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
    return pItem;
}
