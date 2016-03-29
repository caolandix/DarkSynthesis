#ifndef PHYSVECTOR_H
#define PHYSVECTOR_H

#include <QtWidgets>
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
/*
    PhysVector(
            CartesianGraph *pParent, PhysParticle *pParticle,
            const QString variable, const QString equation, const QString name, const double magnitude = 0.0, const bool bDraw = true, const double angle = 0.0);
    PhysVector(CartesianGraph *, const QString, PhysParticle * = NULL, PhysParticle * = NULL);
    */
    PhysVector(PhysParticle *startItem, PhysParticle *endItem, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    ~PhysVector();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void adjust();
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;
    void updatePosition();

    PhysVector *copy();
    void init();

    // accessors
    double Magnitude() const { return m_pDataObj ->Magnitude(); }
    Theta theta() const { return m_Theta; }
    QColor Color() const { return m_Color; }
    void setColor(QColor c) { m_Color = c; }
    QPolygonF ArrowHead() const { return m_arrowHead; }
    PhysParticle *StartParticle() const { return m_pStartParticle; }
    PhysParticle *EndParticle() const { return m_pEndParticle; }
    QString Name() const { return m_pDataObj ->Name(); }
    map<AxisOrientation, QString> OrientationLabelMap() const { return m_OrientationLabelMap;}
    map<int, QString> EditableProps() const { return m_listEditableProps;}
    PhysVectorDataObj *DataObj() const { return m_pDataObj; }

    void Name(const QString &);
    void theta(const Theta &val) { m_Theta = val; }
    void StartParticle(PhysParticle *);
    void EndParticle(PhysParticle *);
    void clearParticle(PhysParticle *);
    void removeFromParticles();
    void createConnections();
    void initGraphicsProperties();

    void StartPoint(const QPointF &pt) { m_StartPoint = pt; }
    void EndPoint(const QPointF &pt) { m_EndPoint = pt; }
    void CurrPos(const QPointF &pt) { m_currPos = pt; }
    void Magnitude(const double val) { m_pDataObj ->Magnitude(val); }
    void Magnitude(const QString &str) { m_pDataObj ->Magnitude(str.toDouble()); }
    void SetDraw(bool bVal) { m_bDraw = bVal; }
    void ThetaAngle(const double);
    void ThetaAngle(const QString &);
    void ThetaAxisOrient(const AxisOrientation val) { m_Theta.axisOrientation = val; }
protected:

    // Qt overrides
    QVariant itemChange(GraphicsItemChange, const QVariant &) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;

signals:
    void reorderObjNav(QGraphicsItem *);
    void changeItemName(const QString &, const QString &);
    void repaint();
private:
    // Member attributes


    // Data Specific (should be pulled out into a separate DataObject like CartesianGraph has
    QPointF m_currPos;
    static map<int, QString> m_listEditableProps;
    bool m_bUseNewThetaAngle;
    Theta m_Theta;
    PhysParticle *m_pStartParticle;
    PhysParticle *m_pEndParticle;

    // Drawing specific.
    bool m_bDraw;
    CartesianLabel *m_pLabel;
    QColor m_Color;
    QPolygonF m_arrowHead;
    qreal m_arrowSize;
    MouseClickLocale m_dragIndex;
    CartesianGraph *m_pParent;
    QPointF m_StartPoint;
    QPointF m_EndPoint;

    PhysVectorDataObj *m_pDataObj;
};

Q_DECLARE_METATYPE(PhysVector *)
#endif // PHYSVECTOR_H
