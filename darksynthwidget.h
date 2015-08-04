#ifndef DARKSYNTHWIDGET_H
#define DARKSYNTHWIDGET_H

#include <QGraphicsView>

class Node;

class DarkSynthWidget : public QGraphicsView
{

    Q_OBJECT

public:
    DarkSynthWidget(QWidget *parent = NULL);

    void itemMoved();

public slots:
    void shuffle();
    void zoomIn() { scaleView(qreal(1.2)); };
    void zoomOut() { scaleView(1 / qreal(1.2)); };

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void scaleView(qreal scaleFactor);
private:
    int m_timerId;
    Node *m_pcenterNode;
};

#endif // DARKSYNTHWIDGET_H
