#ifndef CARTESIANGRAPH_H
#define CARTESIANGRAPH_H

#include <QtWidgets>
#include "cartesiangraphdataobj.h"

class GraphWidget;
class PhysVector;
class PhysParticle;
class CartesianGraphDataObj;

class CartesianGraph : public PhysBaseItem, public QGraphicsItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:

    // ctors/dtor
    CartesianGraph(GraphWidget *, const QString & = "Cartesian Plane", CartesianGraphDataObj * = NULL);
    CartesianGraph(const CartesianGraph &);
    ~CartesianGraph();

    // operator overloads
    CartesianGraph &operator=(const CartesianGraph &);

    // overloaded inherited methods
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

    // accessors -- get
    double tickStep() const { return m_pDataObj -> tickStep(); }
    double xMin() const { return m_pDataObj ->  xMin(); }
    double yMin() const { return m_pDataObj -> yMin(); }
    double xMax() const { return m_pDataObj -> xMax(); }
    double yMax() const { return m_pDataObj -> yMax(); }
    QPointF origin() const { return m_pDataObj -> origin(); }
    QList<PhysVector *> Vectors() const { return m_pDataObj -> Vectors(); }
    QList<PhysParticle *> Particles() const { return m_pDataObj -> Particles(); }
    CartesianGraphDataObj *DataObj() const { return m_pDataObj; }
    GraphWidget *graphWidget() const { return m_pGraphWidget; }
    QString XAxisLabel() const { return m_x_label -> toPlainText(); }
    QString YAxisLabel() const { return m_y_label -> toPlainText(); }
    QString Name() const { return m_pDataObj ->Name(); }
    CartesianLabel *xlabel() const { return m_x_label; }
    map<int, QString> EditableProps() const { return m_listEditableProps;}


    // accessors -- set
    void XAxisLabel(const QString &data) { m_x_label -> setPlainText(data); }
    void YAxisLabel(const QString &data) { m_y_label -> setPlainText(data); }
    void Name(const QString &str) { m_pDataObj ->Name(str); }
    void tickStep(const QString &str) { m_pDataObj ->tickStep(str.toDouble()); }
    void XExtent(const QString &);
    void YExtent(const QString &);

    enum { Type = PhysBaseItem::CartesianGraphType };
    int type() const Q_DECL_OVERRIDE { return Type; }

    CartesianGraph *copy();
    void init();
    void createConnections();
    void restructure();


protected:
    QVariant itemChange(GraphicsItemChange, const QVariant &) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
private:
    GraphWidget *m_pGraphWidget;
    CartesianLabel *m_x_label, *m_y_label;
    CartesianLabel *m_pXMin;
    CartesianLabel *m_pXMax;
    CartesianLabel *m_pYMin;
    CartesianLabel *m_pYMax;
    CartesianGraphDataObj *m_pDataObj;
    int m_borderWidth;
    static map<int, QString> m_listEditableProps;
public slots:
    void onPropChange(const QString &);
    void onReorderObjNav(QGraphicsItem *);
    void onChangeItemName(const QString &, const QString &);
    void onRepaint();
signals:
    void reorderObjNav(QGraphicsItem *);
    void changeItemName(const QString &, const QString &);
    void updateUI();
    void repaint();
};
Q_DECLARE_METATYPE(CartesianGraph *)
#endif // CARTESIANGRAPH_H
