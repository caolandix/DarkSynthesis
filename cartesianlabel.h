#ifndef CARTESIANLABEL_H
#define CARTESIANLABEL_H

#include <QtWidgets>

#include "darksynth.h"

class CartesianLabel : public QGraphicsTextItem {
    Q_OBJECT
public:
    CartesianLabel(const QString &, Qt::Alignment, QGraphicsItem * = NULL, bool bMoveable = true, bool bDraw = true);
    CartesianLabel(const QString &, QGraphicsItem * = NULL, bool bMoveable = true, bool bDraw = true);
    CartesianLabel(QGraphicsItem * = NULL, bool bMoveable = true, bool bDraw = true);
    QRectF boundingRect() const;

    Qt::Alignment alignment() const { return m_Flags; }
    void setAlignment(Qt::Alignment flags) { m_Flags = flags; }

    void SetTextInteraction(bool, bool = false);
    QVariant itemChange(QGraphicsItem::GraphicsItemChange, const QVariant &);

    void setDraw(bool bVal) { m_bDraw = bVal; }

    // From PhysBaseItem
    void init(bool, bool);
    CartesianLabel *copy();

    // From QGraphicsTextItem
    int type() const { return DarkSynth::PhysTextType; }

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget * = 0);

private:
    Qt::Alignment m_Flags;
    mutable QRectF m_Bounds;
    bool m_bDraw;
};

#endif // CARTESIANLABEL_H
