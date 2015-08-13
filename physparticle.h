#ifndef PHYSPARTICLE_H
#define PHYSPARTICLE_H

#include <QGraphicsItem>
#include <QList>

class GraphWidget;
class QGraphicsSceneMouseEvent;

class PhysParticle : public QGraphicsItem {
public:
    PhysParticle(GraphWidget *graphWidget);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
private:
    GraphWidget *graph;
};

#endif // PHYSPARTICLE_H
