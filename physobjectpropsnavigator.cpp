#include <QtWidgets>

#include "physbaseitem.h"
#include "cartesiangraph.h"
#include "physparticle.h"
#include "physvector.h"
#include "physobjectpropsnavigator.h"
#include "physctrldoublespinboxdelegate.h"
#include "physctrldoublespinbox.h"
#include "physobjectpropdelegate.h"
#include "physobjectpropeditor.h"
#include "graphwidget.h"

PhysObjectPropsNavigator::PhysObjectPropsNavigator(QWidget *pParent, int numRows, int numCols) : QTableView(pParent) {
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

    m_pGraphicsItem = NULL;

    m_pTable = new QTableWidget(numRows, numCols, this);

    setShowGrid(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    m_pTable ->setColumnCount(2);
    verticalHeader() -> setVisible(false);

    QStringList tableHeader;
    tableHeader << "Property" << "Value";
    m_pTable ->setHorizontalHeaderLabels(tableHeader);
    m_pTable -> setItemPrototype(m_pTable -> item(numRows - 1, numCols - 1));
    createConnections();
}


void PhysObjectPropsNavigator::createConnections() {

    // Create connections between controls and the View so that modifications will update PhysObject the view is assocviated with

    /*
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
    m_pGraphicsItem = pObj;
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
        if (m_pXaxisLabel) {

            qDebug("m_pXaxisLabel ->text(): '%s'", m_pXaxisLabel ->text().toStdString().c_str());
            pObj ->XAxisLabel(m_pXaxisLabel ->text());
            qDebug("New String is: '%s'", pObj ->XAxisLabel().toStdString().c_str());

        }
        if (m_pYaxisLabel) {
            pObj ->YAxisLabel(m_pYaxisLabel ->text());
        }
        if (m_pAxisTickInc) {
            pObj ->tickStep(m_pAxisTickInc ->text());
        }
        if (m_pXaxisExtent) {
            pObj ->XExtent(m_pXaxisExtent ->text());
        }
        if (m_pYaxisExtent) {
            pObj ->YExtent(m_pYaxisExtent ->text());
        }
        if (m_pCartesianGraphName) {
            pObj ->Name(m_pCartesianGraphName ->text());
        }
        pObj ->graphWidget() -> update();
    }
}

void PhysObjectPropsNavigator::onUpdateControl(int row, int col) {
    qDebug("PhysObjectPropsNavigator::onUpdateControl(), Row: %d, Col: %d", row, col);

    if (m_pGraphicsItem) {
        switch (m_pGraphicsItem ->type()) {
        case PhysBaseItem::CartesianGraphType:
            updateCartesianGraphTable(static_cast<CartesianGraph *>(m_pGraphicsItem));
            break;
        case PhysBaseItem::VectorType:
            updateVectorTable(static_cast<PhysVector *>(m_pGraphicsItem));
            break;
        case PhysBaseItem::ParticleType:
            updateParticleTable(static_cast<PhysParticle *>(m_pGraphicsItem));
            break;
        }
    }
    else {
        qDebug("PhysObjectPropsNavigator::onUpdateControl1(): pObj is NULL");
    }
}

void PhysObjectPropsNavigator::onUpdateControl(double val) {
    qDebug("PhysObjectPropsNavigator::onUpdateControl2()");
    // PhysObjectPropEditor *pEditor = static_cast<PhysObjectPropEditor *>(m_pTable ->item(row, col));
    QGraphicsItem *pObj = m_pGraphicsItem;

    if (pObj) {
        switch (pObj ->type()) {
        case PhysBaseItem::CartesianGraphType:
            updateCartesianGraphTable(static_cast<CartesianGraph *>(pObj));
            break;
        case PhysBaseItem::VectorType:
            updateVectorTable(static_cast<PhysVector *>(pObj));
            break;
        case PhysBaseItem::ParticleType:
            updateParticleTable(static_cast<PhysParticle *>(pObj));
            break;
        }
    }
    else {
        qDebug("PhysObjectPropsNavigator::onUpdateControl2(): pObj is NULL");
    }
}

void PhysObjectPropsNavigator::onUpdateControl() {
    qDebug("PhysObjectPropsNavigator::onUpdateControl3()");
}


void PhysObjectPropsNavigator::buildCartesianGraphTable(CartesianGraph *pObj, QGraphicsItem *pPrev) {
    qDebug("PhysObjectPropsNavigator::buildCartesianGraphTable()");

    if (pObj) {
        if (pPrev)
            destroyPrevTable(pPrev);
        map<int, QString> properties = pObj ->EditableProps();

        // Column 0
        for (int i = 0; i < properties.size(); i++) {
            m_pTable ->insertRow(i);
            m_pTable ->setItem(i, 0, createRowItem(properties[i]));
        }

        // Column 1 specialties
        m_pTable ->setItem(0, 1, m_pXaxisLabel = new PhysObjectPropEditor());
        m_pTable ->setItem(1, 1, m_pYaxisLabel = new PhysObjectPropEditor());
        m_pTable ->setItem(2, 1, m_pAxisTickInc = new PhysObjectPropEditor());
        m_pTable ->setItem(3, 1, m_pXaxisExtent = new PhysObjectPropEditor());
        m_pTable ->setItem(4, 1, m_pYaxisExtent = new PhysObjectPropEditor());

        // set data
        m_pXaxisLabel ->setText(pObj -> XAxisLabel());
        m_pYaxisLabel ->setText(pObj -> YAxisLabel());
        m_pAxisTickInc ->setText(QString::number(pObj ->tickStep()));

        // m_pXaxisExtent ->setRange(-pObj ->xMax(), pObj ->xMax());
        m_pXaxisExtent ->setText(QString::number(pObj ->xMax()));
        m_pYaxisExtent ->setText(QString::number(pObj ->yMax()));
        connect(m_pTable, SIGNAL(cellChanged(int, int)), this, SLOT(onUpdateControl(int, int)));
        //connect(m_pAxisTickInc, SIGNAL(valueChanged(double)), this, SLOT(onUpdateControl(double)));
        //connect(m_pAxisTickInc, SIGNAL(editingFinished()), this, SLOT(onUpdateControl()));
    }
}

void PhysObjectPropsNavigator::buildVectorTable(PhysVector *pObj, QGraphicsItem *pPrev) {
    qDebug("PhysObjectPropsNavigator::buildVectorTable()");

    if (pObj) {
        if (pPrev)
            destroyPrevTable(pPrev);
        map<int, QString> properties = pObj ->EditableProps();

        // Column 0
        for (int i = 0; i < properties.size(); i++) {
            m_pTable ->insertRow(i);
            m_pTable ->setItem(i, 0, createRowItem(properties[i]));
        }

        // Column 1
        m_pTable ->setItem(0, 1, m_pVectorName = new PhysObjectPropEditor());
        m_pTable ->setItem(1, 1, m_pVectorMag = new PhysObjectPropEditor());
        m_pTable ->setItem(2, 1, m_pVectorThetaAngle = new PhysObjectPropEditor());
        m_pTable ->setCellWidget(3, 1, m_pVectorThetaAxisOrient = new QComboBox(this));
        m_pTable ->setItem(4, 1, m_pVectorAssocParticle = new PhysObjectPropEditor());

        // set data
        m_pVectorMag ->setText(QString::number(pObj ->Magnitude()));
        m_pVectorThetaAngle ->setText(QString::number(pObj ->theta().degrees));

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
        map<int, QString> properties = pObj ->EditableProps();

        // Column 0
        for (int i = 0; i < properties.size(); i++) {
            m_pTable ->insertRow(i);
            m_pTable ->setItem(i, 0, createRowItem(properties[i]));
        }

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
    pItem ->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    return pItem;
}
