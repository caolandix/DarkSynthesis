#ifndef CARTESIANLABEL_H
#define CARTESIANLABEL_H

class QGraphicsTextItem;
class QGraphicsSceneMouseEvent;
class QVariant;
class QGraphicsItem;

class CartesianLabel : public QGraphicsTextItem {
public:
    CartesianLabel(const QString &, Qt::Alignment, QGraphicsItem * = 0);
    CartesianLabel(const QString &, QGraphicsItem * = 0);
    CartesianLabel(QGraphicsItem * = 0);

    QRectF boundingRect() const;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget * = 0);

    Qt::Alignment alignment() const { return m_Flags; }
    void setAlignment(Qt::Alignment flags) { m_Flags = flags; }

    void SetTextInteraction(bool, bool = false);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    QVariant itemChange(QGraphicsItem::GraphicsItemChange, const QVariant &);

private:
    Qt::Alignment m_Flags;
    mutable QRectF m_Bounds;
};

#endif // CARTESIANLABEL_H
