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
    void DataObj(const PhysParticleDataObj &obj) { m_DataObj = obj; }
    PhysParticle *copy();
    void init();
    void createConnections();

    QString Name() const { return m_Name; }
    void Name(const QString &str) { m_Name = str; }
    double mass() const { return m_DataObj.mass(); }
    void mass(const double val)  { m_DataObj.mass(val); }
    map<int, QString> EditableProps() const { return m_listEditableProps;}

protected:
    QVariant itemChange(GraphicsItemChange, const QVariant &) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
signals:
    void changeItemName(const QString &, const QString &);
private:
    CartesianLabel *m_pLabel;
    QString m_Name;
    QList<PhysVector *> m_Vectors;
    PhysParticleDataObj m_DataObj;
    CartesianGraph *m_pParent;
    static map<int, QString> m_listEditableProps;
};
Q_DECLARE_METATYPE(PhysParticle *)
#endif // PHYSPARTICLE_H
