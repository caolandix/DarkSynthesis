#ifndef PHYSVECTOR_H
#define PHYSVECTOR_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QList>
#include <QGraphicsSceneMouseEvent>
#include <QContextMenuEvent>

class CartesianLabel;
class PhysParticle;
class CartesianGraph;

static const double PI = 3.141592653589;

class PhysVector : public QGraphicsLineItem {
private:
    typedef enum { DI_VECTORLINE = -1, DI_VECTORHEAD = 0, DI_VECTORTAIL = 1 } MouseClickLocale;
    typedef enum { AXIS_HORIZ = 0, AXIS_VERT } AxisOrientation;
    struct Theta {
        double degrees;
        bool bAboveAxis;
        AxisOrientation axisOrientation;
    };
public:
    PhysVector(CartesianGraph *, const QPointF &, const QString &, PhysParticle * = NULL, PhysParticle * = NULL, QGraphicsScene * = NULL);
    ~PhysVector();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void adjust() Q_DECL_OVERRIDE;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;
    void updatePosition();

    void vectorPropsDlg();
    void createActions();


    // accessors
    double Magnitude() const { return m_magnitude; }
    Theta theta() const { return m_Theta; }
    QColor Color() const { return m_Color; }
    QPolygonF ArrowHead() const { return m_arrowHead; }
    PhysParticle *StartParticle() const { return m_pStartParticle; }
    PhysParticle *EndParticle() const { return m_pEndParticle; }
protected:

    // Qt overrides
    QVariant itemChange(GraphicsItemChange, const QVariant &) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *);

private:
    // Member attributes
    CartesianLabel *m_pLabel;
    double m_magnitude;
    Theta m_Theta;
    PhysParticle *m_pStartParticle;
    PhysParticle *m_pEndParticle;
    QPointF m_StartPoint;
    QPointF m_EndPoint;
    QPointF m_currPos;

    QColor m_Color;
    QPolygonF m_arrowHead;
    qreal m_arrowSize;
    MouseClickLocale m_dragIndex;
    CartesianGraph *m_pParent;
    QAction *m_actVectorProps;

};
#endif // PHYSVECTOR_H
