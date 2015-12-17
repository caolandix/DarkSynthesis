#include "physeqsolvertable.h"
#include "physeqsolvertableheader.h"
#include "physobjectpropdelegate.h"


PhysEqSolverTableHeader::PhysEqSolverTableHeader(QList<int> lstTimeSlices, QWidget *pParent) : QHeaderView(Qt::Horizontal, pParent) {
    m_pActionInsertColumn = NULL;
    m_pActionRemoveColumn = NULL;
    m_pTable = static_cast<PhysEqSolverTable *>(pParent);
    setSectionsClickable(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
    m_lstTimeSlices = lstTimeSlices;

    connect(this, SIGNAL(sectionDoubleClicked(int)), this, SLOT(onSectionDoubleClicked(int)));
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onShowContextMenu(const QPoint &)));
}

void PhysEqSolverTableHeader::onShowContextMenu(const QPoint &pos) {
    QMenu ctxMenu(tr("PhysEqTableheader Menu"));

    m_pActionInsertColumn = new QAction(tr("Insert Column"), this);
    m_pActionInsertColumn -> setStatusTip(tr("Insert a new time column"));
    connect(m_pActionInsertColumn, SIGNAL(triggered()), this, SLOT(insertColumn()));
    m_pActionRemoveColumn = new QAction(tr("Remove Column"), this);
    m_pActionRemoveColumn -> setStatusTip(tr("Removes a time column"));
    connect(m_pActionRemoveColumn, SIGNAL(triggered()), this, SLOT(removeColumn()));

    ctxMenu.addAction(m_pActionInsertColumn);
    ctxMenu.addAction(m_pActionRemoveColumn);

    m_hdrIdx = logicalIndexAt(pos);
    ctxMenu.exec(mapToGlobal(pos));
}

void PhysEqSolverTableHeader::onSectionDoubleClicked(int logicalIndex) {
    qDebug("PhysEqSolverTableHeader::onSectionDoubleClicked");

    QString strTime = QInputDialog::getText(this, tr("Enter a time value"), tr("Enter a value in seconds"), QLineEdit::Normal, "");
    while (!verifyTimeEntry(strTime.toInt(), logicalIndex)) {
        strTime = QInputDialog::getText(this, tr("Enter a time value"), tr("Enter a value in seconds"), QLineEdit::Normal, "");
    }
    int time = strTime.toInt();
    QList<int> m_rebuiltList;
    for (int i = 0; i < logicalIndex; i++)
        m_rebuiltList.push_back(m_lstTimeSlices.at(i));
    m_rebuiltList.push_back(time);
    for (int i = logicalIndex + 1; i < model() ->columnCount(); i++)
        m_rebuiltList.push_back(m_lstTimeSlices.at(i));
    m_lstTimeSlices.clear();
    m_lstTimeSlices = m_rebuiltList;
    emit updateTimeSlices(logicalIndex, time);
}

bool PhysEqSolverTableHeader::verifyTimeEntry(const int timeSliceAmount, const int logicalIndex) {

    // Its valid...
    bool retVal = true;

    // We need to ensure that the timeSliceAmount in the column indicated by logicalIndex is properly placed because
    // time values should be increasing left to right.
    if (logicalIndex == 0)
        retVal = false;
    else {

        // It's the first element
        if (logicalIndex == 1) {
            if (m_lstTimeSlices.at(logicalIndex - 1) >= timeSliceAmount)
                retVal = false;
        }
        else {
            int count = model() ->columnCount();

            // it's the last element
            if (logicalIndex == count - 1) {
                if (m_lstTimeSlices.at(logicalIndex - 1) <= m_lstTimeSlices.at(logicalIndex - 2))
                    retVal = false;
            }

            // Make sure that the next is not less <= and that the previous is not >= the new one.
            else {
                if ((m_lstTimeSlices.at(logicalIndex - 2) >= timeSliceAmount) || (m_lstTimeSlices.at(logicalIndex) <= timeSliceAmount))
                    retVal = false;
            }
        }
    }
    return retVal;
}

void PhysEqSolverTableHeader::insertColumn() {
    m_pTable ->insertColumn();
}

void PhysEqSolverTableHeader::removeColumn() {
    m_pTable ->removeColumn(m_hdrIdx);
}

