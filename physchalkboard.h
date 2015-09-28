#ifndef PHYSCHALKBOARD_H
#define PHYSCHALKBOARD_H

#include <QGraphicsScene>
#include <QMenu>

class CartesianLabel;

class PhysChalkboard : public QGraphicsScene {
public:
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem };

    // ctors
    PhysChalkboard();
    // PhysChalkboard(QMenu *itemMenu, QObject *parent = 0);
    PhysChalkboard(QObject * = NULL);
    QFont font() const { return myFont; }
    QColor textColor() const { return myTextColor; }
    QColor itemColor() const { return myItemColor; }
    QColor lineColor() const { return myLineColor; }
    void setLineColor(const QColor &);
    void setTextColor(const QColor &);
    void setItemColor(const QColor &);
    void setFont(const QFont &);

public slots:
    void setMode(Mode mode);
    // void setItemType(DiagramItem::DiagramType );
    void editorLostFocus(CartesianLabel *);

signals:
    void itemInserted(QGraphicsItem *);
    void textInserted(QGraphicsTextItem *);
    void itemSelected(QGraphicsItem *);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

private:
    bool isItemChange(int type);

    //DiagramItem::DiagramType myItemType;
    QMenu *myItemMenu;
    Mode myMode;
    bool leftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *line;
    QFont myFont;
    CartesianLabel *textItem;
    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;
};

#endif // PHYSCHALKBOARD_H
