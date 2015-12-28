#ifndef CARTESIANLABEL_H
#define CARTESIANLABEL_H

#include <QtWidgets>

class CartesianLabel : public QGraphicsTextItem {
public:
    CartesianLabel(const QString &, Qt::Alignment, QGraphicsItem * = 0, bool = true);
    CartesianLabel(const QString &, QGraphicsItem * = 0, bool = true);
    CartesianLabel(QGraphicsItem * = 0, bool = true);
    QRectF boundingRect() const;

    Qt::Alignment alignment() const { return m_Flags; }
    void setAlignment(Qt::Alignment flags) { m_Flags = flags; }

    void SetTextInteraction(bool, bool = false);
    QVariant itemChange(QGraphicsItem::GraphicsItemChange, const QVariant &);

    void setDraw(bool bVal) { m_bDraw = bVal; }
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget * = 0);

private:
    Qt::Alignment m_Flags;
    mutable QRectF m_Bounds;
    bool m_bDraw;
};

#endif // CARTESIANLABEL_H
