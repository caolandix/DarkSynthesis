#ifndef PHYSGRAPHICSSCENE_H
#define PHYSGRAPHICSSCENE_H
/*
#include "diagramitem.h"
#include "diagramtextitem.h"
*/
#include <QGraphicsScene>

#include "physdataobj.h"
#include "cartesianlabel.h"
#include "physparticle.h"

class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;

class PhysGraphicsScene : public QGraphicsScene {
    Q_OBJECT
public:
    enum Actions { DeleteItem, InsertItem, DeleteLine, InsertLine, DeleteText, InsertText, MoveItem };

    explicit PhysGraphicsScene(QMenu *, QObject * = 0);
    QFont font() const { return m_currFont; }
    QColor textColor() const { return m_currTextColor; }
    QColor itemColor() const { return m_currItemColor; }
    QColor lineColor() const { return m_currLineColor; }
    void setLineColor(const QColor &);
    void setTextColor(const QColor &);
    void setItemColor(const QColor &);
    void setFont(const QFont &);

public slots:
    void setAction(Actions action);
    void setItemType(int);
    void editorLostFocus(CartesianLabel *);

signals:
    void itemInserted(PhysParticle *);
    void textInserted(QGraphicsTextItem *);
    void itemSelected(QGraphicsItem *);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;

private:
    bool isItemChange(int type);

    int m_currItemType;
    QMenu *m_pItemMenu;
    Actions m_currAction;
    bool m_bIsleftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *m_pLine;
    QFont m_currFont;
    CartesianLabel *m_pCurrTextItem;
    QColor m_currTextColor;
    QColor m_currItemColor;
    QColor m_currLineColor;
};

#endif // PHYSGRAPHICSSCENE_H
