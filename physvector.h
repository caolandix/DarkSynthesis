#ifndef PHYSVECTOR_H
#define PHYSVECTOR_H

#include <QGraphicsItem>
#include <QList>

class GraphWidget;
class QGraphicsSceneMouseEvent;
class CartesianLabel;

class PhysVector : public QGraphicsItem {
public:
    PhysVector(GraphWidget *);
    ~PhysVector();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

    // accessors
    double Magnitude() const { return m_magnitude; }
protected:
    QVariant itemChange(GraphicsItemChange, const QVariant &) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
private:
    CartesianLabel *m_pLabel;
    double m_magnitude;
};
#endif // PHYSVECTOR_H
