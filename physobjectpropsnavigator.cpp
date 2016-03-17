#include <QtWidgets>

#include "physbaseitem.h"
#include "cartesiangraph.h"
#include "physparticle.h"
#include "physvector.h"
#include "physobjectpropsnavigator.h"
#include "physobjectpropdelegate.h"
#include "physobjectpropeditor.h"
#include "graphwidget.h"

PhysObjectPropsNavigator::PhysObjectPropsNavigator(QWidget *pParent, int numRows, int numCols) : QTableWidget(pParent) {
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
    m_pParticleMass = NULL;
    m_pGraphicsItem = NULL;
    m_pLockXAxis = NULL;
    m_pLockYAxis = NULL;
    m_pPosition = NULL;

    setShowGrid(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    verticalHeader() -> setVisible(false);
    createTable(numRows, numCols);
}

void PhysObjectPropsNavigator::createTable(const int numRows, const int numCols) {
    QStringList tableHeader;

    tableHeader << "Property" << "Value";
    setColumnCount(2);
    setHorizontalHeaderLabels(tableHeader);
    setItemPrototype(item(numRows - 1, numCols - 1));
}

void PhysObjectPropsNavigator::onChangeObj(QGraphicsItem *pObj, QGraphicsItem *pPrevious) {
    qDebug("PhysObjectPropsNavigator::onChangeObj()");
    if (pObj != pPrevious) {
        m_pGraphicsItem = pObj;
        if (pObj) {
            disconnect(this, SIGNAL(cellChanged(int, int)), this, SLOT(onUpdateControl()));
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
            connect(this, SIGNAL(cellChanged(int, int)), this, SLOT(onUpdateControl()));
        }
    }
}

void PhysObjectPropsNavigator::onUpdateObj(QGraphicsItem *pObj) {
    //qDebug("PhysObjectPropsNavigator::onUpdateObj()");
    if (pObj != m_pGraphicsItem) {
        m_pGraphicsItem = pObj;
        onUpdateControl();
    }
}

void PhysObjectPropsNavigator::updateVectorTable(PhysVector *pObj) {
    //qDebug("PhysObjectPropsNavigator::updateVectorTable()");
    if (pObj) {
        QString str;
        if (m_pVectorMag) {
            str = m_pVectorMag ->text();
            pObj ->Magnitude(str.toDouble());
        }
        if (m_pVectorThetaAngle) {
            str = m_pVectorThetaAngle ->text();
            pObj ->ThetaAngle(str.toDouble());
        }
        if (m_pVectorThetaAxisOrient) {
            pObj ->ThetaAxisOrient((PhysVector::AxisOrientation)(m_pVectorThetaAxisOrient ->currentIndex()));
        }
        if (m_pVectorAssocParticle) {
            ;
        }

        // NOTE: Name is put last because it uses updated values from other vars
        if (m_pVectorName) {

            // Cases ..
            // 1. m_pVectorName is empty. In which case we assign the value in pObj to m_pVectorName
            // 2. m_pVectorName is not empty in which it is assigned to pObj
            str = m_pVectorName ->text();
            if (str.length() > 0)
                pObj ->Name(str);
            else {
                str = pObj ->Name();
                m_pVectorName ->setText(str);
            }
        }
    }
}

void PhysObjectPropsNavigator::updateParticleTable(PhysParticle *pObj) {
    //qDebug("PhysObjectPropsNavigator::updateParticleTable()");
    if (pObj) {
        pObj ->mass(m_pParticleMass ->text().toDouble());

        // Alert the PhysEqTable that a change in name has occurred in particles.
        emit updateParticleName(pObj ->Name(), m_pParticleName ->text());
        pObj ->Name(m_pParticleName ->text());

        // Extract the values from the string
        QString str = m_pPosition ->text();

        str = str.right(str.length() - 1);
        str = str.left(str.length() - 1);
        QStringList strList(str.split(","));

        QPointF newPos(strList.at(0).toDouble(), strList.at(1).toDouble());
        pObj ->Position(newPos);

        // Locking of the axis'
        pObj ->LockXAxis(m_pLockXAxis ->currentIndex() == 0 ? true : false);
        pObj ->LockYAxis(m_pLockYAxis ->currentIndex() == 0 ? true : false);
    }
}
void PhysObjectPropsNavigator::updateCartesianGraphTable(CartesianGraph *pObj) {
    //qDebug("PhysObjectPropsNavigator::updateCartesianGraphTable()");
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
    //qDebug("PhysObjectPropsNavigator::onUpdateControl()");
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
    emit repaint();
}

void PhysObjectPropsNavigator::buildCartesianGraphTable(CartesianGraph *pObj, QGraphicsItem *pPrev) {
    //qDebug("PhysObjectPropsNavigator::buildCartesianGraphTable()");
    if (pObj) {
        if (pPrev)
            destroyPrevTable(pPrev);
        map<int, QString> properties = pObj ->EditableProps();

        // Column 0
        for (unsigned int i = 0; i < properties.size(); i++) {
            insertRow(i);
            setItem(i, 0, createRowItem(properties[i]));
        }

        // Column 1 specialties
        setItem(0, 1, m_pXaxisLabel = new PhysObjectPropEditor());
        setItem(1, 1, m_pYaxisLabel = new PhysObjectPropEditor());
        setItem(2, 1, m_pAxisTickInc = new PhysObjectPropEditor());
        setItem(3, 1, m_pXaxisExtent = new PhysObjectPropEditor());
        setItem(4, 1, m_pYaxisExtent = new PhysObjectPropEditor());

        // set data
        m_pXaxisLabel ->setText(pObj -> XAxisLabel());
        m_pYaxisLabel ->setText(pObj -> YAxisLabel());
        m_pAxisTickInc ->setText(QString::number(pObj ->tickStep()));
        m_pXaxisExtent ->setText(QString::number(pObj -> xMax()));
        m_pYaxisExtent ->setText(QString::number(pObj -> yMax()));
    }
}

void PhysObjectPropsNavigator::buildVectorTable(PhysVector *pObj, QGraphicsItem *pPrev) {
    //qDebug("PhysObjectPropsNavigator::buildVectorTable()");

    if (pObj) {
        if (pPrev)
            destroyPrevTable(pPrev);
        map<int, QString> properties = pObj ->EditableProps();

        // Column 0
        for (unsigned int i = 0; i < properties.size(); i++) {
            insertRow(i);
            setItem(i, 0, createRowItem(properties[i]));
        }

        // Column 1
        setItem(0, 1, m_pVectorName = new PhysObjectPropEditor(pObj ->Name()));
        setItem(1, 1, m_pVectorMag = new PhysObjectPropEditor(QString::number(pObj ->Magnitude())));
        setItem(2, 1, m_pVectorThetaAngle = new PhysObjectPropEditor(QString::number(pObj ->theta().degrees)));
        setCellWidget(3, 1, m_pVectorThetaAxisOrient = new QComboBox(this));
        setItem(4, 1, m_pVectorAssocParticle = new PhysObjectPropEditor());

        // Populate the combobox control with possible values...
        QStringList items;
        items << pObj -> OrientationLabelMap().at(PhysVector::AXIS_HORIZ) << pObj ->OrientationLabelMap().at(PhysVector::AXIS_VERT);
        m_pVectorThetaAxisOrient -> addItems(items);

        // ... now set the value to what the vector object is assigned to.
        m_pVectorThetaAxisOrient ->setCurrentIndex(pObj ->theta().axisOrientation);

        if (pObj ->EndParticle())
            m_pVectorAssocParticle ->setText(QString(pObj -> EndParticle() -> Name()));
        else
            m_pVectorAssocParticle ->setText(QString("None"));
    }
}

void PhysObjectPropsNavigator::buildParticleTable(PhysParticle *pObj, QGraphicsItem *pPrev) {
    //qDebug("PhysObjectPropsNavigator::buildParticleTable()");

    if (pObj) {
        if (pPrev)
            destroyPrevTable(pPrev);
        map<int, QString> properties = pObj -> EditableProps();

        // Column 0
        for (unsigned int i = 0; i < properties.size(); i++) {
            insertRow(i);
            setItem(i, 0, createRowItem(properties[i]));
        }

        // column 1
        setItem(0, 1, m_pParticleName = new PhysObjectPropEditor());
        setItem(1, 1, m_pParticleMass = new PhysObjectPropEditor());
        setItem(2, 1, m_pPosition = new PhysObjectPropEditor());
        setCellWidget(3, 1, m_pLockXAxis = new QComboBox());
        setCellWidget(4, 1, m_pLockYAxis = new QComboBox());

        // Name
        m_pParticleName -> setText(pObj ->Name());

        // Mass
        m_pParticleMass -> setText(QString("%1").arg(pObj -> mass(), 0, 'f', 6));

        // Position
        QString position = QString("(%1, %2)").arg(pObj ->pos().x(), 0, 'f', 6).arg(pObj ->pos().y(), 0, 'f', 6);
        m_pPosition ->setText(position);

        // Lock the Axis'
        QStringList values;
        values << "false" << "true";
        m_pLockXAxis ->addItems(values);
        m_pLockYAxis ->addItems(values);

        if (pObj ->isXAxisLocked())
            m_pLockXAxis ->setCurrentIndex(1);
        else
            m_pLockXAxis ->setCurrentIndex(0);
        if (pObj ->isYAxisLocked())
            m_pLockYAxis ->setCurrentIndex(1);
        else
            m_pLockYAxis ->setCurrentIndex(0);

    }
}

void PhysObjectPropsNavigator::destroyPrevTable(QGraphicsItem *pObj) {
    //qDebug("PhysObjectPropsNavigator::destroyPrevTable()");
    if (!pObj) {
        //qDebug("PhysObjectPropsNavigator::destroyPrevTable() -- The pObj is NULL");
        return;
    }

    // If there are rows in the table, clear them out
    if (rowCount()) {
        while (rowCount())
            removeRow(0);
    }
}

QTableWidgetItem *PhysObjectPropsNavigator::createRowItem(const QString &strLabel) {
    QTableWidgetItem *pItem = new QTableWidgetItem(strLabel);
    pItem ->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    return pItem;
}
