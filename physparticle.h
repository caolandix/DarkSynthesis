#ifndef PHYSPARTICLE_H
#define PHYSPARTICLE_H

#include <QGraphicsItem>
#include <QList>
#include <QGraphicsSceneMouseEvent>

#include "physbaseitem.h"
#include "cartesianlabel.h"
#include "physparticledataobj.h"

class PhysVector;

class PhysParticle : public PhysBaseItem, public QGraphicsPolygonItem {
    Q_OBJECT
public:
    PhysParticle(QGraphicsItem *);
    PhysParticle(QGraphicsItem *, const QPointF &, const QString &);
    ~PhysParticle();

    enum { Type = ParticleType };
    virtual int type() const Q_DECL_OVERRIDE { return Type; }

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

    bool addVector(PhysVector *);
    bool removeVector(PhysVector *);
    void Vectors(const QList<PhysVector *> vectors);
    void DisassociateVectors();
    void DataObj(const PhysParticleDataObj &obj) { m_DataObj = obj; }
    PhysParticle *copy();
    void init();

    QString Name() const { return m_Name; }

    double mass() const { return m_DataObj.mass(); }
    map<int, QString> EditableProps() const { return m_listEditableProps;}

protected:
    QVariant itemChange(GraphicsItemChange, const QVariant &) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
private:
    CartesianLabel *m_pLabel;
    QString m_Name;
    QList<PhysVector *> m_Vectors;
    PhysParticleDataObj m_DataObj;

    static map<int, QString> m_listEditableProps;
};
Q_DECLARE_METATYPE(PhysParticle *)
#endif // PHYSPARTICLE_H
