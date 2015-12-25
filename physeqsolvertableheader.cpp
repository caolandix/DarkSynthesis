#include "physeqsolvertable.h"
#include "physeqsolvertableheader.h"
#include "physobjectpropdelegate.h"


PhysEqSolverTableHeader::PhysEqSolverTableHeader(QList<double> lstTimeSlices, QWidget *pParent) : QHeaderView(Qt::Horizontal, pParent) {
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

    // Check to see if we are modifying the first column do nothing if we are
    if (logicalIndex > 0) {
        QString strTime = QInputDialog::getText(this, tr("Enter a time value"), tr("Enter a value in seconds"), QLineEdit::Normal, "");
        double timeSlice = 0.0;
        while ((timeSlice = strTime.toDouble()) < 0.0)
            strTime = QInputDialog::getText(this, tr("Enter a time value"), tr("Enter a value in seconds"), QLineEdit::Normal, "");
        QList<double> rebuiltList;

        // conditions
        //      Time slices should increase linearly as t0 is the start time.
        //      timeSliceAmount must be a unique value
        //      timeSliceAmount must be > 0.0
        //      timeSliceAmount cannot be <= the amount to the left of it
        //      timeSliceAmount cannot be = the amount to the right of it
        //      If timeSliceAmount is > the amount to the right of it, all of those values to the right get incremented by
        //      timeSliceAmount. E.g.: if t1 is modified to be 12s, and t2 is 11s, t2 then becomes 12s + 11s = 23s, and so on up the line.


        // At a minimum this value will be 1
        int colCount = m_lstTimeSlices.count();
        int numColumns = model() ->columnCount() - 1;
        int idx = logicalIndex - 1;


        // base case: it's the only item in the list
        if (numColumns == 1 || idx == 0)
            m_lstTimeSlices[0] = timeSlice;
        else {

            // easy case: it's the last item in the list check to see if greater than the one before it
            if (logicalIndex == numColumns) {
                if (m_lstTimeSlices.at(idx - 1) >= timeSlice)
                    return;
                m_lstTimeSlices[idx] = timeSlice;
            }

            // it's between two columns so check their values to ensure that on the left it is greater than, and on the right it is not equal
            else {
                if ((m_lstTimeSlices.at(idx - 1) >= timeSlice) || (m_lstTimeSlices.at(idx + 1) == timeSlice))
                    return;
                m_lstTimeSlices[idx] = timeSlice;
            }

        }

        // reorder the list so that anything to the right of the modified index is corrected for the new value
        int i = 0;
        for (; i < logicalIndex; i++)
            rebuiltList.push_back(m_lstTimeSlices.at(i));
        for (; i < model() ->columnCount() - 1; i++) {
            double sum = m_lstTimeSlices.at(i) + timeSlice;
            rebuiltList.push_back(sum);
        }
        m_lstTimeSlices = rebuiltList;
        emit updateTimeSlices(logicalIndex, timeSlice);
    }
}

void PhysEqSolverTableHeader::insertColumn() {
    m_pTable ->insertColumn();
}

void PhysEqSolverTableHeader::removeColumn() {
    m_pTable ->removeColumn(m_hdrIdx);
}

