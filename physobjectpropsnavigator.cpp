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

    setShowGrid(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    verticalHeader() -> setVisible(false);

    createTable(numRows, numCols);
    createConnections();
}

void PhysObjectPropsNavigator::createTable(const int numRows, const int numCols) {
    QStringList tableHeader;

    tableHeader << "Property" << "Value";
    m_pTable = new QTableWidget(numRows, numCols, this);
    m_pTable -> setColumnCount(2);
    m_pTable -> setHorizontalHeaderLabels(tableHeader);
    m_pTable -> setItemPrototype(m_pTable -> item(numRows - 1, numCols - 1));
}


void PhysObjectPropsNavigator::createConnections() {
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
        if (m_pVectorName) {

            // Cases ..
            // 1. m_pVectorName is empty. In which case we assign the value in pObj to m_pVectorName
            // 2. m_pVectorName is not empty in which it is assigned to pObj
            if (m_pVectorName ->text().length() > 0)
                pObj ->Name(m_pVectorName ->text());
            else
                m_pVectorName ->setText(pObj ->Name());
        }
        if (m_pVectorMag)
            pObj ->Magnitude(m_pVectorName ->text().toDouble());
        if (m_pVectorThetaAngle)
            pObj ->ThetaAngle(m_pVectorName ->text().toDouble());
        if (m_pVectorThetaAxisOrient)
            pObj ->ThetaAxisOrient((PhysVector::AxisOrientation)(m_pVectorName ->text().toInt()));
        if (m_pVectorAssocParticle)
            ;
    }
}

void PhysObjectPropsNavigator::updateParticleTable(PhysParticle *pObj) {
    if (pObj) {

    }
}
void PhysObjectPropsNavigator::updateCartesianGraphTable(CartesianGraph *pObj) {
    if (pObj) {
        if (m_pXaxisLabel) {
            QString str = m_pXaxisLabel ->text();
            pObj ->XAxisLabel(str);
        }
        if (m_pYaxisLabel)
            pObj ->YAxisLabel(m_pYaxisLabel ->text());
        if (m_pAxisTickInc)
            pObj ->tickStep(m_pAxisTickInc ->text());
        if (m_pXaxisExtent)
            pObj ->XExtent(m_pXaxisExtent ->text());
        if (m_pYaxisExtent)
            pObj ->YExtent(m_pYaxisExtent ->text());
        if (m_pCartesianGraphName)
            pObj ->Name(m_pCartesianGraphName ->text());
        pObj ->graphWidget() -> update();
    }
}

void PhysObjectPropsNavigator::onUpdateControl() {
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
        default:
            qDebug("PhysObjectPropsNavigator::onChangeObj(): not a valid Object type");
            return;
        }
    }
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
        m_pXaxisExtent ->setText(QString::number(pObj -> xMax()));
        m_pYaxisExtent ->setText(QString::number(pObj -> yMax()));
        connect(m_pTable, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(onUpdateControl()));
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
        m_pTable ->setItem(0, 1, m_pVectorName = new PhysObjectPropEditor(pObj ->Name()));
        m_pTable ->setItem(1, 1, m_pVectorMag = new PhysObjectPropEditor(QString::number(pObj ->Magnitude())));
        m_pTable ->setItem(2, 1, m_pVectorThetaAngle = new PhysObjectPropEditor(QString::number(pObj ->theta().degrees)));
        m_pTable ->setCellWidget(3, 1, m_pVectorThetaAxisOrient = new QComboBox(this));
        m_pTable ->setItem(4, 1, m_pVectorAssocParticle = new PhysObjectPropEditor());

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
        map<int, QString> properties = pObj -> EditableProps();

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
                //delete m_pVectorMag;
                m_pVectorMag = NULL;
            }
            if (m_pVectorThetaAngle) {
                //delete m_pVectorThetaAngle;
                m_pVectorThetaAngle = NULL;
            }
            if (m_pVectorThetaAxisOrient) {
                //delete m_pVectorThetaAxisOrient;
                m_pVectorThetaAxisOrient = NULL;
            }
            if (m_pVectorAssocParticle) {
                //delete m_pVectorAssocParticle;
                m_pVectorAssocParticle = NULL;
            }
            break;
        case PhysBaseItem::ParticleType:
            if (m_pParticleName) {
                //delete m_pParticleName;
                m_pParticleName = NULL;
            }
            m_pParticleMass = NULL;
            break;
        case PhysBaseItem::CartesianGraphType:
            if (m_pCartesianGraphName) {
                m_pCartesianGraphName = NULL;
            }
            if (m_pYaxisLabel) {
                m_pYaxisLabel = NULL;
            }
            if (m_pXaxisLabel) {
                m_pXaxisLabel = NULL;
            }
            if (m_pAxisTickInc) {
                //delete m_pAxisTickInc;
                m_pAxisTickInc = NULL;
            }
            if (m_pXaxisExtent) {
                //delete m_pXaxisExtent;
                m_pXaxisExtent = NULL;
            }
            if (m_pYaxisExtent) {
                //delete m_pYaxisExtent;
                m_pYaxisExtent = NULL;
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
