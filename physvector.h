#ifndef PHYSVECTOR_H
#define PHYSVECTOR_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QList>

class QGraphicsSceneMouseEvent;
class CartesianLabel;
class PhysParticle;

static const double PI = 3.141592653589;

class PhysVector : public QGraphicsLineItem {
public:
    PhysVector(PhysParticle *, PhysParticle *, QGraphicsItem *, QGraphicsScene *);
    ~PhysVector();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

    // accessors
    double Magnitude() const { return m_magnitude; }
protected:

    // Qt overrides
    QVariant itemChange(GraphicsItemChange, const QVariant &) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
private:
    typedef enum { AXIS_HORIZ = 0, AXIS_VERT } AxisOrientation;
    struct Theta {
        double degrees;
        bool bAboveAxis;
        AxisOrientation axisOrientation;
    };

    // Member attributes
    CartesianLabel *m_pLabel;
    double m_magnitude;
    Theta m_Theta;

    PhysParticle *m_StartParticle;
    PhysParticle *m_EndParticle;
    QColor m_Color;
    QPolygonF arrowHead;
};
#endif // PHYSVECTOR_H
