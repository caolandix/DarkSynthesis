#ifndef PHYSVECTOR_H
#define PHYSVECTOR_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QList>
#include <QGraphicsSceneMouseEvent>
#include <QContextMenuEvent>
#include <QStringList>
#include <map>

#include "physbaseitem.h"
#include "cartesianlabel.h"
#include "physvectordataobj.h"

class CartesianGraph;
class PhysParticle;

class PhysVector : public PhysBaseItem, public QGraphicsLineItem {
    Q_OBJECT
public:
    typedef enum { AXIS_HORIZ = 0, AXIS_VERT } AxisOrientation;
private:
    typedef enum { DI_VECTORLINE = -1, DI_VECTORHEAD = 0, DI_VECTORTAIL = 1 } MouseClickLocale;
    struct Theta {
        double degrees;
        bool bAboveAxis;
        AxisOrientation axisOrientation;
    };
    static const map<AxisOrientation, QString> m_OrientationLabelMap;
    static const map<AxisOrientation, QString> createMap();

public:
    enum { Type = PhysBaseItem::VectorType };
    int type() const Q_DECL_OVERRIDE { return Type; }

    PhysVector(CartesianGraph *, const QPointF &, const QString &, PhysParticle * = NULL, PhysParticle * = NULL, QGraphicsScene * = NULL);
    ~PhysVector();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void adjust();
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;
    void updatePosition();

    PhysVector *copy();

    // accessors
    double Magnitude() const { return m_magnitude; }
    Theta theta() const { return m_Theta; }
    QColor Color() const { return m_Color; }
    QPolygonF ArrowHead() const { return m_arrowHead; }
    PhysParticle *StartParticle() const { return m_pStartParticle; }
    PhysParticle *EndParticle() const { return m_pEndParticle; }
    QString Name() const { return m_pLabel -> toPlainText(); }
    map<AxisOrientation, QString> OrientationLabelMap() const { return m_OrientationLabelMap;}

    void theta(const Theta &val) { m_Theta = val; }
    void StartParticle(PhysParticle *);
    void EndParticle(PhysParticle *);
    void StartPoint(const QPointF &pt) { m_StartPoint = pt; }
    void EndPoint(const QPointF &pt) { m_EndPoint = pt; }
    void CurrPos(const QPointF &pt) { m_currPos = pt; }
    void Magnitude(const double val) { m_magnitude = val; }
protected:

    // Qt overrides
    QVariant itemChange(GraphicsItemChange, const QVariant &) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
private:
    // Member attributes

    // Data Specific (should be pulled out into a separate DataObject like CartesianGraph has
    CartesianLabel *m_pLabel;
    QString m_rawLabel;
    double m_magnitude;
    Theta m_Theta;
    PhysParticle *m_pStartParticle;
    PhysParticle *m_pEndParticle;
    QPointF m_StartPoint;
    QPointF m_EndPoint;
    QPointF m_currPos;

    // Drawing specific.
    QColor m_Color;
    QPolygonF m_arrowHead;
    qreal m_arrowSize;
    MouseClickLocale m_dragIndex;
    CartesianGraph *m_pParent;

    PhysVectorDataObj m_DataObj;
};

Q_DECLARE_METATYPE(PhysVector *)
#endif // PHYSVECTOR_H
