#ifndef PHYSPARTICLE_H
#define PHYSPARTICLE_H

#include <QGraphicsItem>
#include <QList>
#include <QGraphicsSceneMouseEvent>

#include "physbaseitem.h"
#include "cartesianlabel.h"

class GraphWidget;
class PhysVector;

class PhysParticle : public QGraphicsPolygonItem, public PhysBaseItem {
public:
    PhysParticle(QGraphicsItem *);
    PhysParticle(QGraphicsItem *, const QPointF &, const QString &);
    ~PhysParticle();

    enum { Type = ParticleType };
    int type() const Q_DECL_OVERRIDE { return Type; }

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

    bool addVector(PhysVector *);
    bool removeVector(PhysVector *);
    QString Name() const { return m_pLabel -> toPlainText(); }
protected:
    QVariant itemChange(GraphicsItemChange, const QVariant &) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
private:
    CartesianLabel *m_pLabel;
    QList<PhysVector *> m_Vectors;
};

#endif // PHYSPARTICLE_H
