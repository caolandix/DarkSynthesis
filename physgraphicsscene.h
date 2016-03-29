#ifndef PHYSGRAPHICSSCENE_H
#define PHYSGRAPHICSSCENE_H

/*
#include "diagramitem.h"
#include "diagramtextitem.h"
*/

#include <QGraphicsScene>
#include "physparticle.h"
#include "physdataobj.h"

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
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem };

    explicit PhysGraphicsScene(QObject *parent = 0);
    QFont font() const { return myFont; }
    QColor textColor() const { return myTextColor; }
    QColor itemColor() const { return myItemColor; }
    QColor lineColor() const { return myLineColor; }
    void setLineColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setItemColor(const QColor &color);
    void setFont(const QFont &font);

public slots:
    void setMode(Mode mode);
    void setItemType(PhysDataObj::DataType type);
    void editorLostFocus(CartesianLabel *item);

signals:
    void itemInserted(PhysParticle *item);
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

private:
    bool isItemChange(int type);

    PhysDataObj::DataType myItemType;
    QMenu *myItemMenu;
    Mode myMode;
    bool leftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *line;
    QFont myFont;
    // DiagramTextItem *textItem;
    CartesianLabel *textItem;
    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;
};

#endif // PHYSGRAPHICSSCENE_H
