#ifndef CARTESIANLABEL_H
#define CARTESIANLABEL_H

class QGraphicsTextItem;
class QGraphicsSceneMouseEvent;
class QVariant;
class QGraphicsItem;
class QContextMenuEvent;

class CartesianLabel : public QGraphicsTextItem {
public:
    CartesianLabel(const QString &, Qt::Alignment, QGraphicsItem * = 0);
    CartesianLabel(const QString &, QGraphicsItem * = 0);
    CartesianLabel(QGraphicsItem * = 0);
    QRectF boundingRect() const;

    Qt::Alignment alignment() const { return m_Flags; }
    void setAlignment(Qt::Alignment flags) { m_Flags = flags; }

    void SetTextInteraction(bool, bool = false);
    QVariant itemChange(QGraphicsItem::GraphicsItemChange, const QVariant &);
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget * = 0);

private:
    Qt::Alignment m_Flags;
    mutable QRectF m_Bounds;
};

#endif // CARTESIANLABEL_H
