#ifndef PHYSPARTICLE_H
#define PHYSPARTICLE_H

#include <QtWidgets>

#include "physbaseitem.h"
#include "cartesianlabel.h"
#include "physvectordataobj.h"
#include "physparticledataobj.h"

class CartesianGraph;
class PhysParticle;
class PhysVector;

class PhysParticle : public PhysBaseItem, public QGraphicsPolygonItem {
    Q_OBJECT
public:
    PhysParticle(CartesianGraph *);
    PhysParticle(CartesianGraph *, const QPointF &, const QString &);
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
    void DataObj(const PhysParticleDataObj *pObj) { *m_pDataObj = *pObj; }
    PhysParticle *copy();
    void init();
    void createConnections();

    QString Name() const { return m_pDataObj ->Name(); }
    void Name(const QString &str);
    double mass() const { return m_pDataObj ->mass(); }
    void mass(const double val)  { m_pDataObj ->mass(val); }
    bool isXAxisLocked() const { return m_bLockXAxis; }
    bool isYAxisLocked() const { return m_bLockYAxis; }
    void LockXAxis(const bool val) { m_bLockXAxis = val; }
    void LockYAxis(const bool val) { m_bLockYAxis = val; }
    CartesianGraph *Parent() const { return m_pParent; }
    PhysParticleDataObj *DataObj() const { return m_pDataObj; }
    void currPos(QPointF pos) { m_pDataObj ->updatePos(pos.x(), pos.y()); }
    QPointF currPos() const { return QPointF(m_pDataObj ->xcoord(), m_pDataObj ->ycoord()); }

    map<int, QString> EditableProps() const { return m_listEditableProps;}

protected:
    QVariant itemChange(GraphicsItemChange, const QVariant &) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
signals:
    void changeItemName(const QString &, const QString &);
    void updateItemPos(QGraphicsItem *, const QPointF &);
private:
    CartesianLabel *m_pLabel;
    QList<PhysVector *> m_Vectors;
    PhysParticleDataObj *m_pDataObj;
    CartesianGraph *m_pParent;
    bool m_bLockXAxis, m_bLockYAxis;
    static map<int, QString> m_listEditableProps;
};
Q_DECLARE_METATYPE(PhysParticle *)
#endif // PHYSPARTICLE_H
