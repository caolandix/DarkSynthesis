#include <QtWidgets>

#include "cartesianlabel.h"

CartesianLabel::CartesianLabel(const QString &text, Qt::Alignment flags, QGraphicsItem *pParent, bool bDraw, bool editable) : QGraphicsTextItem(text, pParent), m_Flags(flags) {

    setFlags(ItemIgnoresTransformations | ItemIsSelectable | ItemIsMovable | ItemIsFocusable | ItemSendsGeometryChanges);
    setTextInteractionFlags(Qt::NoTextInteraction);
    m_Bounds = QGraphicsTextItem::boundingRect();
    m_bDraw = bDraw;
    m_editable = editable;
}

CartesianLabel::CartesianLabel(const QString &text, QGraphicsItem *pParent, bool bDraw, bool editable) : QGraphicsTextItem(text, pParent), m_Flags(Qt::AlignTop | Qt::AlignLeft) {
    setFlags(ItemIgnoresTransformations | ItemIsSelectable | ItemIsMovable | ItemIsFocusable | ItemSendsGeometryChanges);
    setTextInteractionFlags(Qt::NoTextInteraction);
    m_Bounds = QGraphicsTextItem::boundingRect();
    m_bDraw = bDraw;
}

CartesianLabel::CartesianLabel(QGraphicsItem * pParent, bool bDraw, bool editable) : QGraphicsTextItem(pParent), m_Flags(Qt::AlignTop | Qt::AlignLeft) {
    setFlags(ItemIgnoresTransformations | ItemIsSelectable | ItemIsMovable | ItemIsFocusable | ItemSendsGeometryChanges);
    setTextInteractionFlags(Qt::NoTextInteraction);
    m_Bounds = QGraphicsTextItem::boundingRect();
    m_bDraw = bDraw;
}

QRectF CartesianLabel::boundingRect() const {
    m_Bounds = QGraphicsTextItem::boundingRect();
    QPointF	offset(0.0, 0.0);
    if (m_Flags.testFlag(Qt::AlignRight))
        offset.setX(-m_Bounds.width());
    else if (m_Flags.testFlag(Qt::AlignHCenter))
        offset.setX(-m_Bounds.width() / 2.0);
    if (m_Flags.testFlag(Qt::AlignBottom))
        offset.setY(m_Bounds.height());
    else if (m_Flags.testFlag(Qt::AlignVCenter))
        offset.setY(m_Bounds.height() / 2.0);
    m_Bounds.translate(offset);
    return m_Bounds;
}

void CartesianLabel::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget) {
    if (m_bDraw) {
        pPainter -> translate(m_Bounds.left(), -m_Bounds.top());
        QGraphicsTextItem::paint(pPainter, pOption, pWidget);
    }
}

void CartesianLabel::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *evt) {
    if (!m_editable)
            return;
    qDebug("mouseDoubleClickEvent '%s'", this -> toPlainText().toStdString().c_str());
    if (textInteractionFlags() == Qt::TextEditorInteraction) {

        // if editor mode is already on: pass double click events on to the editor:
        QGraphicsTextItem::mouseDoubleClickEvent(evt);
        return;
    }

    // if editor mode is off:
    // 1. turn editor mode on and set selected and focused:
    SetTextInteraction(true);

    // 2. send a single click to this QGraphicsTextItem (this will set the cursor to the mouse position):
    // create a new mouse event with the same parameters as evt
    QGraphicsSceneMouseEvent *pevtClick = new QGraphicsSceneMouseEvent(QEvent::GraphicsSceneMousePress);
    pevtClick -> setButton(pevtClick -> button());
    pevtClick -> setPos(pevtClick -> pos());
    QGraphicsTextItem::mousePressEvent(pevtClick);
    delete pevtClick; // don't forget to delete the event
}

QVariant CartesianLabel::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    // qDebug("CartesianLabel::itemChange()");
    if (change == QGraphicsItem::ItemSelectedChange) {
        qDebug("itemChange '%s', selected=%s", toPlainText().toStdString().c_str(), value.toString().toStdString().c_str());
    }
    if (change == QGraphicsItem::ItemSelectedChange && textInteractionFlags() != Qt::NoTextInteraction && !value.toBool()) {

        // item received SelectedChange event AND is in editor mode AND is about to be deselected:
        SetTextInteraction(false); // leave editor mode
    }
    return QGraphicsTextItem::itemChange(change, value);
}

void CartesianLabel::SetTextInteraction(bool bOn, bool bSelectAll) {
    if (bOn && textInteractionFlags() == Qt::NoTextInteraction) {

        // switch on editor mode:
        setTextInteractionFlags(Qt::TextEditorInteraction);

        // manually do what a mouse click would do else -- also gives the item keyboard focus
        setFocus(Qt::MouseFocusReason);

        // this ensures that itemChange() gets called when we click out of the item
        setSelected(true);

         // option to select the whole text (e.g. after creation of the TextItem)
        if (bSelectAll) {
            QTextCursor cursor = textCursor();
            cursor.select(QTextCursor::Document);
            setTextCursor(cursor);
        }
    }
    else if (!bOn && textInteractionFlags() == Qt::TextEditorInteraction) {

        // turn off editor mode:
        setTextInteractionFlags(Qt::NoTextInteraction);

        // deselect text (else it keeps gray shade):
        QTextCursor cursor = textCursor();
        cursor.clearSelection();
        setTextCursor(cursor);
        clearFocus();
    }
}
